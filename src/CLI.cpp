#include <filesystem>
#include <iostream>
#include <vector>

#include "CLI.h"

#include "InfoMenu.h"
#include "TxtParser.h"

CLI::CLI() = default;

void CLI::setRangesFileName(const std::string &rangesFileName) {
    std::filesystem::path p = "../input/ranges";
    p /= rangesFileName;
    _rangesFileName = p.string();
}

void CLI::setRegistersFileName(const std::string &registersFileName) {
    std::filesystem::path p = "../input/registers";
    p /= registersFileName;
    _registersFileName = p.string();
}

void CLI::setOutputFileName(const std::string &outputFileName) {
    _outputFileName = outputFileName;
}

void CLI::setOutputFromBatch(const bool value) {
    _outputFromBatch = value;
}

void CLI::printTitle() {
    std::cout << "\n=======================================\n"
              << "        REGISTER ALLOCATION TOOL        \n"
              << "=======================================\n" << std::endl;
}

void CLI::processArgs(const std::vector<std::string> &args) {
    if (args.size() >= 2 && args[1] == "-b") {
        // Batch mode
        checkValidInputFiles(args[2], args[3]);
        setRangesFileName(args[2]);
        setRegistersFileName(args[3]);
        if (args.size() == 5) {
            setOutputFileName(args[4]);
            setOutputFromBatch(true);
        }
        // Otherwise the output is put in the same as the rest
    } else {
        const std::string rangesFile = askRangeFilePath();
        const std::string registersFile = askRegisterFilePath();
        checkValidInputFiles(rangesFile, registersFile);
        setRangesFileName(rangesFile);
        setRegistersFileName(registersFile);
    }
}

void CLI::checkValidInputFiles(const std::string& rangesFile, const std::string& registersFile) {
    if (rangesFile.empty() || registersFile.empty()) {
        throw std::invalid_argument("Input file name cannot be empty.");
    }

    size_t dotPosRanges = rangesFile.rfind('.');
    size_t dotPosRegisters = registersFile.rfind('.');

    if (dotPosRanges == std::string::npos || rangesFile.substr(dotPosRanges) != ".txt"
        || dotPosRegisters == std::string::npos ||registersFile.substr(dotPosRegisters) != ".txt") {
        throw std::invalid_argument("Input file extension should be .txt.");
    }
}

void CLI::readInput(const std::string& rangesFile, const std::string& registersFile, std::map<std::string, std::vector<LiveRange>>& variableLiveRanges, ExecutionPlan& executionPlan){

    TxtParser parser(rangesFile, registersFile);
    parser.parseFiles(variableLiveRanges, executionPlan);
}

std::string CLI::askRangeFilePath() {
    constexpr char sep = std::filesystem::path::preferred_separator;
    std::cout << "Enter range file from ranges folder (.txt):\n(" << std::filesystem::current_path().string() << sep << "input/ranges" << sep << ")";
    std::string rangesFile;
    std::cin >> rangesFile;
    return rangesFile;
}

std::string CLI::askRegisterFilePath() {
    constexpr char sep = std::filesystem::path::preferred_separator;
    std::cout << "Enter register file from registers folder (.txt):\n(" << std::filesystem::current_path().string() << sep << "input/registers" << sep << ")";
    std::string registersFile;
    std::cin >> registersFile;
    return registersFile;
}


void CLI::execute(const std::vector<std::string> &args) {
    printTitle();
    processArgs(args);

    std::map<std::string, std::vector<LiveRange>> variableLiveRanges;
    ExecutionPlan executionPlan{};
    readInput(_rangesFileName, _registersFileName, variableLiveRanges, executionPlan);

    InfoMenu infoMenu(variableLiveRanges, executionPlan);
    if (infoMenu.display()) {
        // Run the algorithm
    }
}
