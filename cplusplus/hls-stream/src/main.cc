#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iomanip>
#include <string>

#include "../inc/parameter.h"
#include "../inc/dir.h"
#include "../inc/layer.h"
#include "../inc/util.h"
#include "../inc/type.h"
#include "../inc/weight.h"
#include "../inc/predict.h"

/* LeNet-5 Architecture */
/*
    [INPUT] -> [ CONV1 + ReLU ] -> 
   (32 * 32)   [  Max Pooling ] -> 
   ( image )   [ CONV2 + ReLU ] -> 
               [  Max Pooling ] -> 
               [ CONV3 + ReLU ] -> 
               [ FULL1 + ReLU ] ->
               [ FULL2 + SMax ] -> [OUTPUT] 
                                     (1)
                              (Predicted number)
*/

int main (int argc, char* argv[]) {

    std::string input_data;

    input_t input_array[IMAGE_SIZE] = { 0.0, };

    /* Run all test cases */
    int err_cnt = 0;

    int    answer[TEST_NUM] = { 0, };
    int my_answer[TEST_NUM] = { 0, };

    std::string answer_file = ANSWER_FILE;
    
    read_answer(answer_file, answer, TEST_NUM);
    
    std::cout << "Number \tAnswer\tPredict \n";

    for (size_t i = 0; i < TEST_NUM; i++) {
        
        stream_output output;

        std::string dir   = INPUT_DIR;
        std::string input = "input_";
        std::string num   = std::to_string(i);
        std::string ext   = ".data";

        std::string file  = dir + input + num + ext;

        read_data(file, input_array, IMAGE_SIZE);

        predict(input_array, output);

        my_answer[i] = (int)output.read(); 

        if (my_answer[i] != answer[i]) {
            err_cnt++;
            std::cout << "[ FALSE ]  [" << std::setw(4) << i << "]\t" << answer[i] << "\t" << my_answer[i] << "\n";
        }
        else {
            std::cout << "[ TRUE  ]  [" << std::setw(4) << i << "]\t" << answer[i] << "\t" << my_answer[i] << "\n";
        }

        
        
    }

    float accuracy = ((float)(TEST_NUM - err_cnt) / (float)TEST_NUM) * 100;
    std::cout << "\n[Fixed-Point + HLS stream] \n";
    std::cout << "Accuracy : " << std::setw(5) << accuracy << " [%] \n";
    std::cout << "Error    : " << std::setw(5) << err_cnt  << " [cases] \n\n";
    
    return 0;

}