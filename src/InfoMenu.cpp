#include "InfoMenu.h"

#include <iostream>
#include <limits>
#include <map>
#include <vector>

InfoMenu::InfoMenu(const std::map<std::string, std::vector<LiveRange>> &variableLiveRanges, const ExecutionPlan& executionPlan) : variableLiveRanges(variableLiveRanges), executionPlan(executionPlan) {}

void InfoMenu::displayOptions() {
    std::cout << "\n=======================================\n"
              << "        REGISTER ALLOCATION TOOL       \n"
              << "=======================================\n"
              << "  [1] View Live Ranges\n"
              << "  [2] View Execution Plan\n"
              << "  [3] Run Allocation Algorithm\n"
              << "  [4] Exit\n"
              << "=======================================\n"
              << "  Select an option (1-4): ";
}

void InfoMenu::displayLiveRanges() {
    std::cout << "\n=== Live Ranges List ===" << std::endl;

    for (const auto& [varName, liveRanges] : variableLiveRanges) {
        std::cout << " Variable: " << varName << std::endl;
        for (const auto& liveRange : liveRanges) {
            std::cout << "   Live Range: ";
            for (const auto& line : liveRange) {
                std::cout << "" << line.lineNum
                          << (line.type == firstDef ? "+" : (line.type == read ? "" : "-")) << " ";
            }
            std::cout << std::endl;
        }
    }
}

void InfoMenu::displayExecutionPlan() {
    std::cout << "\n=== Execution Plan ===" << std::endl;

    std::cout << "  Register Count: " << executionPlan.registerCount << std::endl;
    std::cout << "  Algorithm Variant: " << (executionPlan.algorithmVariant == basic ? "basic" : (executionPlan.algorithmVariant == splitting ? "splitting" : "spilling")) << std::endl;
    if (executionPlan.algorithmVariant != basic) std::cout << "K: " << executionPlan.k << std::endl;
}

void InfoMenu::printNonDefinedField(const int& field) {
    if (!field) {
        std::cout << "Not defined" << std::endl;
    }
    else {
        std::cout << field << std::endl;
    }
}

int InfoMenu::display() {
    int retV = 0;
    unsigned opt = 0;

    while (opt != 3 && opt != 4) {
        displayOptions();

        while(!(std::cin >> opt)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  Invalid input. Please enter a number.\n"
                      << "  Select an option (1-4): ";
        }

        while (opt < 1 || opt > 4) {
            std::cout << "  Invalid option.\n" << "  Select an option (1-4): ";
            while(!(std::cin >> opt)){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "  Invalid input. Please enter a number.\n"
                          << "  Select an option (1-4): ";
            }
        }

        switch (opt) {
        case 1: displayLiveRanges(); break;
        case 2: displayExecutionPlan(); break;
        case 3: retV = 1; break;
        default: break;
        }
    }
    return retV; // 1 -> run max allocation algr. Else exit
}

