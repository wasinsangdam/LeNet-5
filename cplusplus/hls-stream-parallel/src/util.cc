#include "../inc/util.h"

void read_data(std::string file_name, axis_input &axis, input_t* array, size_t size) {
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

        axis.write(temp);
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


