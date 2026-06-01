#pragma once

#include <string>

#include "config.h"
#include "program_file.h"

bool runFile(const ProgramFile &file, const std::string &inputFile);

bool runGenFile(const ProgramFile &file, const std::string &inputFile);

bool runAll(const Config &config, const std::string &inputFile);
