#include <iostream>
#include "graph/graph.h"
#include "graph/graph_container.h"
#include "graph/graphsplit.h"
#include <chrono>
#include "tester.h"
#include <filesystem>
#include <memory>
#include "writer/writer.h"
#include "memory/MemoryProfiler.h"
#include "utils/types.h"
#include "boost/program_options.hpp"
#include "utils/utils.h"



enum Mode
{
    DISCARD,RESUME,AUTO
};


size_t countLines(std::istream &I)
{
    return std::count(std::istreambuf_iterator<char>(I),
                      std::istreambuf_iterator<char>(), '\n');
}

using namespace PFA;
/**
 * @brief main function
 * @param  filename name of the file to be generated.
 * @param  mode mode of the file generation, either discard or resume. discard will redo all the calculations, resume will resume the calculations from the last point.
 * */
int main(int argc, char** argv)
{
    namespace po=boost::program_options;
    po::options_description desc("Command Line options");
    desc.add_options()
            ("help", "produce help message")
            ("graphs-folder,f",po::value<std::filesystem::path>(),"Read the folder that contains graphs")
            ("config,c", po::value< std::string >()->default_value("test.cfg"),
             "Path to the configuration file")
            ("mode,m",
             "Mode of the program, either discard or resume. discard will redo all the calculations, resume will resume the calculations from the last point.")
            ("tests-per-implementation,t",po::value<int>(),"Number of tests per implementation")
            ("test-types,T",po::value<std::string>(),"Container types that will be tested, 'one' denotes VectorVectorContainer");
    po::options_description cfg_desc("Configuration options");
    cfg_desc.add_options()
            ("tests-per-implementation",po::value<int>()->default_value(3),"Number of tests per implementation")
            ("test-types,T",po::value<std::string>()->default_value("one"),"Container types that will be tested, 'one' denotes VectorVectorContainer")
            ("graphs-folder",po::value<std::filesystem::path>(),"Read the folder that contains graphs")
            ("mode",po::value< std::string >()->default_value("discard"),"Mode of the program, either discard or resume. discard will redo all the calculations, resume will resume the calculations from the last point.")
            ("human-output.enable",po::value<bool>()->default_value(true),"Enable human output")
            ("human-output.path",po::value<std::string>(),"Path to the output file. If not set, output will be written to standard output")
            ("csv.enable",po::value<bool>()->default_value(false),"Enable csv output")
            ("csv.path",po::value<std::filesystem::path>(),"Path to the csv file")
            ("csv.separator",po::value<std::string>()->default_value(","),"Separator of the csv file")
            ("json.enable",po::value<bool>()->default_value(false),"Enable json output")
            ("json.path",po::value<std::filesystem::path>(),"Path to the json file")
            ("json.finalize",po::value<bool>()->default_value(true),"After successful execution, marks the json file as finished")
            ("profile.enable",po::value<bool>()->default_value(false),"Periodically get memory usage")
             ("profile.path",po::value<std::filesystem::path>(),"Path to the memory profile file")
            ("profile.interval",po::value<std::string>()->default_value("200ms"),"The interval between two profiling operations")
            ("sequential.enable",po::value<bool>()->default_value(true),"Enable sequential execution tests")
            ("parallel.enable",po::value<bool>()->default_value(false),"Enable parallel execution tests, ignored if the tests for sequential execution is enabled")
            ("parallel.splits",po::value<std::vector<std::string>>(),"Splits to perform in parallel")
            ("parallel.inplace",po::value<bool>()->default_value(true),"Read file inplace without doing any file split");

    po::variables_map vm;

    po::store(parse_command_line(argc, argv, desc), vm);

    // config with help
    if(vm.contains("help"))
    {
        std::cout << "Usage: PFAProject graphs_path [options]\n";
        std::cout << desc << std::endl;
        std::cout << cfg_desc << std::endl;
        return 0;
    }
    // parsing config file
    try {
        po::store(parse_config_file(vm["config"].as<std::string>().c_str(), cfg_desc,true), vm);
        po::notify(vm);
    }
    catch(boost::program_options::error& e) {
        std::cerr << "Configuration error: " << e.what() << ". Exiting..." << std::endl;
        return 1;
    }

    //get umber of test from config file
    PFA::Tester tester(vm["tests-per-implementation"].as<int>());
    // initializing writers
    PFA::MultipleWriter writers;
    std::unique_ptr<PFA::Writer> stdWriter,csvWriter,jsonWriter;
    std::ofstream JSONFile, CSVFile, profileFile;
    std::unique_ptr<PFA::MemoryProfiler> profiler;

    // human output options
    if(vm["human-output.enable"].as<bool>())
    {
        if(vm.contains("human-output.path"))
            try {
                stdWriter = std::make_unique<StandardFileWriter>(vm["human-output.path"].as<std::string>());
            }
            catch(std::exception& e) {
                std::cerr << "Error: " << e.what() << ". Defaulting to standard output" << std::endl;
                stdWriter = std::make_unique<StandardWriter>(std::cout);
            }
        else
            stdWriter = std::make_unique<StandardWriter>(std::cout);
        writers.addWriter(stdWriter.get());
    }
    // mode discard ,resume or auto
    Mode mode = DISCARD;
    if(vm["mode"].as<std::string>() == "resume")
        mode = RESUME;
    else if(vm["mode"].as<std::string>() == "auto")
        mode = AUTO;
    /*
     * Number of iterations to skip
     * Works only in resume mode
     * */
    int skip=0;
    std::ios::openmode openMode=std::ios::out;


    /*
     * Configuring CSV output
     * */
    if(vm["csv.enable"].as<bool>())
    {
        bool csvFileProblem=false;
        std::filesystem::path csvFilePath;
        try
        {
            csvFilePath=vm["csv.path"].as<std::filesystem::path>();

            /*
             * Configuring resume mode, works only when there is a csv output.
             * */
            if(mode==RESUME)
            {
                openMode|=std::ios::app;
                /*
                 * File containing last session, if it exists
                 * */
                std::ifstream inFile(csvFilePath);
                inFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                if (inFile)
                    skip= countLines(inFile);
            }
            else if(mode ==AUTO)
            {
                openMode|=std::ios::app;
                if(std::filesystem::exists(csvFilePath))
                {
                    std::ifstream inFile(csvFilePath);
                    inFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                    if (inFile)
                        skip= countLines(inFile);
                }
            }
        }
        catch(std::exception& e) {
            std::cerr << "Error: " << e.what() << ". Defaulting to 'result.csv'" << std::endl;
            if(openMode|std::ios::app) {
                openMode &= ~std::ios::app;
                std::cerr  << "Ignoring mode '" << vm["mode"].as<std::string>() << "' because of error" << std::endl;
            }
            csvFilePath="result.csv";
        }

        bool csvFail=false;
        CSVFile.open(csvFilePath,openMode);
        if(!CSVFile.is_open())
        {   if(csvFilePath!="result.csv")
            {
                std::cerr << "Error: Cannot open file '" << csvFilePath << "'. Defaulting to 'result.csv'" << std::endl;
                csvFilePath="result.csv";
                CSVFile.open(csvFilePath,openMode);
            }
            if(!CSVFile.is_open()) {
                std::cerr << "Unable to open file '" << csvFilePath << "'. Ignoring csv output" << std::endl;
                csvFail=true;
            }
        }
        if(!csvFail) {
            char separator;
            if (vm["csv.separator"].as<std::string>() == "tab" || vm["csv.separator"].as<std::string>() == "\\t")
                separator = '\t';
            else
                separator = vm["csv.separator"].as<char>();
            csvWriter = std::make_unique<CSVWriter>(CSVFile, separator);
            writers.addWriter(csvWriter.get());
        }
    }

    /*
     * Configuring JSON output
     * */
    if(vm["json.enable"].as<bool>())
    {
        std::filesystem::path jsonFilePath;
        try {
            jsonFilePath=vm["json.path"].as<std::filesystem::path>();
        }
        catch(std::exception& e) {
            std::cerr << "Error: " << e.what() << ". Defaulting to 'result.json'" << std::endl;
            jsonFilePath="result.json";
        }

        bool jsonFail=false;
        JSONFile.open(jsonFilePath,openMode);
        if(!JSONFile.is_open())
        {   if(jsonFilePath!="result.json")
            {
                std::cerr << "Error: Cannot open file '" << jsonFilePath << "'. Defaulting to 'result.csv'" << std::endl;
                jsonFilePath="result.json";
                JSONFile.open(jsonFilePath,openMode);
            }
            if(!JSONFile.is_open()) {
                std::cerr << "Unable to open file '" << jsonFilePath << "'. Ignoring json output" << std::endl;
                jsonFail=true;
            }
        }
        if(!jsonFail)
        {
            jsonWriter = std::make_unique<JSONWriter>(JSONFile,skip==0);
            writers.addWriter(jsonWriter.get());
        }
    }

    /*
     * Configuring Memory Profiler
     * */
    if(vm["profile.enable"].as<bool>()) try
    {
        profileFile.open(vm["profile.path"].as<std::filesystem::path>(),openMode);
        auto interval=parse_duration(vm["profile.interval"].as<std::string>());
        profiler=std::make_unique<StandardMemoryProfiler>(profileFile,interval,!skip);
    }
    catch(std::exception& e)
    {
        using  namespace std::chrono_literals;
        profiler=std::make_unique<StandardMemoryProfiler>(profileFile,200ms,!skip);
        std::cerr << "Error: " << e.what() << ". Defaulting to a 200ms interval"<< std::endl;
    }

    //configuring creation strategy  (sequential or parallel)
    // I need to add strategy 3
    if(vm["sequential.enable"].as<bool>())
    {
        if(vm["test-types"].as<std::string>()=="one") //if only vector of vectors
            tester.writeGraphCreationAllImplementationsSequential<CurrentType>(
                vm["graphs-folder"].as<std::filesystem::path>(), writers, skip);
        // if testing with all containers
        else tester.writeGraphCreationAllImplementationsSequential<TestTypes>(
                    vm["graphs-folder"].as<std::filesystem::path>(), writers, skip);
    }
    else if(vm["parallel.enable"].as<bool>())
    {
        if(vm["parallel.inplace"].as<bool>())
        {
            auto splitsStr= split_regex(vm["parallel.splits"].as<std::vector<std::string>>().front(),R"([\n\r\t ]+)");
            bool finalize=vm["json.finalize"].as<bool>();
            for(int i=0;i<splitsStr.size();i++)
                if(vm["test-types"].as<std::string>()=="one")
                    skip=tester.writeGraphCreationAllImplementationsParallelInplace<CurrentType>(
                        vm["graphs-folder"].as<std::filesystem::path>(), writers, std::stoi(splitsStr[i]), skip, i==splitsStr.size()-1 && finalize);
                else if(vm["test-types"].as<std::string>()=="alt")
                    skip=tester.writeGraphCreationAllImplementationsParallelInplace<AlternativeType>(
                            vm["graphs-folder"].as<std::filesystem::path>(), writers, std::stoi(splitsStr[i]), skip, i==splitsStr.size()-1 && finalize);
                else skip=tester.writeGraphCreationAllImplementationsParallelInplace<TestTypes>(
                        vm["graphs-folder"].as<std::filesystem::path>(), writers, std::stoi(splitsStr[i]),skip, i==splitsStr.size()-1 && finalize);
        }
        /*else {
            if(vm["test-types"].as<std::string>()=="one")
                tester.writeGraphCreationAllImplementationsParallel<CurrentType>(
                    vm["graphs-folder"].as<std::filesystem::path>(), writers, skip);
            else tester.writeGraphCreationAllImplementationsParallel<TestTypes>(
                        vm["graphs-folder"].as<std::filesystem::path>(), writers, skip);
        }*/
    }
    //configuring profiler
    if(profiler) {
        profiler->endProfiler = true;
        profiler->join();
    }
    JSONFile.close();
    CSVFile.close();
    profileFile.close();

}
