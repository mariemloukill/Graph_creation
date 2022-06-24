//
// Created by ramizouari on 04/04/2022.
//

#include "writer.h"
#include <iomanip>
#include "tester.h"
#include <numeric>

using namespace PFA;
StreamWriter::StreamWriter(std::ostream &out): out(out) {}

CSVWriter::CSVWriter(std::ostream &out, char sep): StreamWriter(out), separator(sep)
{
}

void CSVWriter::initialize() {
    out << "\"Algorithm Name\"" << separator << "Type" << separator << "\"Graph Name\"" << separator
    << "\"Average Time\"" << separator << "\"Average Memory\"" << separator << "\"Start Time\"" << separator << "\"End Time\"" <<  std::endl;

}

/**
 * TODO: Write the memory time
 * */
void CSVWriter::write(const AlgorithmTest &test)
{
    double timeAvg= std::reduce(test.timeResults.begin(), test.timeResults.end()) / test.timeResults.size();
    double memoryAvg= *std::max_element(test.memoryResults.begin(), test.memoryResults.end()) /1;
    out << '"' << test.name << '"'
    << separator << test.type << separator
    << '"' << test.graphName << '"'
    << separator << timeAvg/1000 << separator << memoryAvg/(1024*1024) << separator << test.startTime << separator << test.endTime << std::endl;
}

void CSVWriter::write(const AlgorithmTestError &testError) {
    out << '"' << testError.name << '"'
        << separator << testError.type << separator
        << '"' << testError.graphName << '"'
        << separator << "CRASHED" << separator << "CRASHED" << std::endl;
}

void StandardWriter::write(const AlgorithmTest &test) {
    double timeAvg= std::reduce(test.timeResults.begin(), test.timeResults.end(), 0.0) / test.timeResults.size();
    double memoryAvg= *std::max_element(test.memoryResults.begin(), test.memoryResults.end()) /1;
    out << std::left << std::setfill('.') << std::setw(40) << test.name
    << std::right << std::setfill('.') << std::setw(40) << timeAvg/1000 << " s" << std::endl;
    out << "Memory usage: " << memoryAvg/(1024*1024) << " MB" << std::endl;

}

void StandardWriter::write(const std::string &graphFile)
{
    out << "Testing on graph file '" << graphFile << "':" << std::endl;
}

void StandardWriter::write(const AlgorithmTestError &testError) {
    out << std::left << std::setfill('.') << std::setw(40) << testError.name
        << std::right << std::setfill('.') << std::setw(40)  << "CRASHED" << std::endl;
    out << "Reason: " << testError.error.what() << std::endl;
}

void JSONWriter::write(const AlgorithmTest &test)
{
    if(!firstWrite)
        out << ",";
    firstWrite=false;
    out << "{" << std::endl;
    out << R"("Algorithm Name": ")" << test.name << "\"," << std::endl;
    out << R"("Type": ")" << test.type << "\"," << std::endl;
    out << R"("Graph Name": ")" << test.graphName << "\"," << std::endl;
    out << R"("Test Times": [)" << std::endl;
    bool firstWriteTime = true;
    for (auto time : test.timeResults) {
        if(!firstWriteTime)
            out << ", ";
        out << time/1000;
        firstWriteTime=false;
    }
    out << "]," << std::endl;
    out << R"("Test Memories": [)" << std::endl;
    firstWriteTime=true;
    for (auto memory : test.memoryResults) {
        if(!firstWriteTime)
            out << ", ";
        out << memory/(1024*1024);
        firstWriteTime=false;
    }
    out << "]," << std::endl;
    out << R"("Start Time" : ")" << test.startTime << "\"," << std::endl;
    out << R"("End Time" : ")" << test.endTime << "\"" << std::endl;
    out << "}" << std::endl;
}

void JSONWriter::finalize() {
    out << ']' << std::endl;
    StreamWriter::finalize();
}

JSONWriter::JSONWriter(std::ostream &out,bool firstWrite) : StreamWriter(out),firstWrite(firstWrite) {}

void JSONWriter::initialize() {
    out << "[" << std::endl;
}

void JSONWriter::write(const AlgorithmTestError &testError) {
    if(!firstWrite)
        out << ",";
    firstWrite=false;
    out << "{" << std::endl;
    out << R"("Algorithm Name": ")" << testError.name << "\"," << std::endl;
    out << R"("Type": ")" << testError.type << "\"," << std::endl;
    out << R"("Graph Name": ")" << testError.graphName << "\"," << std::endl;
    out << R"("Test Times": ["CRASHED"],)" << std::endl;
    out << R"("Test Memories": ["CRASHED"])" << std::endl;
    out << R"("Error": ")" << testError.error.what() << '"' << std::endl;
    out << "}" << std::endl;
}

void Writer::finalize() {
    finalized = true;
}

void Writer::write(const std::string &) {

}

void Writer::initialize() {

}

void MultipleWriter::write(const AlgorithmTest &test) {
    for(auto& writer : writers)
        writer->write(test);
}

void MultipleWriter::write(const std::string &graphFile) {
    for(auto& writer : writers)
        writer->write(graphFile);
}

void MultipleWriter::finalize() {
    for(auto& writer : writers)
        writer->finalize();
}

MultipleWriter::MultipleWriter(std::vector<Writer *> writers): writers(std::move(writers)) {}

void MultipleWriter::addWriter(Writer *writerPtr) {
    writers.push_back(writerPtr);
}

void MultipleWriter::addWriter(Writer &writer) {
    writers.push_back(&writer);
}

void MultipleWriter::initialize() {
    for(auto writer : writers)
        writer->initialize();
}

void MultipleWriter::write(const AlgorithmTestError &testError) {
    for(auto writer : writers)
        writer->write(testError);
}

StandardFileWriter::StandardFileWriter(const std::string& fileName): StandardWriter(file),file(fileName) {
    if(file.exceptions() & std::ofstream::failbit)
        throw std::runtime_error("Could not open file '" + fileName + "'");
}
