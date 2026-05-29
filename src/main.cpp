#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>


std::string getFileName(const std::string& file) {
    std::filesystem::path path(file);
    return path.stem().string();
}


bool compileFile(const std::string& file, const std::string& buildName) {
    std::string command = "g++ " + file + " -o " + buildName;
    int code = system(command.c_str());
    if (code != 0) {
        std::cerr << "Compilation failed: " << file << '\n';
        return false;
    }
    return true;
}


bool runFile(const std::string& file, const std::string& buildName, const std::string& outputFile, const std::string& inputFile) {
    std::string command = "./" + buildName + " < " + inputFile + " > " + outputFile;
    int code = system(command.c_str());
    if (code != 0) {
        std::cerr << "Runtime failed: " << file << '\n';
        return false;
    }
    return true;
}


bool runGenFile(const std::string& file, const std::string& buildName, const std::string& inputFile) {
    std::string command = "./" + buildName + " > " + inputFile;
    int code = system(command.c_str());
    if (code != 0) {
        std::cerr << "Runtime failed: " << file << '\n';
        return false;
    }
    return true;
}


std::vector<std::string> readTokens(const std::string& file) {
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


void printFile(const std::string& title, const std::string& file) {
    std::ifstream in(file);

    if (!in) {
        std::cerr << "Failed to open " << file << '\n';
        return; 
    }

    std::cout << title << ": \n";
    std::cout << in.rdbuf() << '\n';
}


int main(int argc, char* argv[]) {
    // ./main gen.cpp slow.cpp fast.cpp testCnt 
    if (argc != 5) {
        std::cerr << "Usage: ./stressHub examples/gen.cpp examples/slow.cpp examples/fast.cpp countOfTests" << '\n';
        return 1;
    }
    std::filesystem::create_directories("tmp");
    // std::filesystem::create_directories("failed_tests");

    std::string genFile = argv[1];
    std::string slowFile = argv[2];
    std::string fastFile = argv[3];
    int testCnt;

    try {
        testCnt = std::stoi(argv[4]);
    } catch (...) {
        std::cerr << "Invalid countOfTests: " << argv[4] << '\n';
        return 1;
    }
    if (testCnt <= 0) {
        std::cerr << "Invalid countOfTests: " << testCnt << '\n';
        return 1;
    }

    std::string inputFile = "tmp/input.txt";
    std::string slowOutputFile = "tmp/" + getFileName(slowFile) + "Output.txt";
    std::string fastOutputFile = "tmp/" + getFileName(fastFile) + "Output.txt";

    std::string failedTestFile = "failed_tests/test.in";
    std::string expected = "failed_tests/expected.out";
    std::string got = "failed_tests/got.out";

    if (!compileFile(genFile, "tmp/gen"))
        return 1;
    if (!compileFile(slowFile, "tmp/slow"))
        return 1;
    if (!compileFile(fastFile, "tmp/fast"))
        return 1;
    

    for (int it = 1; it <= testCnt; ++it) {
        if (!runGenFile(genFile, "tmp/gen", inputFile))
            return 1;
        if (!runFile(slowFile, "tmp/slow", slowOutputFile, inputFile))
            return 1;
        if (!runFile(fastFile, "tmp/fast", fastOutputFile, inputFile))
            return 1;
        
        auto correctAns = readTokens(slowOutputFile);
        auto checkedAns = readTokens(fastOutputFile);

        if (correctAns != checkedAns) { // Found failed test
            std::cout << "Failed at the test " << it << '\n';

             std::string failedTestFile = "failed_tests/test_" + std::to_string(it) + ".in";
            std::string expected = "failed_tests/expected_" + std::to_string(it) + ".out";
            std::string got = "failed_tests/got_" + std::to_string(it) + ".out";


            std::filesystem::copy_file(inputFile,
                failedTestFile,
                std::filesystem::copy_options::overwrite_existing); // copy test to failedTest.txt

            std::filesystem::copy_file(slowOutputFile,
                expected,
                std::filesystem::copy_options::overwrite_existing); // copy correctAns to expected.txt
            
            std::filesystem::copy_file(fastOutputFile,
                got,
                std::filesystem::copy_options::overwrite_existing); // copy checkedAns to got.txt

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

