//
// Created by ramizouari on 04/04/2022.
//

#ifndef PFAPROJECT_WRITER_H
#define PFAPROJECT_WRITER_H
#include <ios>
#include <vector>

namespace PFA
{
    class AlgorithmTest;
    /**
     * @brief The Writer base class
     * @details This class is used to write test results.
     * @author PFA Team
     */
    class Writer {
        bool finalized;
    public:
        virtual ~Writer()=default;
        /**
     * @brief Write a test result
     * @details This method is used to write a test result.
     */
        virtual void write(const AlgorithmTest&)=0;
        /**
         * @brief Write a comment
         * @details This method is used to write a human readable comment, It is ignored unless the instance is a StandardWriter.
         */
        virtual void write(const std::string &);
        /**
         * @brief Write the header of the file
         * @details This method is called after finishing writing all the tests.
         */
        virtual void finalize();
    };

    /**
     * @brief Writer on an output stream
     * @details This class is used to write test results on an output stream.
     * @author PFA Team
     */
    class StreamWriter : public Writer {
    protected:
        std::ostream& out;
    public:
        StreamWriter(std::ostream& out);
    };

    /**
     * @brief Human readable writer
     * @details This class is used to write test results on a stream, with human readable output.
     * @author PFA Team
     */
    class StandardWriter:public StreamWriter{
    public:
        using StreamWriter::StreamWriter;
        void write(const AlgorithmTest&) override;
        void write(const std::string &) override;
    };

    /**
     * @brief StreamWriter with a CSV Format
     * @details This class is used to write test results with a CSV format.
     * @author PFA Team
     */
    class CSVWriter :public StreamWriter{
        char separator;
        void writeHeader();
    public:
        CSVWriter(std::ostream& out,char sep=',');
        void write(const AlgorithmTest& data) override;
    };

    /**
     * @brief StreamWriter with a JSON format
     * @details This class is used to write test results with a JSON format.
     * @author PFA Team
     */
    class JSONWriter :public StreamWriter{
        bool finalized;
        bool firstWrite=true;
        void writeHeader();
    public:
        JSONWriter(std::ostream& out);
        void write(const AlgorithmTest& data) override;
        void finalize() override;
    };

    /**
     * @brief Multiple Writers
     * @details This class is used to write test results using multiple writers.
     * @author PFA Team
     */
    class MultipleWriter : public Writer {
    protected:
        std::vector<Writer*> writers;
    public:
        MultipleWriter(std::vector<Writer*> writers={});
        void write(const AlgorithmTest&) override;
        void write(const std::string &) override;
        void finalize() override;
        void addWriter(Writer*);
        void addWriter(Writer&);
    };

}
#endif //PFAPROJECT_WRITER_H
