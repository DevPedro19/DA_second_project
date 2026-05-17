//
// Created by pedro on 5/4/2026.
//

#ifndef DA_SECOND_PROJECT_EXECUTIONPLAN_H
#define DA_SECOND_PROJECT_EXECUTIONPLAN_H


/**
 * @brief This enum represents the different variants of the register allocation algorithm that can be used in the execution plan.
 */
enum AlgorithmVariant {
    basic,
    splitting,
    spilling,
    freeAlgo
};

/**
 * @brief This struct represents the execution plan for the register allocation algorithm, containing the number of registers available,
 * the variant of the algorithm to be used and the parameter k (if applicable).
 */
struct ExecutionPlan {
    int registerCount;
    AlgorithmVariant algorithmVariant;
    int k;
};

#endif //DA_SECOND_PROJECT_EXECUTIONPLAN_H