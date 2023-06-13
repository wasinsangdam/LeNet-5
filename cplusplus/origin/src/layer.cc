#include "../inc/layer.h"

void conv1_layer(float* input, 
                 float  output[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL])
{
    for (int wn = 0; wn < CONV1_WEIGHT_NUM; wn++) {
        for (int orow = 0; orow < CONV1_OUTPUT_ROW; orow++) {
            for (int ocol = 0; ocol < CONV1_OUTPUT_COL; ocol++) {

                float acc = conv1_bias[wn];

                for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                    for (int wc = 0; wc < WEIGHT_COL; wc++) {
                        acc += input[(orow + wr) * IMAGE_COL + (ocol + wc)] * conv1_weight[wn][wr][wc];
                    }
                }

                output[wn][orow][ocol] = (float)std::tanh(acc);
            }
        }
    }
}


void pool1_layer(float  input[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL], 
                 float output[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL])
{

    for (int num = 0; num < CONV1_OUTPUT_NUM; num++) {
        for (int row = 0; row < CONV1_OUTPUT_ROW; row += POOL_STRIDE) {
            for (int col = 0; col < CONV1_OUTPUT_COL; col += POOL_STRIDE) {
                
                float avg = 0.0;

                avg += input[num][row][col];
                avg += input[num][row][col + 1];
                avg += input[num][row + 1][col];
                avg += input[num][row + 1][col + 1];

                avg = (float)(avg / 4.0) ;

                output[num][row >> 1][col >> 1] = sigmoid(avg);
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

                float acc = conv2_bias[wn];

                for (int wch = 0; wch < CONV2_WEIGHT_CH; wch++) {
                    for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                        for (int wc = 0; wc < WEIGHT_COL; wc++) {
                            acc += input[wch][orow + wr][ocol + wc] * conv2_weight[wn][wch][wr][wc];
                        }   
                    }
                }

                output[wn][orow][ocol] = (float)std::tanh(acc);
            }
        }
    }
}



void pool2_layer(float  input[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL], 
                 float output[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL])
{   

    for (int num = 0; num < CONV2_OUTPUT_NUM; num++) {
        for (int row = 0; row < CONV2_OUTPUT_ROW; row += POOL_STRIDE) {
            for (int col = 0; col < CONV2_OUTPUT_COL; col += POOL_STRIDE) {
                
                float avg = 0.0;

                avg += input[num][row][col];
                avg += input[num][row][col + 1];
                avg += input[num][row + 1][col];
                avg += input[num][row + 1][col + 1];

                avg = (float)(avg / 4.0) ;

                output[num][row >> 1][col >> 1] = sigmoid(avg);
            }
        }
    }
}

void conv3_layer(float  input[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL], 
                 float output[CONV3_OUTPUT_SIZE])
{
    for (int wn = 0; wn < CONV3_WEIGHT_NUM; wn++) {
        
        float acc = conv3_bias[wn];

        for (int wch = 0; wch < CONV3_WEIGHT_CH; wch++) {
            for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                for (int wc = 0; wc < WEIGHT_COL; wc++) {
                    acc += input[wch][wr][wc] * conv3_weight[wn][wch][wr][wc];
                }
            }
        }

        output[wn] = (float)std::tanh(acc);
    }
}


void full1_layer(float  input[CONV3_OUTPUT_SIZE], 
                 float output[FULL1_OUTPUT_SIZE])
{
    for (int row = 0; row < FULL1_WEIGHT_ROW; row++) {

        float acc = full1_bias[row];

        for (int col = 0; col < FULL1_WEIGHT_COL; col++) {
            acc += input[col] * full1_weight[row][col];
        }

        output[row] = (float)std::tanh(acc);
    }
}



void full2_layer(float  input[FULL2_OUTPUT_SIZE], 
                 float output[FULL2_OUTPUT_SIZE])
{
    for (int row = 0; row < FULL2_WEIGHT_ROW; row++) {
        
        float acc = full2_bias[row];
        
        for (int col = 0; col < FULL2_WEIGHT_COL; col++) {
            acc += input[col] * full2_weight[row][col];
        }

        output[row] = (float)std::tanh(acc);
    }
}

float sigmoid(float x) {
    return 1.0 / (1.0 + std::exp(-x));
}

uint8_t softmax(float input[FULL2_OUTPUT_SIZE]){
    
    float output[FULL2_OUTPUT_SIZE];
    float sum = 0.0;
    float max = 0.0;

    uint8_t max_index = 0;

    for (int i = 0; i < FULL2_OUTPUT_SIZE; i++) {
        sum += std::exp(input[i]);
    }


    for (int i = 0; i < FULL2_OUTPUT_SIZE; i++) {
        output[i] = std::exp(input[i]) / sum;
    }

    
    for (int i = 0; i < 10; i++) {
        if (max < output[i]) {
            max = output[i];
            max_index = (uint8_t)i;
        }
    }

    return max_index;
}

