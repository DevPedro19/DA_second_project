#include "WebBuilder.h"

#include <iostream>

#include "../data_structures/Graph.h"


std::vector<LiveRange> liveRanges1 = {
    {{1, firstDef}, {2, read}, {3, read}, {4, read}, {7, read}},
    {{7, read}, {8, lastRead}},
    {{8, firstDef}, {9, lastRead}},
    {{8, read}, {11, read}, {12, read}, {13, lastRead}}
};

std::vector<LiveRange> liveRanges2 = {
    {{1, firstDef}, {2, lastRead}},
    {{2, firstDef}, {8, lastRead}},
    {{7, firstDef}, {9, lastRead}},
    {{8, firstDef}, {11, read}, {12, read}, {13, lastRead}}
};


std::vector<LiveRange> liveRanges3 = {
    {{1, firstDef}, {2, read}, {3, read}, {4, read}, {5, read}, {6, lastRead}},
    {{9, firstDef}, {10, read}, {11, read}, {12, lastRead}},
    {{12, firstDef}, {13, read}, {14, lastRead}},
    {{20, firstDef}, {11, read}, {12, lastRead}}
};

std::vector<LiveRange> liveRanges4 = {
    {{7, firstDef}, {8, read}, {9, read}, {10, lastRead}}
};


int main(const int argc, const char *argv[]) {

    WebBuilder webBuilderI("i", liveRanges3);
    WebBuilder webBuilderSum("sum", liveRanges4);

    std::vector<Web> websA = webBuilderI.buildWebs();
    std::vector<Web> websSum = webBuilderSum.buildWebs();

    std::cout << "Webs:" << std::endl;
    for (const Web& web : websA) {
        std::cout << web.varName << ": ";
        for (const Line& line : web.liveWeb) {
            std::cout << line.lineNum << (line.type == firstDef ? "+" : (line.type == lastRead ? "-" : "")) << " ";
        }
        std::cout << std::endl;
    }

    for (const Web& web : websSum) {
        std::cout << web.varName << ": ";
        for (const Line& line : web.liveWeb) {
            std::cout <<  line.lineNum << (line.type == firstDef ? "+" : (line.type == lastRead ? "-" : "")) << " ";
        }
        std::cout << std::endl;
    }

    std::vector<Web> websCombined;
    websCombined.insert(websCombined.end(), websA.begin(), websA.end());
    websCombined.insert(websCombined.end(), websSum.begin(), websSum.end());
    Graph graph(websCombined);

    return 0;
}
