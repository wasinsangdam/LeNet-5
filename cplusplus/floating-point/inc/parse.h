#ifndef __PARSE_H__
#define __PARSE_H__

#include <string>
#include <iostream>

void arg_parse(int argc, char* argv[], std::string* file_name, bool* print_opt, bool* all_opt); // Parse cmd line

void usage();                                               // Display usage message.
void help();                                                // Display help message.
bool check_data(std::string arg);                           // Make sure the extension is .data.
void check_file(std::string arg, std::string* file_name);   // Check input file.
void check_print(std::string arg, bool* point_opt);         // Check if it is a print option.
void check_all(std::string arg, bool* all_opt);             // Check if it is a all option.

#endif