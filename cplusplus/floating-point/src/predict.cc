#include "../inc/predict.h"

/* Use when run all samples to determine MAX and MIN values */
int predict(float* input, float* conv1_max, float* conv1_min,
                          float* conv2_max, float* conv2_min,
                          float* conv3_max, float* conv3_min,
                          float* full1_max, float* full1_min,
                          float* full2_max, float* full2_min) {
    
    /* Intermediate outputs */
    float conv1_output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL] = { 0.0 };
    float relu1_output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL] = { 0.0 };
    float pool1_output[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL] = { 0.0 };

    float conv2_output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL] = { 0.0 };
    float relu2_output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL] = { 0.0 };
    float pool2_output[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL] = { 0.0 };

    float conv3_output[CONV3_OUTPUT_SIZE] = { 0.0 };
    float relu3_output[CONV3_OUTPUT_SIZE] = { 0.0 };

    float full1_output[FULL1_OUTPUT_SIZE] = { 0.0 };
    float relu4_output[FULL1_OUTPUT_SIZE] = { 0.0 };

    float full2_output[FULL2_OUTPUT_SIZE] = { 0.0 };

    /* 1st convolution layer */
    conv1_layer(input, conv1_output);

    /* 1st ReLU layer */
    relu1_layer(conv1_output, relu1_output);

    /* 1st pooling layer */
    pool1_layer(relu1_output, pool1_output);

    /* 2nd convolution layer */
    conv2_layer(pool1_output, conv2_output);

    /* 2nd ReLU layer */
    relu2_layer(conv2_output, relu2_output);
    
    /* 2nd pooling layer */
    pool2_layer(relu2_output, pool2_output);

    /* 3th convolution layer */
    conv3_layer(pool2_output, conv3_output);

    /* 3th ReLU layer */
    relu3_layer(conv3_output, relu3_output);

    /* 1st fully connected layer */
    full1_layer(relu3_output, full1_output);

    /* 4th ReLU layer */
    relu4_layer(full1_output, relu4_output);

    /* 2nd fully connected layer */
    full2_layer(relu4_output, full2_output);


    /* Find the MAX value of each intermediate result to determine the number of fixed point integer bits */
    *conv1_max = *std::max_element((float*)conv1_output, (float*)conv1_output + CONV1_OUTPUT_SIZE);
    *conv2_max = *std::max_element((float*)conv2_output, (float*)conv2_output + CONV2_OUTPUT_SIZE);
    *conv3_max = *std::max_element((float*)conv3_output, (float*)conv3_output + CONV3_OUTPUT_SIZE);
    *full1_max = *std::max_element((float*)full1_output, (float*)full1_output + FULL1_OUTPUT_SIZE);
    *full2_max = *std::max_element((float*)full2_output, (float*)full2_output + FULL2_OUTPUT_SIZE);

    /* Find the MIN value of each intermediate result to determine the number of fixed point integer bits */
    *conv1_min = *std::min_element((float*)conv1_output, (float*)conv1_output + CONV1_OUTPUT_SIZE);
    *conv2_min = *std::min_element((float*)conv2_output, (float*)conv2_output + CONV2_OUTPUT_SIZE);
    *conv3_min = *std::min_element((float*)conv3_output, (float*)conv3_output + CONV3_OUTPUT_SIZE);
    *full1_min = *std::min_element((float*)full1_output, (float*)full1_output + FULL1_OUTPUT_SIZE);
    *full2_min = *std::min_element((float*)full2_output, (float*)full2_output + FULL2_OUTPUT_SIZE);

    /* Return result */
    return result(full2_output);

}


void predict(float* input, bool print_opt) {

    /* Intermediate outputs */
    float conv1_output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL] = { 0.0 };
    float relu1_output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL] = { 0.0 };
    float pool1_output[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL] = { 0.0 };

    float conv2_output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL] = { 0.0 };
    float relu2_output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL] = { 0.0 };
    float pool2_output[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL] = { 0.0 };

    float conv3_output[CONV3_OUTPUT_SIZE] = { 0.0 };
    float relu3_output[CONV3_OUTPUT_SIZE] = { 0.0 };

    float full1_output[FULL1_OUTPUT_SIZE] = { 0.0 };
    float relu4_output[FULL1_OUTPUT_SIZE] = { 0.0 };

    float full2_output[FULL2_OUTPUT_SIZE] = { 0.0 };

    print_3d("Input image", input, IMAGE_NUM, IMAGE_ROW, IMAGE_COL, true);

    /* 1st convolution layer */
    conv1_layer(input, conv1_output);

    /* 1st ReLU layer */
    relu1_layer(conv1_output, relu1_output);

    /* 1st pooling layer */
    pool1_layer(relu1_output, pool1_output);

    /* 2nd convolution layer */
    conv2_layer(pool1_output, conv2_output);

    /* 2nd ReLU layer */
    relu2_layer(conv2_output, relu2_output);
    
    /* 2nd pooling layer */
    pool2_layer(relu2_output, pool2_output);

    /* 3th convolution layer */
    conv3_layer(pool2_output, conv3_output);

    /* 3th ReLU layer */
    relu3_layer(conv3_output, relu3_output);

    /* 1st fully connected layer */
    full1_layer(relu3_output, full1_output);

    /* 4th ReLU layer */
    relu4_layer(full1_output, relu4_output);

    /* 2nd fully connected layer */
    full2_layer(relu4_output, full2_output);

    if (print_opt) {
        print_3d("CONV1 output", (float*)relu1_output, CONV1_OUTPUT_NUM, CONV1_OUTPUT_ROW, CONV1_OUTPUT_COL, print_opt);
        print_3d("POOL1 output", (float*)pool1_output, POOL1_OUTPUT_NUM, POOL1_OUTPUT_ROW, POOL1_OUTPUT_COL, print_opt);
        
        print_3d("CONV2 output", (float*)relu2_output, CONV2_OUTPUT_NUM, CONV2_OUTPUT_ROW, CONV2_OUTPUT_COL, print_opt);
        print_3d("POOL2 output", (float*)pool2_output, POOL2_OUTPUT_NUM, POOL2_OUTPUT_ROW, POOL2_OUTPUT_COL, print_opt);
        
        print_1d("CONV3 output", relu3_output, CONV3_OUTPUT_NUM, print_opt);

        print_1d("FULL1 output", relu4_output, FULL1_OUTPUT_SIZE, print_opt);
        
        print_1d("FULL2 output", full2_output, FULL2_OUTPUT_SIZE, print_opt);
    }

    print_result(full2_output);
}
