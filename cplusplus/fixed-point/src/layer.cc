#include "../inc/layer.h"

void read_input(float* input, input_t output[IMAGE_ROW][IMAGE_COL]) {

    /* Read input */
    for (size_t i = 0; i < IMAGE_ROW; i++) {
        for (size_t j = 0; j < IMAGE_COL; j++) {
            output[i][j] = (input_t)input[i * IMAGE_COL + j];
        }
    }
}

void conv1_layer(input_t input[IMAGE_ROW][IMAGE_COL], 
                 conv1_t output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL]) 
{
    for (int wn = 0; wn < CONV1_WEIGHT_NUM; wn++) {
        for (int orow = 0; orow < CONV1_OUTPUT_ROW; orow++) {
            for (int ocol = 0; ocol < CONV1_OUTPUT_COL; ocol++) {
                
                /* Compute */
                conv1_temp acc = conv1_bias[wn];

                for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                    for (int wc = 0; wc < WEIGHT_COL; wc++) {
                        acc += (conv1_temp)(input[orow + wr][ocol + wc] * conv1_weight[wn][wr][wc]);
                    }
                }

                /* ReLU Activation & Write */
                if (acc > 0) output[wn][orow][ocol] = (conv1_t)acc;
                else         output[wn][orow][ocol] = (conv1_t)0.0;
            }
        }
    }
}


void pool1_layer(conv1_t  input[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL],
                 conv1_t output[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL]) 
{
    for (int num = 0; num < CONV1_OUTPUT_NUM; num++) {
        for (int row = 0; row < CONV1_OUTPUT_ROW; row += POOL_STRIDE) {
            for (int col = 0; col < CONV1_OUTPUT_COL; col += POOL_STRIDE) {
                
                /* Compute */
                conv1_t n1 = input[num][row][col];
                conv1_t n2 = input[num][row][col + 1];
                conv1_t n3 = input[num][row + 1][col];
                conv1_t n4 = input[num][row + 1][col + 1];

                conv1_t max1 = std::max(n1, n2);
                conv1_t max2 = std::max(n3, n4);

                conv1_t max = std::max(max1, max2); // Find Max value 

                /* Write */
                output[num][row >> 1][col >> 1] = max;
            }
        }
    }
}



void conv2_layer(conv1_t  input[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL],
                 conv2_t output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL])
{
    for (int wn = 0; wn < CONV2_WEIGHT_NUM; wn++) {
        for (int orow = 0; orow < CONV2_OUTPUT_ROW; orow++) {
            for (int ocol = 0; ocol < CONV2_OUTPUT_COL; ocol++) {
                
                /* Compute */
                conv2_temp acc = conv2_bias[wn];

                for (int wch = 0; wch < CONV2_WEIGHT_CH; wch++) {
                    for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                        for (int wc = 0; wc < WEIGHT_COL; wc++) {
                            acc += (conv2_temp)(input[wch][orow + wr][ocol + wc] * conv2_weight[wn][wch][wr][wc]);
                        }
                    }
                }

                /* ReLU Activation & Write */
                if (acc > 0) output[wn][orow][ocol] = (conv2_t)acc;
                else         output[wn][orow][ocol] = (conv2_t)0.0;
            }
        }
    }
}


void pool2_layer(conv2_t  input[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL],
                 conv2_t output[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL]) 
{
    for (int num = 0; num < CONV2_OUTPUT_NUM; num++) {
        for (int row = 0; row < CONV2_OUTPUT_ROW; row += POOL_STRIDE) {
            for (int col = 0; col < CONV2_OUTPUT_COL; col += POOL_STRIDE) {
                
                /* Compute */
                conv2_t n1 = input[num][row][col];
                conv2_t n2 = input[num][row][col + 1];
                conv2_t n3 = input[num][row + 1][col];
                conv2_t n4 = input[num][row + 1][col + 1];

                conv2_t max1 = std::max(n1, n2);
                conv2_t max2 = std::max(n3, n4);
                
                conv2_t max = std::max(max1, max2); // Find Max value

                /* Write */
                output[num][row >> 1][col >> 1] = max;
            }
        }
    }
}

void conv3_layer(conv2_t  input[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL],
                 conv3_t output[CONV3_OUTPUT_SIZE])
{
    for (int wn = 0; wn < CONV3_WEIGHT_NUM; wn++) {

        /* Compute */
        conv3_temp acc = conv3_bias[wn];

        for (int wch = 0; wch < CONV3_WEIGHT_CH; wch++) {
            for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                for (int wc = 0; wc < WEIGHT_COL; wc++) {
                    acc += (conv3_temp)(input[wch][wr][wc] * conv3_weight[wn][wch][wr][wc]);
                }
            }
        }

        /* ReLU Activation & Write */
        if (acc > 0) output[wn] = (conv3_t)acc;
        else         output[wn] = (conv3_t)0.0;
    }
}


void full1_layer(conv3_t  input[CONV3_OUTPUT_SIZE],
                 full1_t output[FULL1_OUTPUT_SIZE])
{
    for (int row = 0; row < FULL1_WEIGHT_ROW; row++) {
        
        /* Compute */
        full1_temp acc = full1_bias[row];

        for (int col = 0; col < FULL1_WEIGHT_COL; col++) {
            acc += (full1_temp)(input[col] * full1_weight[row][col]);
        }

        /* ReLU Activation & Write */
        if (acc > 0) output[row] = (full1_t)acc;
        else         output[row] = (full1_t)0.0;
    }
}


void full2_layer(full1_t  input[FULL1_OUTPUT_SIZE],
                 full2_t output[FULL2_OUTPUT_SIZE])
{
    for (int row = 0; row < FULL2_WEIGHT_ROW; row++) {
        
        /* Compute */
        full2_temp acc = full2_bias[row];

        for (int col = 0; col < FULL2_WEIGHT_COL; col++) {
            acc += (full2_temp)(input[col] * full2_weight[row][col]);
        }

        /* Write */
        output[row] = (full2_t)acc;
    }
}

uint8_t result(full2_t* array) {

    full2_t max = array[0];

    uint8_t max_index = 0;

    /* Find Max value and index of Max value */
    for (int i = 1; i < 10; i++) {
        if (max < array[i]) {
            max = array[i];
            max_index = i;
        }
    }

    return max_index;   // Return index of Max value
}