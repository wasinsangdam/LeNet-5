#include <iostream>
#include <fstream>
#include <string>

#include "predict.h"
#include "parameter.h"

#define INPUT_DIR "C:\\LeNet-5\\input\\" // Synthesis & Generate IP executed on Window

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

        if (i == size - 1) 
            temp_axi.last = 1;

        stream.write(temp_axi);
    }

    fs.close();
}

int main (int argc, char* argv[]) {

    std::string input_data;

    stream_axis input_axi_stream;

    int err_cnt = 0;

    uint8_t my_answer[TEST_NUM] = { 0, };

    for (size_t i = 0; i < TEST_NUM; i++) {

        std::string dir   = INPUT_DIR;
        std::string input = "input_";
        std::string num   = std::to_string(i);
        std::string ext   = ".data";

        std::string file  = dir + input + num + ext;

        read_data(file, input_axi_stream, IMAGE_SIZE);

        predict(input_axi_stream, &my_answer[i]);

        std::cout << (int)my_answer[i] << "\n";
    }

    return 0;

}
