#include <filesystem>
#include <iostream>
#include <vector>

#include "CLI.h"
#include "BasicAlgorithm.h"
#include "GraphColoringStrategy.h"
#include "InfoMenu.h"
#include "OutputWriter.h"
#include "SpillingAlgorithm.h"
#include "TxtParser.h"
#include "WebBuilder.h"
#include "../data_structures/Graph.h"
#include "../data_structures/MutablePriorityQueue.h"

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

void CLI::writeOutput(const Graph& interferenceGraph, const int registersUsed, const std::string& outputFileName) {
    if (!_outputFromBatch) {
        setOutputFileName(outputFileName);
    }
    const OutputWriter outputWriter(outputFileName);
    outputWriter.writeOutput(interferenceGraph, registersUsed);
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

int executeBasicAlgorithm(Graph& interferenceGraph, int maxRegisters, GraphColoringStrategy* strategy) {
    // Execute the algorithm from 1 to registerCount registers
    interferenceGraph.resetColors();
    int regsUsed = 0;
    for (int regCount = 1; regCount <= maxRegisters; regCount++) { // the goal is to find the minimum number of registers needed
        if (strategy->execute(interferenceGraph, regCount)) {
            regsUsed = regCount;
            break; // break the loop as soon the algorithm works
        }
        interferenceGraph.resetColors();
    }
    return regsUsed;
}

//  1. Higher degree
//  2. Higher neighbor degree sum
bool spillingComp(const Vertex& v1, const Vertex& v2) {
    if (v1.getDegree() == v2.getDegree()) {
        return v1.getNeighborDegreeSum() > v2.getNeighborDegreeSum(); // extends on the definition of "difficult-to-color vertex"
    }
    return v1.getDegree() > v2.getDegree();
}

void CLI::execute(const std::vector<std::string> &args) {
    printTitle();
    processArgs(args);

    std::map<std::string, std::vector<LiveRange>> variableLiveRanges;
    ExecutionPlan executionPlan{};
    readInput(_rangesFileName, _registersFileName, variableLiveRanges, executionPlan);

    InfoMenu infoMenu(variableLiveRanges, executionPlan);
    if (infoMenu.display()) {
        std::vector<Web> webs;

        // Collect all webs of every variable
        for (const auto& [varName, liveRanges] : variableLiveRanges) {
            WebBuilder webBuilder(varName, liveRanges); // builds the webs associated with the current variable
            std::vector<Web> variableWebs = webBuilder.buildWebs();

            webs.insert(webs.end(), variableWebs.begin(), variableWebs.end());
        }
        Graph interferenceGraph = Graph(webs);

        // Choose the strategy
        auto* graphColoringStrategy = new GraphColoringStrategy();

        auto* basicAlgorithm = new BasicAlgorithm();
        graphColoringStrategy->setStrategy(basicAlgorithm);

        int regsUsed = executeBasicAlgorithm(interferenceGraph, executionPlan.registerCount, graphColoringStrategy);

        if (regsUsed == 0) { // could not color

            if (executionPlan.algorithmVariant == spilling) {
                MutablePriorityQueue<Vertex> pq(spillingComp);

                for (Vertex* vertex : interferenceGraph.getVertexSet()) {
                    if (vertex->isActive()) pq.insert(vertex);
                }

                for (int spilledRegs = 1; spilledRegs <= executionPlan.k; spilledRegs++) {
                    Vertex* spilledReg = pq.extractMin(); // spill a register
                    spilledReg->disable(); // disable the register node in the graph

                    // update the priority queue
                    for (Edge* edge : spilledReg->getActiveAdj()) {
                        Vertex* neighbor = edge->getDest();
                        pq.decreaseKey(neighbor);
                    }

                    regsUsed = executeBasicAlgorithm(interferenceGraph, executionPlan.registerCount, graphColoringStrategy);
                    if (regsUsed) break; // was possible with 'spilledRegs' spilled registers
                }
            }
        }


        //TODO: output.txt is the current default output file. Also it is going to cmake-build, need to change CMAKElsit
        writeOutput(interferenceGraph, regsUsed, "output.txt");
    }
}
