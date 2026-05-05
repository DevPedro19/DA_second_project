#ifndef DA_SECOND_PROJECT_ALLOCATION_H
#define DA_SECOND_PROJECT_ALLOCATION_H

#include <string>
#include <set>

enum LineType {
    firstDef,
    read,
    lastRead,
};

struct Line {
    int lineNum;
    LineType type;
};

typedef std::set<Line> LiveRange;

struct Web {
    std::string varName;    // ex: "i", "sum"
    LiveRange liveWeb;      // == merge(liveRanges[varName])
};

#endif //DA_SECOND_PROJECT_ALLOCATION_H
