#ifndef DA_SECOND_PROJECT_INFOMENU_H
#define DA_SECOND_PROJECT_INFOMENU_H

#include "allocation.h"
#include "ExecutionPlan.h"

/**
 * @brief Provider a user interface that allows the user's to select different options to view the data and run the algorithm.
 */
class InfoMenu {
public:
    /**
     * @brief Constructor of InfoMenu with the given data.
     * @param variableLiveRanges Reference to the map that contains the live ranges mapped to each variable name.
     * @param executionPlan Reference to the execution plan struct that tells how the algorithm should run.
     */
    InfoMenu(const std::map<std::string, std::vector<LiveRange>> &variableLiveRanges, const ExecutionPlan& executionPlan);
    /**
     * @brief Displays the information meny and handles user interaction with the CLI.
     * The user can choose to view the live ranges, execution plan or run the allocation algorithm.
     * @return Either 0, if the user chooses to exit, or  1, if the user chooses to run the allocation algorithm.
     */
    int display();

private:
    /**
     * @brief Displays the menu options.
     */
    static void displayOptions();

    /**
     * @brief Prints a field value or indicates if it is not defined.
     * @param field Prints a field value or indicates if it is not defined.
     */
    static void printNonDefinedField(const int& field);

    /**
     * @brief Displays the live ranges of the variables.
     */
    void displayLiveRanges();

    /**
     * @brief Displays the execution plan.
     */
    void displayExecutionPlan();

    /**
     * @brief Reference to a map of each variable name to their corresponding live range.
     */
    const std::map<std::string, std::vector<LiveRange>>& variableLiveRanges;

    /**
     * @brief Reference to the execution plan of the algorithm.
     */
    const ExecutionPlan& executionPlan;
};

#endif //DA_SECOND_PROJECT_INFOMENU_H
