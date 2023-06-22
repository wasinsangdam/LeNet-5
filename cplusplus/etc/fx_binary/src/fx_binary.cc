#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <iomanip>

#include <ap_fixed.h>

typedef ap_ufixed<16, 1, AP_RND, AP_SAT> input_t;

#define NUM         10000
#define IMAGE_SIZE  32 *32

using namespace std;


void read_data(string file_name, input_t* array, size_t size) {

    std::fstream fs;

    fs.open(file_name);

    if (!fs.is_open()) {
        cout << "Open file failed! [READ]\n";
        exit(1);
    }

    for (size_t i = 0; i < size; i++) {
        fs >> array[i];
    }

    fs.close();
}

void read_answer(string file_name, int* array, size_t size) {
    std::fstream fs;

    fs.open(file_name);

    if (!fs.is_open()) {
        cout << "Open file failed! [READ]\n";
        exit(1);
    }

    for (size_t i = 0; i < size; i++) {
        fs >> array[i];
    }

    fs.close();
}

void write_data_bin(string file_name, uint16_t* array, size_t size) {
    std::ofstream fs;

    fs.open(file_name, ios::out | ios::binary);

    if (!fs.is_open()) {
        cout << "Open file failed! [WRITE]\n";
        exit(1);
    }

    fs.write(reinterpret_cast<const char*>(array), size * sizeof(uint16_t));

    fs.close();
}

void write_answer_bin(string file_name, int* array, size_t size) {
    std::ofstream fs;

    fs.open(file_name, ios::out | ios::binary);

    if (!fs.is_open()) {
        cout << "Open file failed! [WRITE]\n";
        exit(1);
    }
    
    fs.write(reinterpret_cast<const char*>(array), size * sizeof(int));

    fs.close();
}

void read_data_bin(string file_name, uint16_t* array, size_t size) {
    std::ifstream fs;

    fs.open(file_name, ios::in | ios::binary);

    if (!fs.is_open()) {
        cout << "Open file failed! [READ]\n";
        exit(1);
    }

    fs.read(reinterpret_cast<char*>(array), size * sizeof(uint16_t));

    fs.close();

    for (size_t i = 0; i < size; i++) {
        cout << setw(6) << array[i] << " ";
        if (i % 32 == 31) cout << "\n";
    }
}


int main (void) {


    input_t**  input  = new input_t*[NUM];
    uint16_t** output = new uint16_t*[NUM];

    for (size_t i = 0; i < NUM; i++) {
        input[i]  = new input_t[IMAGE_SIZE];
        output[i] = new uint16_t[IMAGE_SIZE];
    }

    string dir1 = "../../../data/input/input_";
    string dir2 = "../../../data/input_fx_bin/fx_";

    string ext1 = ".data";
	string ext2 = ".bin";

    for (size_t i = 0; i < NUM; i++) {

        string num = to_string(i);
        string file = dir1 + num + ext1;

        read_data(file, input[i], IMAGE_SIZE);
    }

    for (size_t i = 0; i < NUM; i++) {
        for (size_t j = 0; j < IMAGE_SIZE; j++) {
            output[i][j] = input[i][j].range();
        }
    }
    
    for (size_t i = 0; i < NUM; i++) {
        string num = to_string(i);
        string file = dir2 + num + ext2;

        write_data_bin(file, output[i], IMAGE_SIZE);
    }

    int answer[NUM] = { 0, };

    string input_answer  = "../../../data/input/answer.txt";
    string output_answer = "../../../data/input_fx_bin/answer.bin";

    read_answer(input_answer, answer, NUM);
    write_answer_bin(output_answer, answer, NUM);

    for (size_t i = 0; i < NUM; i++) {
        delete[] input[i];
        delete[] output[i];
    }

    delete[] input;
    delete[] output;

}
