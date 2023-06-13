#ifndef __PARSE2_H__
#define __PARSE2_H__

#include <string>
#include <iostream>

void arg_parse(int argc, char* argv[], std::string* file_name, bool* print_opt, bool* all_opt);
void usage();
void help();
bool check_data(std::string arg);
void check_file(std::string arg, std::string* file_name);
void check_print(std::string arg, bool* point_opt);
void check_all(std::string arg, bool* all_opt);

#endif