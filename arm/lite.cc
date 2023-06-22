#include "lite.h"

void predict_ref(float* input, u8* output) {

    float conv1_output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL] = { 0.0 };
    float pool1_output[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL] = { 0.0 };

    float conv2_output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL] = { 0.0 };
    float pool2_output[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL] = { 0.0 };

    float conv3_output[CONV3_OUTPUT_SIZE] = { 0.0 };

    float full1_output[FULL1_OUTPUT_SIZE] = { 0.0 };

    float full2_output[FULL2_OUTPUT_SIZE] = { 0.0 };

    conv1_layer(input, conv1_output);

    pool1_layer(conv1_output, pool1_output);

    conv2_layer(pool1_output, conv2_output);

    pool2_layer(conv2_output, pool2_output);

    conv3_layer(pool2_output, conv3_output);

    full1_layer(conv3_output, full1_output);

    full2_layer(full1_output, full2_output);

    result(full2_output, output);
}

void conv1_layer(float* input, 
                 float  output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL])
{
    for (int wn = 0; wn < CONV1_WEIGHT_NUM; wn++) {
        for (int orow = 0; orow < CONV1_OUTPUT_ROW; orow++) {
            for (int ocol = 0; ocol < CONV1_OUTPUT_COL; ocol++) {
                output[wn][orow][ocol] = conv1_bias[wn];

                for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                    for (int wc = 0; wc < WEIGHT_COL; wc++) {
                        output[wn][orow][ocol] += input[(orow + wr) * IMAGE_COL + (ocol + wc)] * conv1_weight[wn][wr][wc];
                    }
                }

                output[wn][orow][ocol] = output[wn][orow][ocol] > 0.0 ? output[wn][orow][ocol] : 0.0;
            }
        }
    }
}


void pool1_layer(float  input[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL], 
                 float output[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL])
{
    float max = 0.0;

    for (int num = 0; num < CONV1_OUTPUT_NUM; num++) {
        for (int row = 0; row < CONV1_OUTPUT_ROW; row += POOL_STRIDE) {
            for (int col = 0; col < CONV1_OUTPUT_COL; col += POOL_STRIDE) {
                
                max = input[num][row][col];

                for (int pr = 0; pr < POOL_ROW; pr++) {
                    for (int pc = 0; pc < POOL_COL; pc++) {
                        if (input[num][row + pr][col + pc] > max)
                            max = input[num][row + pr][col + pc];
                    }
                }
                output[num][row >> 1][col >> 1] = max;
            }
        }
    }
}

void conv2_layer(float  input[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL], 
                 float output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL])
{
    for (int wn = 0; wn < CONV2_WEIGHT_NUM; wn++) {
        for (int orow = 0; orow < CONV2_OUTPUT_ROW; orow++) {
            for (int ocol = 0; ocol < CONV2_OUTPUT_COL; ocol++) {

                output[wn][orow][ocol] = conv2_bias[wn];

                for (int wch = 0; wch < CONV2_WEIGHT_CH; wch++) {
                    for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                        for (int wc = 0; wc < WEIGHT_COL; wc++) {
                            output[wn][orow][ocol] += input[wch][orow + wr][ocol + wc] * conv2_weight[wn][wch][wr][wc];
                        }   
                    }
                }

                output[wn][orow][ocol] = output[wn][orow][ocol] > 0.0 ? output[wn][orow][ocol] : 0.0;

            }
        }
    }
}

void pool2_layer(float  input[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL], 
                 float output[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL])
{   
    float max = 0.0;

    for (int num = 0; num < CONV2_OUTPUT_NUM; num++) {
        for (int row = 0; row < CONV2_OUTPUT_ROW; row += POOL_STRIDE) {
            for (int col = 0; col < CONV2_OUTPUT_COL; col += POOL_STRIDE) {
                
                max = input[num][row][col];

                for (int pr = 0; pr < POOL_ROW; pr++) {
                    for (int pc = 0; pc < POOL_COL; pc++) {
                        if (input[num][row + pr][col + pc] > max)
                            max = input[num][row + pr][col + pc];
                    }
                }
                output[num][row >> 1][col >> 1] = max;
            }
        }
    }
}

void conv3_layer(float  input[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL], 
                 float output[CONV3_OUTPUT_SIZE])
{
    for (int wn = 0; wn < CONV3_WEIGHT_NUM; wn++) {
        
        output[wn] = conv3_bias[wn];

        for (int wch = 0; wch < CONV3_WEIGHT_CH; wch++) {
            for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                for (int wc = 0; wc < WEIGHT_COL; wc++) {
                    output[wn] += input[wch][wr][wc] * conv3_weight[wn][wch][wr][wc];
                }
            }
        }

        output[wn] = output[wn] > 0.0 ? output[wn] : 0.0;

    }
}

void relu3_layer(float  input[CONV3_OUTPUT_SIZE], 
                 float output[CONV3_OUTPUT_SIZE])
{
    for (int i = 0; i < CONV3_OUTPUT_SIZE; i++) {
        output[i] = input[i] > 0.0 ? input[i] : 0.0;    
    }
}

void full1_layer(float  input[CONV3_OUTPUT_SIZE], 
                 float output[FULL1_OUTPUT_SIZE])
{
    for (int row = 0; row < FULL1_WEIGHT_ROW; row++) {

        output[row] = full1_bias[row];

        for (int col = 0; col < FULL1_WEIGHT_COL; col++) {
            output[row] += input[col] * full1_weight[row][col];
        }

        output[row] = output[row] > 0.0 ? output[row] : 0.0;
    }
}

void full2_layer(float  input[FULL2_OUTPUT_SIZE], 
                 float output[FULL2_OUTPUT_SIZE])
{
    for (int row = 0; row < FULL2_WEIGHT_ROW; row++) {
        
        output[row] = full2_bias[row];
        
        for (int col = 0; col < FULL2_WEIGHT_COL; col++) {
            output[row] += input[col] * full2_weight[row][col];
        }

    }
}

void result(float input[FULL2_OUTPUT_SIZE], u8* output){
    
    float max = input[0];

    int max_index = 0;

    for (int i = 1; i < 10; i++) {
        if (max < input[i]) {
            max = input[i];
            max_index = i;
        }
    }

    *output = max_index;
}