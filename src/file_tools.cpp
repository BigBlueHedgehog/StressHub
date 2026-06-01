#include "file_tools.h"

#include <filesystem>
#include <fstream>
#include <iostream>

void makeHelpDirectories() {
    std::filesystem::create_directories("tmp");
    std::filesystem::create_directories("failed_tests");
}

std::string getFileName(const ProgramFile& file) {
    std::filesystem::path path(file.path);
    return path.stem().string();
}

void printFile(const std::string& title, const std::string& file) {
    std::ifstream in(file);

    if (!in) {
        std::cerr << "Failed to open " << file << '\n';
        return;
    }

    std::cout << title << ": \n";
    std::cout << in.rdbuf() << '\n';
}

void copyFile(const std::string& file1, const std::string& file2) {
    std::filesystem::copy_file(file1, file2, std::filesystem::copy_options::overwrite_existing);
}

void saveAndPrintFailedTest(const Config& config, const std::string& inputFile, int numberOfTest) {
    std::cout << "Failed at the test " << numberOfTest << '\n';

    std::string failedTestFile = "failed_tests/test_" + std::to_string(numberOfTest) + ".in";
    std::string expected = "failed_tests/expected_" + std::to_string(numberOfTest) + ".out";
    std::string got = "failed_tests/got_" + std::to_string(numberOfTest) + ".out";

    // Save outputs
    copyFile(inputFile, failedTestFile);
    copyFile(config.slow.outputPath, expected);
    copyFile(config.fast.outputPath, got);

    // print outputs
    printFile("Input", failedTestFile);
    printFile("Expected", expected);
    printFile("Got", got);
}