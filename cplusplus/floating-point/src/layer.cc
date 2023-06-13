#include "../inc/layer.h"

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
            }
        }
    }
}

void relu1_layer(float  input[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL], 
                 float output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL])
{
    for (int k = 0; k < CONV1_OUTPUT_NUM; k++) {
        for (int i = 0; i < CONV1_OUTPUT_ROW; i++) {
            for (int j = 0; j < CONV1_OUTPUT_COL; j++) {
                output[k][i][j] = input[k][i][j] > 0.0 ? input[k][i][j] : 0.0;
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
            }
        }
    }
}

void relu2_layer(float  input[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL], 
                 float output[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL])
{
    for (int k = 0; k < CONV2_OUTPUT_NUM; k++) {
        for (int i = 0; i < CONV2_OUTPUT_ROW; i++) {
            for (int j = 0; j < CONV2_OUTPUT_COL; j++) {
                output[k][i][j] = input[k][i][j] > 0.0 ? input[k][i][j] : 0.0;    
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
    }
}

void relu4_layer(float  input[FULL1_OUTPUT_SIZE], 
                 float output[FULL1_OUTPUT_SIZE])
{
    for (int i = 0; i < FULL1_OUTPUT_SIZE; i++) {
        output[i] = input[i] > 0.0 ? input[i] : 0.0;    
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

uint8_t result(float input[FULL2_OUTPUT_SIZE]){
    
    float max = input[0];

    uint8_t max_index = 0;

    for (int i = 1; i < 10; i++) {
        if (max < input[i]) {
            max = input[i];
            max_index = i;
        }
    }

    return max_index;
}

