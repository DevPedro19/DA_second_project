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
 * @param l1 The first line to compare.
 * @param l2 The second line to compare.
 * @return Returns true if the line number of l1 is less than the line number of l2, and false otherwise.
 */
inline bool operator<(const Line& l1, const Line& l2) {
    return l1.lineNum < l2.lineNum;
}


/**
 * @brief Determines if two lines are equal by comparing both their line numbers and their types.
 * @param l1 The fisrt line to compare.
 * @param l2 The second line to compare.
 * @return Returns true if the line number and type of l1 are equal to the line number and type of l2, and false otherwise.
 */
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

    /**
     * @brief Determines if this web interferes with another web, which is the case if their intersection, excluding the line limits of each web, is not empty.
     * @param otherWeb The other web to compare with this web.
     * @return Returns true if this web interferes with the other web, and false otherwise.
     */
    [[nodiscard]] bool interferesWith(const Web& otherWeb) const {
        const int thisBegin = this->getFirstLineNum();
        const int thisEnd = this->getLastLineNum();
        const int otherBegin = otherWeb.getFirstLineNum();
        const int otherEnd = otherWeb.getLastLineNum();

        return otherBegin < thisEnd && otherEnd > thisBegin;
    }

    /**
     * @brief Gets the line number of the first line of the web, which is the line with the smallest line number in the liveWeb set.
     * @return The line number of the first line of the web.
     */
    [[nodiscard]] int getFirstLineNum() const {
        return liveWeb.begin()->lineNum;
    }

    /**
     * @ brief Gets the line number of the last line of the web, which is the line with the greatest line number in the liveWeb set.
     * @return The line number of the last line of the web.
     */
    [[nodiscard]] int getLastLineNum() const {
        return liveWeb.rbegin()->lineNum;
    }
};


/**
 * @brief Determines if a web is lower than another web, by comparing the sorted line numbers of their liveWeb sets. This operator is used to sort the webs by the line number of their first line, and in case of a tie, by the line number of their second line, and so on.
 * @param w1 The first web to compare.
 * @param w2 The second web to compare.
 * @return Returns true if w1 is lower than w2, and false otherwise.
 */
inline bool operator<( const Web& w1, const Web& w2) {
    return w1.liveWeb < w2.liveWeb;
}

/**
 * @brief Determines if two webs are equal by comparing both their variable names and their liveWeb sets.
 * @param w1 The first web to compare.
 * @param w2 The second web to compare.
 * @return Returns true if the variable name and liveWeb of w1 are equal to the variable name and liveWeb of w2, and false otherwise.
 */
inline bool operator==( const Web& w1, const Web& w2) {
    return w1.varName == w2.varName && w1.liveWeb == w2.liveWeb;
}

#endif //DA_SECOND_PROJECT_ALLOCATION_H
