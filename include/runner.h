#pragma once

#include <program_file.h>

#include <string>


bool runFile(const ProgramFile& file, const std::string &outputFile,
             const std::string &inputFile);

bool runGenFile(const ProgramFile& file,
                const std::string &inputFile);

