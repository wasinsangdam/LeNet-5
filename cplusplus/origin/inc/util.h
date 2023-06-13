#ifndef __UTIL_H__
#define __UTIL_H__


#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

void read_data(std::string file_name, float* array, size_t size);
void read_answer(std::string file_name, int* array, size_t size);

#endif