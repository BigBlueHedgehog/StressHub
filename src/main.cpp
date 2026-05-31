#include "config.h"
#include "compiler.h"
#include "runner.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


std::string getFileName(const ProgramFile &file) {
    std::filesystem::path path(file.path);
    return path.stem().string();
}




std::vector<std::string> readTokens(const std::string &file) {
    std::ifstream in(file);
    std::vector<std::string> tokens;
    if (!in) {
        std::cerr << "Failed to open " << file << '\n';
        return tokens;
    }
    std::string token;
    while (in >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

void printFile(const std::string &title, const std::string &file) {
    std::ifstream in(file);

    if (!in) {
        std::cerr << "Failed to open " << file << '\n';
        return;
    }

    std::cout << title << ": \n";
    std::cout << in.rdbuf() << '\n';
}

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
    config.gen.executablePath = "tmp/gen";
    config.slow.executablePath = "tmp/slow";
    config.fast.executablePath = "tmp/fast";

    std::filesystem::create_directories("tmp");

    

    std::string inputFile = "tmp/input.txt";
    std::string slowOutputFile = "tmp/" + getFileName(config.slow) + "Output.txt";
    std::string fastOutputFile = "tmp/" + getFileName(config.fast) + "Output.txt";

    std::string failedTestFile;
    std::string expected;
    std::string got;

    

    if (!compileFile(config.gen)) return 1;
    if (!compileFile(config.slow)) return 1;
    if (!compileFile(config.fast)) return 1;

    for (int it = 1; it <= config.testCnt; ++it) {
        if (!runGenFile(config.gen, inputFile)) return 1;
        if (!runFile(config.slow, slowOutputFile, inputFile)) return 1;
        if (!runFile(config.fast, fastOutputFile, inputFile)) return 1;

        auto correctAns = readTokens(slowOutputFile);
        auto checkedAns = readTokens(fastOutputFile);

        if (correctAns != checkedAns) {  // Found failed test
            std::cout << "Failed at the test " << it << '\n';

            std::string failedTestFile = "failed_tests/test_" + std::to_string(it) + ".in";
            std::string expected = "failed_tests/expected_" + std::to_string(it) + ".out";
            std::string got = "failed_tests/got_" + std::to_string(it) + ".out";

            std::filesystem::copy_file(
                inputFile, failedTestFile,
                std::filesystem::copy_options::overwrite_existing);  // copy test to
                                                                     // failedTest.txt

            std::filesystem::copy_file(
                slowOutputFile, expected,
                std::filesystem::copy_options::overwrite_existing);  // copy correctAns
                                                                     // to expected.txt

            std::filesystem::copy_file(
                fastOutputFile, got,
                std::filesystem::copy_options::overwrite_existing);  // copy checkedAns
                                                                     // to got.txt

            printFile("Input", failedTestFile);
            printFile("Expected", expected);
            printFile("Got", got);

            return 1;
        } else {
            std::cout << "Test " << it << " : OK\n";
        }
    }
    std::cout << "All tests passed :) \n";
    return 0;
}
