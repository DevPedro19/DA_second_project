#include <filesystem>
#include <iostream>
#include <vector>

#include "CLI.h"

CLI::CLI() = default;

void CLI::setRangesFileName(const std::string &rangesFileName) {
    std::filesystem::path p = "input/ranges";
    p /= rangesFileName;
    this->_rangesFileName = p.string();
}

void CLI::setRegistersFileName(const std::string &registersFileName) {
    std::filesystem::path p = "input/registers";
    p /= registersFileName;
    this->_registersFileName = p.string();
}

void CLI::setOutputFileName(const std::string &outputFileName) {
    this->_outputFileName = outputFileName;
}

void CLI::setOutputFromBatch(const bool value) {
    this->_outputFromBatch = value;
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
        const std::vector<std::string> inputFilesName = askInputFilePath();
        checkValidInputFiles(inputFilesName[0], inputFilesName[1]);
        setRangesFileName(inputFilesName[0]);
        setRegistersFileName(inputFilesName[1]);
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

void CLI::readInput(const std::string &rangesFile, const std::string &registersFile) {
    TxtParser parser(rangesFile, registersFile);
    // exec the function that will parse
}

std::vector<std::string> CLI::askInputFilePath() {
    constexpr char sep = std::filesystem::path::preferred_separator;
    std::cout << "Enter input path to ranges and registers files, respectively (.txt):\n(" << std::filesystem::current_path().string() << sep << "input" << sep << ")";
    std::string rangesFile, registersFile;
    std::cin >> rangesFile >> registersFile;
    return std::vector{rangesFile, registersFile};
}

void CLI::execute(const std::vector<std::string> &args) {
    printTitle();
    processArgs(args);

    readInput(_rangesFileName, _registersFileName);
}
