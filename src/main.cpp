#include <iostream>

#include "WebBuilder.h"

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


WebBuilder webBuilder("i", liveRanges3);

int main() {
    std::vector<Web> webs = webBuilder.buildWebs();

    for (const Web& web : webs) {
        std::cout << web.varName << ": ";
        for (const Line& line : web.liveWeb) {
            std::cout << line.lineNum << (line.type == firstDef ? "+" : line.type == lastRead ? "-" : "") << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
