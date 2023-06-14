#include "../inc/util.h"

void read_data(std::string file_name, stream_axis &stream, size_t size) {
    std::fstream fs;

    fs.open(file_name);

    if (!fs.is_open()) {
        std::cout << "Open file failed!\n";
        exit(1);
    }

    axis_t  temp_axi;
    input_t temp_input;

    for (size_t i = 0; i < size; i++) {
        fs >> temp_input;

        temp_axi.data.range() = temp_input.range();

        stream.write(temp_axi);
    }

    fs.close();
}


void read_answer(std::string file_name, int* array, size_t size) {
    std::fstream fs;

    fs.open(file_name);

    if (!fs.is_open()) {
        std::cout << "Open file failed!\n";
        exit(1);
    }

    for (size_t i = 0; i < size; i++) {
        fs >> array[i];
    }

    fs.close();
}


