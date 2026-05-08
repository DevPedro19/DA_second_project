#include <fstream>
#include <utility>

#include "OutputWriter.h"

OutputWriter::OutputWriter(std::string  outputFileName) : _outputFileName(std::move(outputFileName)) {}

void OutputWriter::writeWebs(std::ofstream& ofs, const Graph& interferenceGraph) {
    ofs << "webs: " << interferenceGraph.getVertexSet().size() << "\n";
    int count = 0;
    for (const auto web : interferenceGraph.getVertexSet()) {
        ofs << "web" << count++ << ": ";
        for (const auto line: web->getInfo().liveWeb) {
            ofs << "" << line.lineNum
                    << (line.type == firstDef ? "+" : (line.type == read ? "" : "-")) << " ";
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

void OutputWriter::writeOutput(const Graph& interferenceGraph, const int registersCount) const {
    std::ofstream ofs(_outputFileName);
    ofs << "# Total number of webs followed by the listing of the program points of each one\n";
    writeWebs(ofs, interferenceGraph);
    ofs << "# Total number of registers used, followed by assignment to webs\n";
    writeRegisters(ofs, interferenceGraph, registersCount);
    ofs.close();
}
