#include <string>
#include <iostream>

#include "arg_parser.h"


EntryParameters ArgParser::parse(int argc, char** argv)
{
    if (argc <= 1) {
        return default_params();
    }

    std::string arg1(argv[1]);
    if (arg1 == "--help" || arg1 == "-h" || arg1 == "help") {
        std::cout << "Here will be some help..." << std::endl;
        exit(EXIT_SUCCESS);
    }
    // TODO: actual parsing from argv

    return default_params();
}

EntryParameters ArgParser::default_params()
{
    EntryParameters args = { 80, 0.25, 150, 30 };
    return args;
}


