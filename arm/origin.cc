#include "origin.h"

void org_predict(float* input, u8* output) {

    /* Intermediate outputs */
    float conv1_output[ORG_CONV1_OUTPUT_NUM][ORG_CONV1_OUTPUT_ROW][ORG_CONV1_OUTPUT_COL] = { 0.0 };
    float pool1_output[ORG_POOL1_OUTPUT_NUM][ORG_POOL1_OUTPUT_ROW][ORG_POOL1_OUTPUT_COL] = { 0.0 };

    float conv2_output[ORG_CONV2_OUTPUT_NUM][ORG_CONV2_OUTPUT_ROW][ORG_CONV2_OUTPUT_COL] = { 0.0 };
    float pool2_output[ORG_POOL2_OUTPUT_NUM][ORG_POOL2_OUTPUT_ROW][ORG_POOL2_OUTPUT_COL] = { 0.0 };

    float conv3_output[ORG_CONV3_OUTPUT_SIZE] = { 0.0 };

    float full1_output[ORG_FULL1_OUTPUT_SIZE] = { 0.0 };

    float full2_output[ORG_FULL2_OUTPUT_SIZE] = { 0.0 };

    /* 1st convolution layer */
    org_conv1_layer(input, conv1_output);

    /* 1st pooling layer */
    org_pool1_layer(conv1_output, pool1_output);

    /* 2nd convolution layer */
    org_conv2_layer(pool1_output, conv2_output);
    
    /* 2nd pooling layer */
    org_pool2_layer(conv2_output, pool2_output);

    /* 3th convolution layer */
    org_conv3_layer(pool2_output, conv3_output);

    /* 1st fully connected layer */
    org_full1_layer(conv3_output, full1_output);

    /* 2nd fully connected layer */
    org_full2_layer(full1_output, full2_output);

    /* Softmax */
    softmax(full2_output, output);
}

void org_conv1_layer(float* input, 
                     float  output[ORG_CONV1_OUTPUT_NUM][ORG_CONV1_OUTPUT_ROW][ORG_CONV1_OUTPUT_COL])
{
    for (int wn = 0; wn < ORG_CONV1_WEIGHT_NUM; wn++) {
        for (int orow = 0; orow < ORG_CONV1_OUTPUT_ROW; orow++) {
            for (int ocol = 0; ocol < ORG_CONV1_OUTPUT_COL; ocol++) {

                float acc = org_conv1_bias[wn];

                for (int wr = 0; wr < ORG_WEIGHT_ROW; wr++) {
                    for (int wc = 0; wc < ORG_WEIGHT_COL; wc++) {
                        acc += input[(orow + wr) * ORG_IMAGE_COL + (ocol + wc)] * org_conv1_weight[wn][wr][wc];
                    }
                }

                output[wn][orow][ocol] = (float)std::tanh(acc);
            }
        }
    }
}


void org_pool1_layer(float  input[ORG_CONV1_OUTPUT_NUM][ORG_CONV1_OUTPUT_ROW][ORG_CONV1_OUTPUT_COL], 
                     float output[ORG_POOL1_OUTPUT_NUM][ORG_POOL1_OUTPUT_ROW][ORG_POOL1_OUTPUT_COL])
{

    for (int num = 0; num < ORG_CONV1_OUTPUT_NUM; num++) {
        for (int row = 0; row < ORG_CONV1_OUTPUT_ROW; row += ORG_POOL_STRIDE) {
            for (int col = 0; col < ORG_CONV1_OUTPUT_COL; col += ORG_POOL_STRIDE) {
                
                float avg = 0.0;

                avg += input[num][row][col];
                avg += input[num][row][col + 1];
                avg += input[num][row + 1][col];
                avg += input[num][row + 1][col + 1];

                avg = (float)(avg / 4.0);

                output[num][row >> 1][col >> 1] = sigmoid(avg);
            }
        }
    }
}

