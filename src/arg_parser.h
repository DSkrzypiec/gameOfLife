
struct EntryParameters
{
    int grid_size;
    double alive_percent;
    int refresh_milliseconds;
    int timeout_seconds;
};

class ArgParser
{
public:
    EntryParameters parse(int argc, char** argv);
private:
    EntryParameters default_params();
    void print_help();
    EntryParameters parse_and_valid(char** argv);
};
