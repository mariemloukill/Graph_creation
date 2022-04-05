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
    << "\"Average Time\"" << separator << "\"Average Memory\"" << std::endl;

}

/**
 * TODO: Write the memory time
 * */
void CSVWriter::write(const AlgorithmTest &test)
{
    double timeAvg= std::reduce(test.timeResults.begin(), test.timeResults.end()) / test.timeResults.size();
    double memoryAvg= std::reduce(test.memoryResults.begin(), test.memoryResults.end()) / test.memoryResults.size();
    out << '"' << test.name << '"'
    << separator << test.type << separator
    << '"' << test.graphName << '"'
    << separator << timeAvg << separator << memoryAvg << std::endl;
}

void StandardWriter::write(const AlgorithmTest &test) {
    double timeAvg= std::reduce(test.timeResults.begin(), test.timeResults.end(), 0.0) / test.timeResults.size();
    out << std::left << std::setfill('.') << std::setw(40) << test.name
    << std::right << std::setfill('.') << std::setw(40) << timeAvg << " ms" << std::endl;
    out << "Memory usage: " << GlobalAllocator::max_memory << " bytes" << std::endl;

}

void StandardWriter::write(const std::string &graphFile)
{
    out << "Testing on graph file '" << graphFile << "':" << std::endl;
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
        out << time;
        firstWriteTime=false;
    }
    out << "]," << std::endl;
    out << R"("Test Memories": [)" << std::endl;
    firstWriteTime=true;
    for (auto memory : test.memoryResults) {
        if(!firstWriteTime)
            out << ", ";
        out << memory;
        firstWriteTime=false;
    }
    out << "]" << std::endl;
    out << "}" << std::endl;
}

void JSONWriter::finalize() {
    out << ']' << std::endl;
    StreamWriter::finalize();
}

JSONWriter::JSONWriter(std::ostream &out) : StreamWriter(out) {

}

void JSONWriter::initialize() {
    out << "[" << std::endl;
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
