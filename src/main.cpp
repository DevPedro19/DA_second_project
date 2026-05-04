#include "CLI.h"

#include <iostream>

int main(const int argc, const char *argv[]) {
    const std::vector<std::string> args(argv, argv + argc);
    try {
        CLI cli;
        cli.execute(args);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
