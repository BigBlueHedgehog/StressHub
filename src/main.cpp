#include <cstdlib>
#include <iostream>
#include <string>

#include "comparator.h"
#include "compiler.h"
#include "config.h"
#include "file_tools.h"
#include "runner.h"

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; ++i) {
        if (std::string(argv[i]) == "--help") {
            std::cout << "Usage: ./stressHub examples/gen.cpp examples/slow.cpp "
                         "examples/fast.cpp countOfTests [options]\n"
                      << "Options: \n"
                      << "  --seed <value>    Set generator seed\n"
                      << "  --help            Show this help message\n";
            return 0;
        }
    }
    Config config;
    try {
        config = parseInput(argc, argv);
    } catch (...) {
        std::cerr << "Usage: ./stressHub examples/gen.cpp examples/slow.cpp "
                     "examples/fast.cpp countOfTests [options]\n"
                  << "Print \"./stressHub --help\" to see all options\n";
        return 1;
    }
    makeHelpDirectories();

    config.gen.executablePath = "tmp/gen";
    config.slow.executablePath = "tmp/slow";
    config.fast.executablePath = "tmp/fast";

    std::string inputFile = "tmp/input.txt";
    config.slow.outputPath = "tmp/expected.out";
    config.fast.outputPath = "tmp/got.out";

    if (!compileAll(config)) return 1;

    for (int test_number = 1; test_number <= config.testCnt; ++test_number) {
        if (!runAll(config, inputFile, test_number)) return 1;

        if (!compareFiles(config.slow.outputPath, config.fast.outputPath)) {  // Found failed test
            saveAndPrintFailedTest(config, inputFile, test_number);
            std::cout << "Seed " << config.seed << '\n';
            std::cout << "Seed of the failed test is: " << config.seed + test_number
                      << " = seed + test_number" << '\n';
            std::cout << "If you want to check only this test again, run with countOfTests = 1 and "
                         "seed = "
                      << config.seed + test_number - 1 << '\n';
            return 1;
        } else {
            std::cout << "Test " << test_number << " : OK\n";
        }
    }
    std::cout << "All tests passed :) \n";
    return 0;
}
