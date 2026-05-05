//
// Created by pedro on 5/4/2026.
//

#include "TxtParser.h"
#include <iostream>

int main() {
    // For testing the parser
    std::string rangesFile = "../test/ranges1.txt";
    std::string registerFile = "../test/registers4.txt";
    TxtParser parser(rangesFile, registerFile);
    std::map<std::string, std::vector<LiveRange>> variableLiveRanges;
    ExecutionPlan executionPlan = {};
    parser.parseFiles(variableLiveRanges, executionPlan);
    for (const auto& [varName, liveRanges] : variableLiveRanges) {
        std::cout << "Variable: " << varName << std::endl;
        for (const auto& liveRange : liveRanges) {
            std::cout << "  Live Range:";
            for (const auto& line : liveRange) {
                std::cout << "" << line.lineNum
                          << (line.type == firstDef ? "+" : (line.type == read ? "" : "-")) << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << "Execution Plan:" << std::endl;
    std::cout << "  Register Count: " << executionPlan.registerCount << std::endl;
    std::cout << "  Algorithm Variant: " << (executionPlan.algorithmVariant == basic ? "basic" : (executionPlan.algorithmVariant == splitting ? "splitting" : "spilling")) << std::endl;
    std::cout << "  K: " << executionPlan.k << std::endl;
    return 0;
}
