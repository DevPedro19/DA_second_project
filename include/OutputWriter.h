#ifndef DA_SECOND_PROJECT_OUTPUTWRITER_H
#define DA_SECOND_PROJECT_OUTPUTWRITER_H
#include <string>

#include "../data_structures/Graph.h"

class OutputWriter {
public:
    OutputWriter(std::string  outputFileName);

    void writeOutput(const Graph& interferenceGraph, int registersCount) const;

private:
    static void writeWebs(std::ofstream& ofs, const Graph& interferenceGraph);

    static void writeRegisters(std::ofstream& ofs, const Graph& interferenceGraph, const int registersCount );

    std::string _outputFileName;
};

#endif //DA_SECOND_PROJECT_OUTPUTWRITER_H
