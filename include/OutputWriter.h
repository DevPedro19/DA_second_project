#ifndef DA_SECOND_PROJECT_OUTPUTWRITER_H
#define DA_SECOND_PROJECT_OUTPUTWRITER_H
#include <string>

#include "ExecutionPlan.h"
#include "../data_structures/Graph.h"

/**
 * @brief Class responsible for writing the output of the algorithm in to a text file.
 */
class OutputWriter {
public:
    /**
     * @brief Constructor of the class with a specified output filename.
     * @param outputFileName the name output file.
     */
    OutputWriter(const std::string& outputFileName);

    /**
     * @brief Write the output of the algorithm to the output file. The output includes the total number of webs, the program points of each web, the total number of registers used and the assignment of registers to webs.
     * @param interferenceGraph the interference graph containing the webs and their assigned colors (registers).
     * @param registersCount the number of registers (colors) used to color the graph.
     * @param spilledRegisters the number of spilled registers.
     */
    void writeOutput(const Graph& interferenceGraph, const ExecutionPlan& executionPlan, int registersCount) const;

private:
    /**
     * @brief Writes web information. Total number of webs and the program points of each web.
     * @param ofs the output file stream to write to.
     * @param interferenceGraph the interference graph containing the webs and their assigned colors (registers).
     */
    static void writeWebs(std::ofstream& ofs, const Graph& interferenceGraph);

    static void writeSplit(std::ofstream& ofs);

    /**
     * @biref
     * @param ofs the output file stream to write to.
     * @param interferenceGraph the interference graph containing the webs and their assigned colors (registers).
     * @param registersCount total number of registers(colors) used.
     */
    static void writeRegisters(std::ofstream& ofs, const Graph& interferenceGraph, const int registersCount );

    /**
     * @brief The name of the output file to be written.
     */
    std::string _outputFileName;
};

#endif //DA_SECOND_PROJECT_OUTPUTWRITER_H
