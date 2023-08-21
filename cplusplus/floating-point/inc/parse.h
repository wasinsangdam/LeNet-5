#ifndef __PARSE_H__
#define __PARSE_H__

#include <string>
#include <iostream>
#include <getopt.h>

void arg_parse(int argc, char* argv[], std::string* file_name, bool* print_opt, bool* all_opt); // Parse cmd line

void usage();                                               // Display usage message.
void help();                                                // Display help message.

#endif