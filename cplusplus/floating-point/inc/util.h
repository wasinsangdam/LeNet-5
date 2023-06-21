#ifndef __UTIL_H__
#define __UTIL_H__


#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

void read_data(std::string file_name, float* array, size_t size);  // Initialize the array by reading the data in the txt file. (input)
void read_answer(std::string file_name, int* array, size_t size);  // Initialize the array by reading the data in the txt file. (answer)

void print_3d(std::string name, float* array, size_t num, size_t row, size_t col, bool flag);   // Print 3D array
void print_1d(std::string name, float* array, size_t num, bool flag);                           // Print 1D array
void print_result(float* array);                                                                // Print result

#endif