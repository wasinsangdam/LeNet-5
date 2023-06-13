#include "../inc/parse.h"

void arg_parse(int argc, char* argv[], std::string* file_name, bool* print_opt, bool* all_opt) {

    std::string argv1;
    std::string argv2;

    if (argc == 2) 
        argv1 = argv[1];
    else if (argc == 3) {
        argv1 = argv[1];
        argv2 = argv[2];
    }

    std::string str_help = "--help";
    std::string str_h    = "-h";

    std::string str_all = "--all";
    std::string str_a   = "-a";

    std::string str_input = "--input";
    std::string str_i     = "-i";

    std::string str_print = "--print";
    std::string str_p     = "-p";

    switch (argc) {
        // No argument
        case 1 : {
            usage();
            help();
            exit(0);

            break;
        }
        // 1 argument
        case 2 : {

            if (argv1 == str_help || argv1 == str_h) {
                usage();
                help();
                exit(0);
            }

            else if (argv1.find(str_all) != std::string::npos) {
                check_all(argv1, all_opt);
            }
            else if (argv1.find(str_a)   != std::string::npos) {
                check_all(argv1, all_opt);
            }

            else if (argv1.find(str_input) != std::string::npos) {
                check_file(argv1, file_name);
                *print_opt = false;
            }
            else if (argv1.find(str_i)     != std::string::npos) {
                check_file(argv1, file_name);
                *print_opt = false;
            }

            break;
        }
        // 2 arguments
        case 3 : {

            check_file(argv1, file_name);
            check_print(argv2, print_opt);

            break;
        }

        // No more possibility
        default : {
            usage();
            help();

            break;
        }

    }

}

void usage() {
    std::cout << "[Run one input]\n";
    std::cout << "Usage : ./main --input=[input.data]\n";
    std::cout << "        ./main -i=[input.data]\n\n";

    std::cout << "[Run one input with print option]\n";
    std::cout << "Usage : ./main --input=[input.data] --print=[bool]\n";
    std::cout << "        ./main -i=[input.data] -p=[bool]\n\n";

    std::cout << "[Run all inputs]\n";
    std::cout << "Usage : ./main --all=[bool]\n";
    std::cout << "        ./main -a=[bool]\n\n";
}

void help() {
    std::cout << "--input=[input] | -i=[input]  \t File name to run.\n";
    std::cout << "                              \t [input] must be txt file.\n";
    std::cout << "                              \t Extension must be *.data.\n";
    std::cout << "                              \t This option is required.\n\n";

    std::cout << "--print=[bool] | -p=[bool]    \t Determine whether to print intermediate result.\n";
    std::cout << "                              \t [bool] must be true or false with small letters.\n";
    std::cout << "                              \t This option is optional.\n\n";

    std::cout << "--all=[bool] | -a=[bool]      \t Determine whether run all test cases.\n";
    std::cout << "                              \t [bool] must be true or false with small letters.\n";
    std::cout << "                              \t This option is optional.\n\n";

    std::cout << "--help | -h                   \t Display this information.\n";
}

bool check_data(std::string arg) {
    if (arg.substr(arg.size() - 4, arg.size()) == "data")
        return true;
    else
        return false;
}

void check_file(std::string arg, std::string* file_name) {
    std::string opt_input = "--input=";
    std::string opt_i     = "-i=";

    // if data file exists with long option
    if (arg.find(opt_input) != std::string::npos) {
        arg = arg.substr(opt_input.size());

        if (check_data(arg)) {
            file_name->append(arg);
        }
        else {
            usage();
            help();
        }
    }
    // if data file exists with short option
    else if (arg.find(opt_i) != std::string::npos) {
        arg = arg.substr(opt_i.size());

        if (check_data(arg)) {
            file_name->append(arg);
        }
        else {
            usage();
            help();
        }
    }
    // No other possibility
    else {
        usage();
        help();
    }
}


void check_print(std::string arg, bool* print_opt) {
    std::string opt_print = "--print=";
    std::string opt_p     = "-p=";
    std::string opt_true  = "true";
    std::string opt_false = "false";

    // if print option exists with long option
    if (arg.find(opt_print) != std::string::npos) {
        arg = arg.substr(opt_print.size());

        if (arg == opt_true)
            *print_opt = true;
        else
            *print_opt = false;

    }
    // if print option exits with short option
    else if (arg.find(opt_p) != std::string::npos) {
        arg = arg.substr(opt_p.size());

        if (arg == opt_true)
            *print_opt = true;
        else
            *print_opt = false;
    }
    // No other possibility
    else {
        usage();
        help();
    }
}

void check_all(std::string arg, bool* all_opt) {
    std::string opt_all   = "--all=";
    std::string opt_a     = "-a=";
    std::string opt_true  = "true";
    std::string opt_false = "false";

    // if print option exists with long option
    if (arg.find(opt_all) != std::string::npos) {
        arg = arg.substr(opt_all.size());

        if (arg == opt_true)
            *all_opt = true;
        else
            *all_opt = false;

    }
    // if print option exits with short option
    else if (arg.find(opt_a) != std::string::npos) {
        arg = arg.substr(opt_a.size());

        if (arg == opt_true)
            *all_opt = true;
        else
            *all_opt = false;
    }
    // No other possibility
    else {
        usage();
        help();
    }

}