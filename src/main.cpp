#include <cstdlib>
#include <iostream>
#include <string>

#include "comparator.h"
#include "compiler.h"
#include "config.h"
#include "file_tools.h"
#include "runner.h"

int main(int argc, char *argv[]) {
    Config config;
    try {
        config = parseInput(argc, argv);
    } catch (...) {
        std::cerr << "Usage: ./stressHub examples/gen.cpp examples/slow.cpp "
                     "examples/fast.cpp countOfTests"
                  << '\n';
        return 1;
    }
    makeHelpDirectories();

    config.gen.executablePath = "tmp/gen";
    config.slow.executablePath = "tmp/slow";
    config.fast.executablePath = "tmp/fast";

    std::string inputFile = "tmp/input.txt";
    config.slow.outputPath = "tmp/" + getFileName(config.slow) + "Output.txt";
    config.fast.outputPath = "tmp/" + getFileName(config.fast) + "Output.txt";

    if (!compileAll(config)) return 1;

    for (int it = 1; it <= config.testCnt; ++it) {
        if (!runAll(config, inputFile)) return 1;

        if (!compareFiles(config.slow.outputPath, config.fast.outputPath)) {  // Found failed test
            saveAndPrintFailedTest(config, inputFile, it);
            return 1;
        } else {
            std::cout << "Test " << it << " : OK\n";
        }
    }
    std::cout << "All tests passed :) \n";
    return 0;
}
