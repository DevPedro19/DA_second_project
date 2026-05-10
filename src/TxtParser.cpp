#include "TxtParser.h"

#include <fstream>
#include <iostream>
#include <sstream>

TxtParser::TxtParser(std::string rangesFile, std::string registerFile) {
    this->rangesFilepath = std::move(rangesFile);
    this->registerFilepath = std::move(registerFile);
}

void TxtParser::parseFiles(std::map<std::string, std::vector<LiveRange>> &variableLiveRanges, ExecutionPlan &executionPlan) {
    parseRangesFile(variableLiveRanges, rangesFilepath);
    parseRegisterFile(executionPlan, registerFilepath);
}

void TxtParser::parseRangesFile(std::map<std::string, std::vector<LiveRange>> &variableLiveRanges, std::string &file) {
    std::ifstream input(file);
    if (!input.is_open()) {
        throw std::runtime_error("Could not open file " + file);
    }
    std::string currLine;
    while (std::getline(input, currLine)) {
        removeTrailingSequence(currLine, " ");
        if (currLine.empty() || currLine[0] == '#') continue;
        std::istringstream iss(currLine);
        std::string varName;
        if (std::getline(iss, varName, ':')) {
            removeTrailingSequence(varName, " ");
            std::string lineAsStr;
            LiveRange liveRange;
            while (std::getline(iss, lineAsStr, ',')) {
                removeTrailingSequence(lineAsStr, " ");
                if (lineAsStr.empty()) continue;
                Line linePoint = parseLine(lineAsStr);
                liveRange.insert(linePoint);
            }
            variableLiveRanges[varName].push_back(liveRange);
        }
    }
}

void TxtParser::parseRegisterFile(ExecutionPlan &executionPlan, std::string &file) {
    std::ifstream input(file);
    if (!input.is_open()) {
        throw std::runtime_error("Could not open file " + file);
    }
    std::string currLine;
    while (std::getline(input, currLine)) {
        removeTrailingSequence(currLine, " ");
        if (currLine.empty() || currLine[0] == '#') continue;
        std::istringstream iss(currLine);
        std::string parameterName;
        while (std::getline(iss, parameterName, ':')) {
            std::string dataStr;
            if (parameterName.find("registers") != std::string::npos) {
                std::getline(iss, dataStr);
                removeTrailingSequence(dataStr, " ");
                getRegisterCount(executionPlan, dataStr);
            }
            else if (parameterName.find("algorithm") != std::string::npos) {
                std::getline(iss, dataStr, ',');
                std::string kValue;
                std::getline(iss, kValue);
                removeTrailingSequence(dataStr, " ");
                removeTrailingSequence(kValue, " ");
                getAlgorithmVariant(executionPlan, dataStr, kValue);
            }
        }
    }
}

void TxtParser::getRegisterCount(ExecutionPlan &executionPlan, std::string &dataStr) {
    int registerCount = getInteger(dataStr);
    // Considering only 0 or other positive integers as -1 registers is invalid
    rejectIfLessThan(registerCount, "Register Count", 0);
    executionPlan.registerCount = registerCount;
}

void TxtParser::getAlgorithmVariant(ExecutionPlan &executionPlan, std::string &dataStr, std::string &kValue) {
    static const std::string validAlgorithms = "basic, splitting k, spilling k";

    if (dataStr == "basic") {
        if (!kValue.empty())
            throw std::domain_error("Algorithm 'basic' does not accept a numeric parameter.");
        executionPlan.algorithmVariant = basic;
        return;
    }

    if (kValue.empty())
        throw std::domain_error("Algorithm '" + dataStr + "' requires a numeric parameter k. Valid: " + validAlgorithms);

    if (dataStr != "splitting" && dataStr != "spilling")
        throw std::domain_error("Unknown algorithm '" + dataStr + "'. Valid: " + validAlgorithms);

    int k = getInteger(kValue);
    rejectIfLessThan(k, "K", 1);
    std::cout << "Register count: " << executionPlan.registerCount << std::endl;
    executionPlan.k = k;
    executionPlan.algorithmVariant = dataStr == "splitting" ? splitting : spilling;
}

Line TxtParser::parseLine(const std::string& lineAsStr ) {
    Line linePoint = {};
    std::string substring = lineAsStr.substr(0, lineAsStr.size() - 1);
    if (lineAsStr.back() == '+') {
        linePoint.type = firstDef;
    }
    else if (lineAsStr.back() == '-') {
        linePoint.type = lastRead;
    }
    else {
        linePoint.type = read;
        substring = lineAsStr; // for read lines, the entire string is the line number since there is no + or - at the end
    }
    linePoint.lineNum = getInteger(substring);
    return linePoint;
}

void TxtParser::removeTrailingSequence(std::string &str, const std::string &s) {
    const size_t start = str.find_first_not_of(s);
    const size_t end = str.find_last_not_of(s);
    if (start == std::string::npos || end == std::string::npos) {
        str = "";
    } else {
        str = str.substr(start, end - start + 1);
    }
}

int TxtParser::getInteger(std::string &str) {
    removeTrailingSequence(str, " ");
    const int id = std::stoi(str);
    return id;
}

void TxtParser::rejectIfLessThan(int val, const std::string& name, int threshold) {
    if (val < threshold)
        throw std::domain_error(name + " must be >= " + std::to_string(threshold) +
                                ". Got: " + std::to_string(val));
}


// TODO: this function is not needed(?)
void TxtParser::rejectIfGreaterThan(int val, const std::string& name, int threshold) {
    if (val > threshold)
        throw std::domain_error(name + " must be <= " + std::to_string(threshold) +
                                ". Got: " + std::to_string(val));
}
