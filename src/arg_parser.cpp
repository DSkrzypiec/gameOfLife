#include <string>
#include <iostream>

#include "arg_parser.h"


// Parses entry parameters from command line arguments.
EntryParameters ArgParser::parse(int argc, char** argv)
{
    if (argc <= 1) {
        return default_params();
    }

    std::string arg1(argv[1]);
    if (arg1 == "--help" || arg1 == "-h" || arg1 == "help") {
        print_help();
        exit(EXIT_SUCCESS);
    }

    if (argc < 5) {
        std::cout << "Expected at least 4 arguments. Check --help" << std::endl;
        exit(EXIT_SUCCESS);
    }

    return parse_and_valid(argv);
}

EntryParameters ArgParser::default_params()
{
    EntryParameters args = { 80, 0.15, 250, 30 };
    return args;
}


EntryParameters ArgParser::parse_and_valid(char** argv)
{
    auto def_params = default_params();
    int grid_size = std::atoi(argv[1]);
    double alive_perc = std::stod(argv[2]);
    int ref_milli = std::atoi(argv[3]);
    int timeout = std::atoi(argv[4]);

    if (grid_size <= 5 || grid_size > 300) {
        std::cout << "Grid out of bounds. Default configuration is taken." << std::endl;
        return def_params;
    }

    if (alive_perc <= 0.0 || alive_perc >= 1.0) {
        std::cout << "alive_percent should be from (0.0, 1.0) range. Default configuration is taken" << std::endl;
        return def_params;
    }

    if (ref_milli <= 30) {
        std::cout << "refresh_milliseconds cannot be lower than 30ms. Default configuration is taken" << std::endl;
        return def_params;
    }

    if (timeout <= 0) {
        std::cout << "timeout_seconds cannot be non posistive. Default configuration is taken" << std::endl;
        return def_params;
    }

    EntryParameters ep = { grid_size, alive_perc, ref_milli, timeout };
    return ep;
}

void ArgParser::print_help()
{
    auto defaultParams = default_params();

    std::cout << std::endl;
    std::cout << "Program GameOfLife by Damian Skrzypiec." << std::endl;
    std::cout << "The following list of arguments is supported:" << std::endl;
    std::cout << "    -grid_size: Size of the grid (default = " << 
        defaultParams.grid_size << ")" << std::endl;
    std::cout << "    -alive_percent: Percent of alive cells (default = " <<
        defaultParams.alive_percent << ")" << std::endl;
    std::cout << "    -refresh_milliseconds: Frame refreshing time (default = " <<
        defaultParams.refresh_milliseconds << ")" << std::endl;
    std::cout << "    -timeout_seconds: Global timeout (default = " <<
        defaultParams.timeout_seconds << ")" << std::endl;

    std::cout << std::endl;
    std::cout << "All or none arguments shall be provided. Example:" << std::endl;
    std::cout << "./gameOfLife" << std::endl;
    std::cout << "./gameOfLife 90 0.45 50 120" << std::endl;
}
