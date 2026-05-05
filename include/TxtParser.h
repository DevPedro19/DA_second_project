//
// Created by pedro on 5/4/2026.
//

#ifndef DA_SECOND_PROJECT_TXTPARSER_H
#define DA_SECOND_PROJECT_TXTPARSER_H

#include <set>
#include <string>
#include <vector>
#include <map>

#include "ExecutionPlan.h"
#include "allocation.h"

/**
 * @brief This class is responsible for parsing the .txt file and extracting the data from it.
 * @details The files must follow the specified format:
 *
 * ranges_.txt:
 * # comment line
 * varName: lineNum1[+|-], lineNum2[+|-], ...
 *
 * registers_.txt:
 * # comment line
 * registers: N
 * # algorithm variants: basic, splitting and spilling each with a numeric parameter
 * algorithm: basic
 */
class TxtParser {
public:
    /**
     * @brief Constructor for the TxtParser class.
     * @param rangesFile Filename of the .txt file containing the live ranges of the variables.
     * @param registerFile Filename of the .txt file containing the execution plan.
     */
    explicit TxtParser(std::string rangesFile, std::string registerFile);

    /**
     * @brief This function essentially is the main method for parsing the .txt file.
     */
    void parseFiles(std::map<std::string, std::vector<LiveRange>>& variableLiveRanges, ExecutionPlan& executionPlan);
private:
    /**
     * @brief The filename of the .txt file containing the live ranges of the variables to be parsed.
     */
    std::string rangesFilepath;

    /**
     * @brief The filename of the .txt file containing the execution plan to be parsed.
     */
    std::string registerFilepath;

    /**
     * @brief This function is responsible for parsing the ranges file and populating a map of variable names to their live ranges.
     * @param variableLiveRanges Map that will be populated with the variable names as keys and their live ranges as values.
     * @param file Filename of the .txt file containing the live ranges of the variables.
     */

    static void parseRangesFile(std::map<std::string, std::vector<LiveRange>>& variableLiveRanges, std::string& file);

    /**
     * @brief This function is responsible for parsing the register file and populating the execution plan.
     * @param executionPlan Execution plan that will be populated with the data from the register file.
     * @param file Filename of the .txt file containing the execution plan.
     */

    static void parseRegisterFile(ExecutionPlan& executionPlan, std::string& file);

    /**
    * @brief This function is responsible for parsing a single Line from a LiveRange (where a variable is first defined
    * , read or last read) of the ranges file and extracting the line number and type of the line.
    * @param line The line from the ranges file that contains the data for a single line of a live range.
    * @return A Line struct containing the line number and type of the line.
    */

    static Line parseLine(const std::string &line);

    /**
     * @brief Helper function to remove leading and trailing spaces from a string.
     * @param str String from which to remove leading and trailing spaces.
     * @param s Sequence to remove at the beginning or at the end of the string str.
     */
    static void removeTrailingSequence(std::string& str, const std::string& s);

    /**
     * @brief Converts a string to an integer.
     * @param str Parse string to be converted to an integer.
     * @return integer value obtained from the string.
     */

    static int getInteger(std::string& str);

    /**
     * @brief This function is responsible for parsing the register count from the register file and populating the execution plan.
     * @param executionPlan Execution plan that will be populated with the register count.
     * @param dataStr String containing the register count to be parsed.
     */

    static void getRegisterCount(ExecutionPlan& executionPlan, std::string& dataStr);

    /**
     * @brief This function is responsible for parsing the algorithm variant and its parameter (if applicable) from the register file and populating the execution plan.
     * @param executionPlan Execution plan that will be populated with the algorithm variant and its parameter (if applicable).
     * @param dataStr String containing the algorithm variant to be parsed.
     * @param kValue String containing the parameter of the algorithm variant to be parsed (if applicable).
     */
    static void getAlgorithmVariant(ExecutionPlan& executionPlan, std::string& dataStr, std::string& kValue);


    /**
     * @brief This function is responsible for validating that a given value is greater than or equal to a specified threshold, throwing an exception if it is not.
     * @param val The value to be validated.
     * @param name The name of the value being validated (used in the error message).
     * @param threshold The minimum acceptable value for val.
     * @throws std::domain_error if val is less than threshold, with an error message indicating the name of the value and the invalid value.
     */
    static void rejectIfLessThan(int val, const std::string& name, int threshold);


    /**
     * @brief This function is responsible for validating that a given value is less than or equal to a specified threshold, throwing an exception if it is not.
     * @param val The value to be validated.
     * @param name The name of the value being validated (used in the error message).
     * @param threshold The maximum acceptable value for val.
     * @throws std::domain_error if val is greater than threshold, with an error message indicating the name of the value and the invalid value.
     */

    static void rejectIfGreaterThan(int val, const std::string& name, int threshold);
};

#endif //DA_SECOND_PROJECT_TXTPARSER_H