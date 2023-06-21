#ifndef __UTIL_H__
#define __UTIL_H__


#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include "type.h"

void read_data(std::string file_name, stream_axis &input_stream, size_t size); // Initialize the array by reading the data in the txt file. (input)
void read_answer(std::string file_name, int* array, size_t size);              // Initialize the array by reading the data in the txt file. (answer)


#endif