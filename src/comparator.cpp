#include "comparator.h"

#include <fstream>
#include <iostream>

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

bool compareFiles(const std::string file1,
                  const std::string file2) {  // compare the contents of two files
    return readTokens(file1) == readTokens(file2);
}