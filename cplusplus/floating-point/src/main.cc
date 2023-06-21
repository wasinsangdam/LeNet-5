#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <iomanip>
#include <string>

#include "../inc/parse.h"
#include "../inc/color.h"
#include "../inc/parameter.h"
#include "../inc/dir.h"
#include "../inc/layer.h"
#include "../inc/util.h"
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

    bool print_option = false;
    bool all_option   = false;

    arg_parse(argc, argv, &input_data, &print_option, &all_option);

    float input_array[IMAGE_SIZE] = { 0, };

    /* Run all */
    if (all_option) {
        int err_cnt = 0;

        int answer[TEST_NUM] = { 0, };
        int my_answer[TEST_NUM] = { 0, };

        /* --- For Max/Min test --- */
        float max_conv1[TEST_NUM];
        float min_conv1[TEST_NUM];

        float max_conv2[TEST_NUM];
        float min_conv2[TEST_NUM];
        
        float max_conv3[TEST_NUM];
        float min_conv3[TEST_NUM];

        float max_full1[TEST_NUM];
        float min_full1[TEST_NUM];

        float max_full2[TEST_NUM];
        float min_full2[TEST_NUM];

        float max_conv1_value;
        float min_conv1_value;

        float max_conv2_value;
        float min_conv2_value;

        float max_conv3_value;
        float min_conv3_value;

        float max_full1_value;
        float min_full1_value;

        float max_full2_value;
        float min_full2_value;
        /* --- For max/min test --- */

        std::string answer_file = ANSWER_FILE;
        
        read_answer(answer_file, answer, TEST_NUM);
        
        std::cout << "Number \tAnswer\tPredict \n";

        for (size_t i = 0; i < TEST_NUM; i++) {
            
            std::string dir   = INPUT_DIR;
            std::string input = "input_";
            std::string num   = std::to_string(i);
            std::string ext   = ".data";

            std::string file  = dir + input + num + ext;

            read_data(file, input_array, IMAGE_SIZE);

            my_answer[i] = predict(input_array, &max_conv1[i], &min_conv1[i],
                                                &max_conv2[i], &min_conv2[i],
                                                &max_conv3[i], &min_conv3[i],
                                                &max_full1[i], &min_full1[i],
                                                &max_full2[i], &min_full2[i]);

            

            if (my_answer[i] != answer[i]) {
                err_cnt++;
                std::cout << "[ FALSE ]  [" << std::setw(4) << i << "]\t" << answer[i] << "\t" << (int)my_answer[i] << "\n";
            }
            else {
                std::cout << "[ TRUE  ]  [" << std::setw(4) << i << "]\t" << answer[i] << "\t" << (int)my_answer[i] << "\n";
            }
        }

        float accuracy = ((float)(TEST_NUM - err_cnt) / (float)TEST_NUM) * 100;
        std::cout << "\n[Floating-Point]\n";
        std::cout << "Accuracy : " << std::setw(5) << accuracy << " [%] \n";
        std::cout << "Error    : " << std::setw(5) << err_cnt  << " [cases] \n\n";

        /* Find Max/Min */
        max_conv1_value = *std::max_element(max_conv1, max_conv1 + TEST_NUM);
        min_conv1_value = *std::min_element(min_conv1, min_conv1 + TEST_NUM);

        max_conv2_value = *std::max_element(max_conv2, max_conv2 + TEST_NUM);
        min_conv2_value = *std::min_element(min_conv2, min_conv2 + TEST_NUM);

        max_conv3_value = *std::max_element(max_conv3, max_conv3 + TEST_NUM);
        min_conv3_value = *std::min_element(min_conv3, min_conv3 + TEST_NUM);

        max_full1_value = *std::max_element(max_full1, max_full1 + TEST_NUM);
        min_full1_value = *std::min_element(min_full1, min_full1 + TEST_NUM);

        max_full2_value = *std::max_element(max_full2, max_full2 + TEST_NUM);
        min_full2_value = *std::min_element(min_full2, min_full2 + TEST_NUM);

        std::cout << "[CONV1] output \t\t MAX : " << std::setw(10) << max_conv1_value << "\t MIN : " << std::setw(10) << min_conv1_value << std::endl;
        std::cout << "[CONV2] output \t\t MAX : " << std::setw(10) << max_conv2_value << "\t MIN : " << std::setw(10) << min_conv2_value << std::endl;
        std::cout << "[CONV3] output \t\t MAX : " << std::setw(10) << max_conv3_value << "\t MIN : " << std::setw(10) << min_conv3_value << std::endl;
        std::cout << "[FULL1] output \t\t MAX : " << std::setw(10) << max_full1_value << "\t MIN : " << std::setw(10) << min_full1_value << std::endl;
        std::cout << "[FULL2] output \t\t MAX : " << std::setw(10) << max_full2_value << "\t MIN : " << std::setw(10) << min_full2_value << std::endl;
       
    }

    /* Run one sample and print intermediate output depending on print option */
    else {
        read_data(input_data  , input_array , IMAGE_SIZE);  // Read input data
        predict(input_array, print_option);                 // Run one input 
    }

    return 0;
}