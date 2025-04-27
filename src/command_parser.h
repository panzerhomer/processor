#pragma once
#include <memory>
#include "filter.h"

class CommandParser {
public:
    void Parse(int argc, char* argv[]);
        
    void PrintHelp();

    std::string GetSourceFile();
    std::string GetDestanationFile();
    std::vector<std::unique_ptr<IFilter>> GetFilters();

private:
    std::string srcFile_;
    std::string destFile_;
    std::vector<std::unique_ptr<IFilter>> filters_;  
};