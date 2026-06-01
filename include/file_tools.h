#pragma once

#include <string>

#include "config.h"
#include "program_file.h"

void makeHelpDirectories();

std::string getFileName(const ProgramFile& file);

void printFile(const std::string& title, const std::string& file);

void copyFile(const std::string& file1, const std::string& file2);  // copy file1 to file2

void saveAndPrintFailedTest(const Config& config, const std::string& inputFile, int numberOfTest);
