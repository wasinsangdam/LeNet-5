#include <iostream>
#include <fstream>
#include <string>

#include "predict.h"

#define N 3

void read_data(std::string file_name, axis_input &axis_input, input_t* array, size_t size) {
    std::fstream fs;

    fs.open(file_name);

    if (!fs.is_open()) {
        std::cout << "Open file failed!\n";
        exit(1);
    }

    axis_i temp;

    for (size_t i = 0; i < size; i++) {
        fs >> array[i];

        temp.data = array[i].range();

        axis_input.write(temp);
    }

    fs.close();
}

int main (void) {
    
    std::string input_name;

    axis_input axis;

    uint8_t output;


    input_t input_array[IMAGE_SIZE] = { 0.0, };

    for (int i = 0; i < N; i++) {
        std::string dir   = "C:\\LeNet-5\\unroll\\input\\";
        std::string input = "input_";
        std::string num   = std::to_string(i);
        std::string ext   = ".data";

        std::string file  = dir + input + num + ext;

        read_data(file, axis, input_array, IMAGE_SIZE);

        predict(axis, &output);

        std::cout << (int)output << "\n";

    }



    return 0;
}