void org_conv2_layer(float  input[ORG_POOL1_OUTPUT_NUM][ORG_POOL1_OUTPUT_ROW][ORG_POOL1_OUTPUT_COL], 
                     float output[ORG_CONV2_OUTPUT_NUM][ORG_CONV2_OUTPUT_ROW][ORG_CONV2_OUTPUT_COL])
{
    for (int wn = 0; wn < ORG_CONV2_WEIGHT_NUM; wn++) {
        for (int orow = 0; orow < ORG_CONV2_OUTPUT_ROW; orow++) {
            for (int ocol = 0; ocol < ORG_CONV2_OUTPUT_COL; ocol++) {

                float acc = org_conv2_bias[wn];

                for (int wch = 0; wch < ORG_CONV2_WEIGHT_CH; wch++) {
                    for (int wr = 0; wr < ORG_WEIGHT_ROW; wr++) {
                        for (int wc = 0; wc < ORG_WEIGHT_COL; wc++) {
                            acc += input[wch][orow + wr][ocol + wc] * org_conv2_weight[wn][wch][wr][wc];
                        }   
                    }
                }

                output[wn][orow][ocol] = (float)std::tanh(acc);
            }
        }
    }
}



void org_pool2_layer(float  input[ORG_CONV2_OUTPUT_NUM][ORG_CONV2_OUTPUT_ROW][ORG_CONV2_OUTPUT_COL], 
                     float output[ORG_POOL2_OUTPUT_NUM][ORG_POOL2_OUTPUT_ROW][ORG_POOL2_OUTPUT_COL])
{   

    for (int num = 0; num < ORG_CONV2_OUTPUT_NUM; num++) {
        for (int row = 0; row < ORG_CONV2_OUTPUT_ROW; row += ORG_POOL_STRIDE) {
            for (int col = 0; col < ORG_CONV2_OUTPUT_COL; col += ORG_POOL_STRIDE) {
                
                float avg = 0.0;

                avg += input[num][row][col];
                avg += input[num][row][col + 1];
                avg += input[num][row + 1][col];
                avg += input[num][row + 1][col + 1];

                avg = (float)(avg / 4.0);

                output[num][row >> 1][col >> 1] = sigmoid(avg);
            }
        }
    }
}

void org_conv3_layer(float  input[ORG_POOL2_OUTPUT_NUM][ORG_POOL2_OUTPUT_ROW][ORG_POOL2_OUTPUT_COL], 
                     float output[ORG_CONV3_OUTPUT_SIZE])
{
    for (int wn = 0; wn < ORG_CONV3_WEIGHT_NUM; wn++) {
        
        float acc = org_conv3_bias[wn];

        for (int wch = 0; wch < ORG_CONV3_WEIGHT_CH; wch++) {
            for (int wr = 0; wr < ORG_WEIGHT_ROW; wr++) {
                for (int wc = 0; wc < ORG_WEIGHT_COL; wc++) {
                    acc += input[wch][wr][wc] * org_conv3_weight[wn][wch][wr][wc];
                }
            }
        }

        output[wn] = (float)std::tanh(acc);
    }
}


void org_full1_layer(float  input[ORG_CONV3_OUTPUT_SIZE], 
                     float output[ORG_FULL1_OUTPUT_SIZE])
{
    for (int row = 0; row < ORG_FULL1_WEIGHT_ROW; row++) {

        float acc = org_full1_bias[row];

        for (int col = 0; col < ORG_FULL1_WEIGHT_COL; col++) {
            acc += input[col] * org_full1_weight[row][col];
        }

        output[row] = (float)std::tanh(acc);
    }
}



void org_full2_layer(float  input[ORG_FULL2_OUTPUT_SIZE], 
                     float output[ORG_FULL2_OUTPUT_SIZE])
{
    for (int row = 0; row < ORG_FULL2_WEIGHT_ROW; row++) {
        
        float acc = org_full2_bias[row];
        
        for (int col = 0; col < ORG_FULL2_WEIGHT_COL; col++) {
            acc += input[col] * org_full2_weight[row][col];
        }

        output[row] = (float)std::tanh(acc);
    }
}

float sigmoid(float x) {
    return 1.0 / (1.0 + std::exp(-x));
}

void softmax(float input[ORG_FULL2_OUTPUT_SIZE], u8* output){
    
    float softMaxArr[ORG_FULL2_OUTPUT_SIZE];
    float sum = 0.0;

    for (int i = 0; i < ORG_FULL2_OUTPUT_SIZE; i++) {
        sum += std::exp(input[i]);
    }


    for (int i = 0; i < ORG_FULL2_OUTPUT_SIZE; i++) {
        softMaxArr[i] = std::exp(input[i]) / sum;
    }

    float max = softMaxArr[0];
    u8 maxIndex = 0;
    
    for (int i = 1; i < 10; i++) {
        if (max < softMaxArr[i]) {
            max = softMaxArr[i];
            maxIndex = (u8)i;
        }
    }

    *output = maxIndex;
}