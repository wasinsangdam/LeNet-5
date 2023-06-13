#include <iostream>
#include <fstream>
#include <string>

#define NUM         10000
#define IMAGE_SIZE  32 * 32

using namespace std;

void read_data(string file_name, float* array, size_t size) {
    std::fstream fs;

    fs.open(file_name);

    if (!fs.is_open()) {
        cout << "Open file failed! [READ]\n";
        exit(1);
    }

    for (size_t i = 0; i < size; i++) {
        fs >> array[i];
    }
}

void write_data_bin(string file_name, float* array, size_t size) {
    std::ofstream fs;

    fs.open(file_name, ios::out | ios::binary);

    if (!fs.is_open()) {
        cout << "Open file failed! [WRITE]\n";
        exit(1);
    }

    fs.write(reinterpret_cast<const char*>(array), size * sizeof(float));

    fs.close();
}

int main (void) {

    float** input = new float*[NUM];

    for (size_t i = 0; i < NUM; i++) {
        input[i] = new float[IMAGE_SIZE];
    }

    string dir_input = "../../../data/input/input_";
    string dir_output = "../../../data/input_fp_bin/fp_";

    string ext_input = ".data";
    string ext_output = ".bin";

    for (size_t i = 0; i < NUM; i++) {
        string num = to_string(i);
        string file = dir_input + num + ext_input;

        read_data(file, input[i], IMAGE_SIZE);
    }

    for (size_t i = 0 ; i < NUM; i++) {
        string num = to_string(i);
        string file = dir_output + num + ext_output;

        write_data_bin(file, input[i], IMAGE_SIZE);
    }

    for (size_t i =0 ; i < NUM; i++) {
        delete[] input[i];
    }

    delete[] input;

    return 0;
}