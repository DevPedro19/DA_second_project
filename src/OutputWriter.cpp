#include <fstream>
#include <utility>

#include "OutputWriter.h"

#include <filesystem>

#include "ExecutionPlan.h"

OutputWriter::OutputWriter(const std::string&  outputFileName) : _outputFileName("output/" + outputFileName) {
    const std::string outputDirectoryName = "output";
    // Create directory
    std::filesystem::create_directory(outputDirectoryName);
}

void OutputWriter::writeWebs(std::ofstream& ofs, const Graph& interferenceGraph) {
    ofs << "webs: " << interferenceGraph.getVertexSet().size() << "\n";
    int count = 0;
    for (const auto web : interferenceGraph.getVertexSet()) {
        ofs << "web" << count++ << ": ";
        for (const auto line: web->getInfo().liveWeb) {
            ofs << "" << line.lineNum
                    << (line.type == firstDef ? "+" : (line.type == active ? "" : "-")) << " ";
        }
        ofs << "\n";
    }
}

void OutputWriter::writeRegisters(std::ofstream& ofs, const Graph& interferenceGraph, const int registersCount) {
    ofs << "registers: " << registersCount << "\n";
    int count = 0;
    for (const auto web : interferenceGraph.getVertexSet()) {
        int color = web->getColor();
        if (color != -1 && web->isActive()) { // colored and not spilled
            ofs << "r" << color << ": ";
        } else {
            ofs << "M: ";
        }
        ofs << "web" << count++ << "\n";
    }
}

void OutputWriter::writeSplit(std::ofstream& ofs) {
    std::set<int> memLines;

    for (const auto& webSplit : Graph::getSplitWebsMap()) {
        ofs << "web " << webSplit.first.varName << " [" << webSplit.first.getFirstLineNum() << "," << webSplit.first.getLastLineNum() << "] ->";
        if (!webSplit.second.second.first.getWeb().empty()) {
            ofs << " ["<< webSplit.second.second.first.getFirstLineNum() << " " << webSplit.second.second.first.getLastLineNum() << "]";
        }
        if (!webSplit.second.second.second.getWeb().empty()) {
            ofs << " ["<< webSplit.second.second.second.getFirstLineNum() << " " << webSplit.second.second.second.getLastLineNum() << "]";
        }
        ofs << " | mem ]" << webSplit.second.first.first.lineNum << " " << webSplit.second.first.second.lineNum << "[";
        ofs << "\n";
    }
}

void OutputWriter::writeOutput(const Graph& interferenceGraph, const ExecutionPlan& executionPlan, const int registersCount) const {
    std::ofstream ofs(_outputFileName);
    if (executionPlan.algorithmVariant == spilling) {
        ofs << "Spilling: " << interferenceGraph.getSpilledWebsNumber() << "\n";
    }

    if (executionPlan.algorithmVariant == splitting || executionPlan.algorithmVariant == freeAlgo) {
        ofs << "Split: " << Graph::getSplitWebsMap().size() << "\n";
        writeSplit(ofs);
    }

    ofs << "# Total number of webs followed by the listing of the program points of each one\n";
    writeWebs(ofs, interferenceGraph);
    ofs << "# Total number of registers used, followed by assignment to webs\n";
    writeRegisters(ofs, interferenceGraph, registersCount);
    ofs.close();
}
