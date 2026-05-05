#ifndef DA_SECOND_PROJECT_CLI_H
#define DA_SECOND_PROJECT_CLI_H

#include <map>
#include <string>
#include <vector>

#include "allocation.h"
#include "ExecutionPlan.h"

/**
 * @brief The CLI class eposes all implemented funcionalities in a user-friendly manner.
 */

class CLI {
public:

    /**
     * @brief Default constructor for the CLI class.
     */
    CLI();

    /**
     * @brief Prints the title of the program.
     */
    static void printTitle();

    /**
     * @brief Checks if the given input files are valid (exists and has .csv extension)
     * @param rangesFile The path to the ranges file to be checked.
     * @param registersFile The path to the registers file to be checked.
     */
    static void checkValidInputFiles(const std::string& rangesFile, const std::string& registersFile);

    /**
     * @brief Asks the user to input the file from the ranges folder
     * @return a string with the name of ranges name.
     */
    static std::string askRangeFilePath();


    /**
     * @brief Asks the user to input the file from the registers folder
     * @return a string with the name of registers name
     */
    static std::string askRegisterFilePath();


    /**
     * @brief Creates a TxtParser object that will parse the files with the given result
     * @param rangesFile string with the path to the range file
     * @param registersFile string with the path to the range file
     * @param variableLiveRanges map that will contain the live ranges of each variable
     * @param executionPlan struct that tells the algorithm how it should run (registers num, variant and k parameter if used)
     */
    static void readInput(const std::string& rangesFile, const std::string& registersFile, std::map<std::string, std::vector<LiveRange>>&
                          variableLiveRanges, ExecutionPlan& executionPlan);

    /**
     * @brief Processes the command line arguments and determines if the execution is in batch or interactive modes and behaves accordingly to check the validity of the input file's extension and set the input and output file paths.
     * @param args Command line arguments passed to the program when executed.
     */
    void processArgs(const std::vector<std::string> & args);

    /**
     * @brief Main method of the CLI class that builds the high-level flow of the CLI execution, calling the necessary methods to read the input, run the allocation algorithm and write the output.
     * @param args Command line arguments passed to the program when executed.
     */
    void execute(const std::vector<std::string>& args);

    /**
     * @brief Sets the input ranges file name.
     * @param rangesFileName Name of the input ranges file to be set.
     */
    void setRangesFileName(const std::string& rangesFileName);

    /**
     * @brief Sets the input registers file name.
     * @param registersFileName Name of the input register file to be set.
     */
    void setRegistersFileName(const std::string& registersFileName);

    /**
     * @brief Sets the output file name.
     * @param outputFileName Name of the output file to be set.
     */
    void setOutputFileName(const std::string& outputFileName);

    /**
     * @brief Sets the boolean value indicating whether the output file name comes from batch mode (true) or not (false).
     * @param value Boolean value to be attributed to the isValidOutputFileName_ field.
     */
    void setOutputFromBatch(bool value);

private:
    /**
     * @brief Name of the input ranges file.
     */
    std::string _rangesFileName;

    /**
     * @brief Name of the input registers file to be read.
     */
    std::string _registersFileName;

    /**
     * @brief Name of the output file to be written.
     */
    std::string _outputFileName;
    
    /**
     * @brief Boolean value indicating whether the output file name comes from batch mode (true) or not (false). This is used to determine if the output file name provided in batch mode should be considered over the output file name specified in the input .csv file. Its value is false by default.
     */
    bool _outputFromBatch = false;
};
#endif //DA_SECOND_PROJECT_CLI_H
