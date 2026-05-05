#ifndef DA_SECOND_PROJECT_ALLOCATION_H
#define DA_SECOND_PROJECT_ALLOCATION_H

#include <string>
#include <set>
#include <iostream>

/**
 * @brief Represents the type of line in a live range, which can be either the first definition of a variable's value (firstDef), a read of that value that is not the last (read), or the last read of the value (lastRead). In the input files, '+' represents a line of type firstDef, '-' represents a line of type lastRead and any line that is not marked with '+' or '-' is of type read.
 */
enum LineType {
    firstDef,
    read,
    lastRead,
};

/**
 * @brief Represents a line in a live range, which is defined by its line number and its type (firstDef, read or lastRead).
 */
struct Line {
    int lineNum;
    LineType type;
};

/**
 * @brief Compares two lines by their line numbers, without taking into consideration the type of the line, to make the comparison restricted to the line numbers.
 * @param l1
 * @param l2
 * @return
 */
inline bool operator<(const Line& l1, const Line& l2) {
    return l1.lineNum < l2.lineNum;
}

inline bool operator==(const Line& l1, const Line& l2) {
    return l1.lineNum == l2.lineNum && l1.type == l2.type;
}

/**
 * @brief Represents a live range, which is a set of lines where a variable is alive. It is represented as a set of Line structs, which are ordered by their line numbers (without taking into consideration the type of the line).
 */
typedef std::set<Line> LiveRange;


/**
 * @brief Represents a web, which is the union of the live ranges of a variable, should they overlap at least in one line.
 */
struct Web {
    /**
     * @brief The name of the variable for relative to the web.
     */
    std::string varName;

    /**
        * @brief The live web of the variable, which is the union of all its live ranges, should they overlap at least in one line. It is represented as a set of Line structs, and for that reason, these are sorted in ascending order by their line numbers (due to the operator< overload for Line struct).
        */
    std::set<Line> liveWeb;


    [[nodiscard]] bool interferesWith(const Web& otherWeb) const {
        const int thisBegin = this->liveWeb.begin()->lineNum;
        const int thisEnd = this->liveWeb.rbegin()->lineNum;
        const int otherBegin = otherWeb.liveWeb.begin()->lineNum;
        const int otherEnd = otherWeb.liveWeb.rbegin()->lineNum;

        return otherBegin < thisEnd && otherEnd > thisBegin;
    }

    [[nodiscard]] Line getFirstLine() const {
        return *liveWeb.begin();
    }

    [[nodiscard]] Line getLastLine() const {
        return *liveWeb.rbegin();
    }
};

inline bool operator<( const Web& w1, const Web& w2) {
    return w1.liveWeb < w2.liveWeb;
}

inline bool operator==( const Web& w1, const Web& w2) {
    return w1.varName == w2.varName && w1.liveWeb == w2.liveWeb;
}

#endif //DA_SECOND_PROJECT_ALLOCATION_H
