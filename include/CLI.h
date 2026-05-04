#ifndef DA_SECOND_PROJECT_CLI_H
#define DA_SECOND_PROJECT_CLI_H

#include <string>
#include <vector>

class CLI {
public:
    CLI();
    static void printTitle();
    static void checkValidInputFiles(const std::string& rangesFile , const std::string& registersFile);
    static std::vector<std::string> askInputFilePath();
    //static void readInput(const std::string& inputFileName, Data& data);
    //void writeOutput(const Result& result, int riskAnalysis, const std::string& outputFileName);
    void processArgs(const std::vector<std::string> & args);
    void execute(const std::vector<std::string>& args);
    void setRangesFileName(const std::string& inputFileName);
    void setRegistersFileName(const std::string& inputFileName);
    void setOutputFileName(const std::string& outputFileName);
    void setOutputFromBatch(bool value);

private:
    std::string _rangesFileName;
    std::string _registersFileName;
    std::string _outputFileName;
    bool _outputFromBatch = false;
};

#endif //DA_SECOND_PROJECT_CLI_H
