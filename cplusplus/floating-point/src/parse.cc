#include "../inc/parse.h"

void arg_parse(int argc, char* argv[], std::string* file_name, bool* print_opt, bool* all_opt) {

    int c;

    static struct option long_options[] = {
        {"input", required_argument , 0, 'i'},
        {"print", no_argument       , 0, 'p'},
        {"all"  , no_argument       , 0, 'a'},
        {"help" , no_argument       , 0, 'h'}
    };

    int option_index = 0;

    // No argument
    if (argc < 2) {
        usage();
        help();
        exit(0);
    }

    while ((c = getopt_long(argc, argv, "i:pa", long_options, &option_index)) != -1) {
        switch (c) {
            case 'i' :
                if (optarg) {
                    std::string optarg_s(optarg);
                    *file_name = optarg_s;
                }
                break;
            case 'p' :
                *print_opt = true;
                break;
            case 'a' :
                *all_opt = true;
                break;
            case 'h' :
                usage();
                help();
                exit(0);
                break;
            case '?' :
                usage();
                help();
                exit(0);
                break;
            default : 
                usage();
                help();
                exit(0);
                break;
        }
    }
}


void usage() {
    std::cout << "[Run one input]\n";
    std::cout << "Usage : ./main --input [input.data]\n";
    std::cout << "        ./main -i [input.data]\n\n";

    std::cout << "[Run one input with print option]\n";
    std::cout << "Usage : ./main --input [input.data] --print\n";
    std::cout << "        ./main -i [input.data] -p\n\n";

    std::cout << "[Run all inputs]\n";
    std::cout << "Usage : ./main --all \n";
    std::cout << "        ./main -a n\n";
}

void help() {
    std::cout << "--input [input] | -i [input]  \t File name to run.\n";
    std::cout << "                              \t [input] must be txt file.\n";
    std::cout << "                              \t This option requires argument.\n\n";

    std::cout << "--print | -p                  \t Determine whether to print intermediate result.\n";
    std::cout << "                              \t This option is optional.\n\n";

    std::cout << "--all | -a                    \t Determine whether run all test cases.\n";
    std::cout << "                              \t This option is optional.\n\n";

    std::cout << "--help | -h                   \t Display this information.\n";
}
