#ifndef __UTIL_H__
#define __UTIL_H__


#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

void read_data(std::string file_name, float* array, size_t size);
void print_3d(std::string name, float* array, size_t num, size_t row, size_t col, bool flag);
void print_1d(std::string name, float*array, size_t num, bool flag);
void print_result(float* array);
void read_answer(std::string file_name, int* array, size_t size);

#endif