#include "../inc/layer.h"

void read_input(axis_input &input, stream_input &sub0,
                                   stream_input &sub1,
                                   stream_input &sub2) {

    axis_i temp_axis;
    input_t temp_input;

    for (int i = 0; i < IMAGE_SIZE; i++) {
        temp_axis = input.read();
        temp_input.range() = temp_axis.data.range();

        sub0.write(temp_input);
        sub1.write(temp_input);
        sub2.write(temp_input);
    }
}

void sub0_conv1_layer(stream_input &input, stream_conv1 &output) {

    input_t input_2d[IMAGE_ROW][IMAGE_COL] = { 0, };

    for (int i = 0; i < IMAGE_ROW; i++) {
        for (int j = 0; j < IMAGE_COL; j++) {
			// #pragma HLS PIPELINE II=1
            input_2d[i][j] = input.read();
        }
    }

    for (int orow = 0; orow < CONV1_OUTPUT_ROW; orow++) {
        for (int ocol = 0; ocol < CONV1_OUTPUT_COL; ocol++) {

            conv1_temp acc = conv1_bias[0];

            for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                for (int wc = 0; wc < WEIGHT_COL; wc++) {
                    
                    // #pragma HLS UNROLL
                    acc += (conv1_temp)(input_2d[orow + wr][ocol + wc] * conv1_weight_sub0[wr][wc]);
                }
            }

            if (acc > 0) output.write((conv1_t)acc);
            else         output.write((conv1_t)0.0);
        }
    }
}

void sub1_conv1_layer(stream_input &input, stream_conv1 &output) {

    input_t input_2d[IMAGE_ROW][IMAGE_COL] = { 0, };

    for (int i = 0; i < IMAGE_ROW; i++) {
        for (int j = 0; j < IMAGE_COL; j++) {
            // #pragma HLS PIPELINE II=1
            input_2d[i][j] = input.read();
        }
    }

    for (int orow = 0; orow < CONV1_OUTPUT_ROW; orow++) {
        for (int ocol = 0; ocol < CONV1_OUTPUT_COL; ocol++) {

            conv1_temp acc = conv1_bias[1];

            for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                for (int wc = 0; wc < WEIGHT_COL; wc++) {
                    
                    // #pragma HLS UNROLL
                    acc += (conv1_temp)(input_2d[orow + wr][ocol + wc] * conv1_weight_sub1[wr][wc]);
                }
            }

            if (acc > 0) output.write((conv1_t)acc);
            else         output.write((conv1_t)0.0);
        }
    }
}

void sub2_conv1_layer(stream_input &input, stream_conv1 &output) {

    input_t input_2d[IMAGE_ROW][IMAGE_COL] = { 0, };

    for (int i = 0; i < IMAGE_ROW; i++) {
        for (int j = 0; j < IMAGE_COL; j++) {
            // #pragma HLS PIPELINE II=1
            input_2d[i][j] = input.read();
        }
    }

    for (int orow = 0; orow < CONV1_OUTPUT_ROW; orow++) {
        for (int ocol = 0; ocol < CONV1_OUTPUT_COL; ocol++) {

            conv1_temp acc = conv1_bias[2];

            for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                for (int wc = 0; wc < WEIGHT_COL; wc++) {
                    
                    // #pragma HLS UNROLL
                    acc += (conv1_temp)(input_2d[orow + wr][ocol + wc] * conv1_weight_sub2[wr][wc]);
                }
            }

            if (acc > 0) output.write((conv1_t)acc);
            else         output.write((conv1_t)0.0);
        }
    }
}

void pool1_layer(stream_conv1  &input0, stream_conv1  &input1, stream_conv1  &input2, 
                 stream_conv1 &output0, stream_conv1 &output1, stream_conv1 &output2,
                 stream_conv1 &output3, stream_conv1 &output4, stream_conv1 &output5) 
{
    conv1_t input_3d[CONV1_OUTPUT_NUM][CONV1_OUTPUT_ROW][CONV1_OUTPUT_COL] = { 0, };
    
    for (int k = 0; k < CONV1_OUTPUT_NUM; k++) {
        for (int i = 0; i < CONV1_OUTPUT_ROW; i++) {
            for (int j = 0; j < CONV1_OUTPUT_COL; j++) {
                if      (k == 0) input_3d[k][i][j] = input0.read();
                else if (k == 1) input_3d[k][i][j] = input1.read();
                else             input_3d[k][i][j] = input2.read();
            }
        }
    }

    for (int num = 0; num < CONV1_OUTPUT_NUM; num++) {
        for (int row = 0; row < CONV1_OUTPUT_ROW; row += POOL_STRIDE) {
            for (int col = 0; col < CONV1_OUTPUT_COL; col += POOL_STRIDE) {
                conv1_t n1 = input_3d[num][row][col];
                conv1_t n2 = input_3d[num][row][col + 1];
                conv1_t n3 = input_3d[num][row + 1][col];
                conv1_t n4 = input_3d[num][row + 1][col + 1];

                conv1_t max1 = hls::max(n1, n2);
                conv1_t max2 = hls::max(n3, n4);

                conv1_t max = hls::max(max1, max2);

                output0.write(max);
                output1.write(max);
                output2.write(max);
                output3.write(max);
                output4.write(max);
                output5.write(max);
                
            }
        }
    }
}

void sub0_conv2_layer(stream_conv1 &input, stream_conv2 &output) {

    conv1_t input_3d[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL] = { 0, };

    for (int k = 0; k < POOL1_OUTPUT_NUM; k++) {
        for (int i = 0; i < POOL1_OUTPUT_ROW; i++) {
            for (int j = 0; j < POOL1_OUTPUT_COL; j++) {
                // #pragma HLS PIPELINE II=1
                input_3d[k][i][j] = input.read();
            }
        }
    }

    for (int orow = 0; orow < CONV2_OUTPUT_ROW; orow++) {
        for (int ocol = 0; ocol < CONV2_OUTPUT_COL; ocol++) {

            conv2_temp acc = conv2_bias[0];

            for (int wch = 0; wch < CONV2_WEIGHT_CH; wch++) {
                for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                    for (int wc = 0; wc < WEIGHT_COL; wc++) {
                            
                        // #pragma HLS UNROLL
                        acc += (conv2_temp)(input_3d[wch][orow + wr][ocol + wc] * conv2_weight_sub0[wch][wr][wc]);
                    }
                }
            }
            if (acc > 0) output.write((conv2_t)acc);
            else         output.write((conv2_t)0.0);
        }
    }
}
    

void sub1_conv2_layer(stream_conv1 &input, stream_conv2 &output) {
    conv1_t input_3d[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL] = { 0, };

    for (int k = 0; k < POOL1_OUTPUT_NUM; k++) {
        for (int i = 0; i < POOL1_OUTPUT_ROW; i++) {
            for (int j = 0; j < POOL1_OUTPUT_COL; j++) {
                // #pragma HLS PIPELINE II=1
                input_3d[k][i][j] = input.read();
            }
        }
    }

    for (int orow = 0; orow < CONV2_OUTPUT_ROW; orow++) {
        for (int ocol = 0; ocol < CONV2_OUTPUT_COL; ocol++) {

            conv2_temp acc = conv2_bias[1];

            for (int wch = 0; wch < CONV2_WEIGHT_CH; wch++) {
                for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                    for (int wc = 0; wc < WEIGHT_COL; wc++) {
                            
                        // #pragma HLS UNROLL
                        acc += (conv2_temp)(input_3d[wch][orow + wr][ocol + wc] * conv2_weight_sub1[wch][wr][wc]);
                    }
                }
            }
            
            if (acc > 0) output.write((conv2_t)acc);
            else         output.write((conv2_t)0.0);   
        }
    }
}

void sub2_conv2_layer(stream_conv1 &input, stream_conv2 &output) {
    conv1_t input_3d[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL] = { 0, };

    for (int k = 0; k < POOL1_OUTPUT_NUM; k++) {
        for (int i = 0; i < POOL1_OUTPUT_ROW; i++) {
            for (int j = 0; j < POOL1_OUTPUT_COL; j++) {
                // #pragma HLS PIPELINE II=1
                input_3d[k][i][j] = input.read();
            }
        }
    }

    for (int orow = 0; orow < CONV2_OUTPUT_ROW; orow++) {
        for (int ocol = 0; ocol < CONV2_OUTPUT_COL; ocol++) {

            conv2_temp acc = conv2_bias[2];

            for (int wch = 0; wch < CONV2_WEIGHT_CH; wch++) {
                for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                    for (int wc = 0; wc < WEIGHT_COL; wc++) {
                            
                        // #pragma HLS UNROLL
                        acc += (conv2_temp)(input_3d[wch][orow + wr][ocol + wc] * conv2_weight_sub2[wch][wr][wc]);
                    }
                }
            }
            if (acc > 0) output.write((conv2_t)acc);
            else         output.write((conv2_t)0.0);   
        }
    }
}

void sub3_conv2_layer(stream_conv1 &input, stream_conv2 &output) {
    conv1_t input_3d[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL] = { 0, };

    for (int k = 0; k < POOL1_OUTPUT_NUM; k++) {
        for (int i = 0; i < POOL1_OUTPUT_ROW; i++) {
            for (int j = 0; j < POOL1_OUTPUT_COL; j++) {
                // #pragma HLS PIPELINE II=1
                input_3d[k][i][j] = input.read();
            }
        }
    }

    for (int orow = 0; orow < CONV2_OUTPUT_ROW; orow++) {
        for (int ocol = 0; ocol < CONV2_OUTPUT_COL; ocol++) {

            conv2_temp acc = conv2_bias[3];

            for (int wch = 0; wch < CONV2_WEIGHT_CH; wch++) {
                for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                    for (int wc = 0; wc < WEIGHT_COL; wc++) {
                        // #pragma HLS UNROLL
                        acc += (conv2_temp)(input_3d[wch][orow + wr][ocol + wc] * conv2_weight_sub3[wch][wr][wc]);
                    }
                }
            }
            if (acc > 0) output.write((conv2_t)acc);
            else         output.write((conv2_t)0.0);
        }
    }
}

void sub4_conv2_layer(stream_conv1 &input, stream_conv2 &output) {
    conv1_t input_3d[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL] = { 0, };

    for (int k = 0; k < POOL1_OUTPUT_NUM; k++) {
        for (int i = 0; i < POOL1_OUTPUT_ROW; i++) {
            for (int j = 0; j < POOL1_OUTPUT_COL; j++) {
                // #pragma HLS PIPELINE II=1
                input_3d[k][i][j] = input.read();
            }
        }
    }

    for (int orow = 0; orow < CONV2_OUTPUT_ROW; orow++) {
        for (int ocol = 0; ocol < CONV2_OUTPUT_COL; ocol++) {

            conv2_temp acc = conv2_bias[4];

            for (int wch = 0; wch < CONV2_WEIGHT_CH; wch++) {
                for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                    for (int wc = 0; wc < WEIGHT_COL; wc++) {
                        // #pragma HLS UNROLL
                        acc += (conv2_temp)(input_3d[wch][orow + wr][ocol + wc] * conv2_weight_sub4[wch][wr][wc]);
                    }
                }
            }
            if (acc > 0) output.write((conv2_t)acc);
            else         output.write((conv2_t)0.0);
        }
    }
}

void sub5_conv2_layer(stream_conv1 &input, stream_conv2 &output) {
    conv1_t input_3d[POOL1_OUTPUT_NUM][POOL1_OUTPUT_ROW][POOL1_OUTPUT_COL] = { 0, };

    for (int k = 0; k < POOL1_OUTPUT_NUM; k++) {
        for (int i = 0; i < POOL1_OUTPUT_ROW; i++) {
            for (int j = 0; j < POOL1_OUTPUT_COL; j++) {
                // #pragma HLS PIPELINE II=1
                input_3d[k][i][j] = input.read();
            }
        }
    }

    for (int orow = 0; orow < CONV2_OUTPUT_ROW; orow++) {
        for (int ocol = 0; ocol < CONV2_OUTPUT_COL; ocol++) {

            conv2_temp acc = conv2_bias[5];

            for (int wch = 0; wch < CONV2_WEIGHT_CH; wch++) {
                for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                    for (int wc = 0; wc < WEIGHT_COL; wc++) {
                        // #pragma HLS UNROLL
                        acc += (conv2_temp)(input_3d[wch][orow + wr][ocol + wc] * conv2_weight_sub5[wch][wr][wc]);
                    }
                }
            }
            if (acc > 0) output.write((conv2_t)acc);
            else         output.write((conv2_t)0.0);
        }
    }
}


void pool2_layer(stream_conv2 &input0,
                 stream_conv2 &input1,
                 stream_conv2 &input2, 
                 stream_conv2 &input3,
                 stream_conv2 &input4, 
                 stream_conv2 &input5, stream_conv2 &output) 
{
    conv2_t input_3d[CONV2_OUTPUT_NUM][CONV2_OUTPUT_ROW][CONV2_OUTPUT_COL] = { 0, };

    for (int k = 0; k < CONV2_OUTPUT_NUM; k++) {
        for (int i = 0; i < CONV2_OUTPUT_ROW; i++) {
            for (int j = 0; j < CONV2_OUTPUT_COL; j++) {
                if      (k == 0) input_3d[k][i][j] = input0.read();
                else if (k == 1) input_3d[k][i][j] = input1.read();
                else if (k == 2) input_3d[k][i][j] = input2.read();
                else if (k == 3) input_3d[k][i][j] = input3.read();
                else if (k == 4) input_3d[k][i][j] = input4.read();
                else             input_3d[k][i][j] = input5.read();
                
            }
        }
    }

    for (int num = 0; num < CONV2_OUTPUT_NUM; num++) {
        for (int row = 0; row < CONV2_OUTPUT_ROW; row += POOL_STRIDE) {
            for (int col = 0; col < CONV2_OUTPUT_COL; col += POOL_STRIDE) {
                conv2_t n1 = input_3d[num][row][col];
                conv2_t n2 = input_3d[num][row][col + 1];
                conv2_t n3 = input_3d[num][row + 1][col];
                conv2_t n4 = input_3d[num][row + 1][col + 1];

                conv2_t max1 = hls::max(n1, n2);
                conv2_t max2 = hls::max(n3, n4);

                conv2_t max = hls::max(max1, max2);

                output.write(max);
            }
        }
    }
}

void conv3_layer(stream_conv2 &input, stream_conv3 &output) {

    conv2_t input_3d[POOL2_OUTPUT_NUM][POOL2_OUTPUT_ROW][POOL2_OUTPUT_COL] = { 0, };

    for (int k = 0; k < POOL2_OUTPUT_NUM; k++) {
        for (int i = 0; i < POOL2_OUTPUT_ROW; i++) {
            for (int j = 0; j < POOL2_OUTPUT_COL; j++) {
                input_3d[k][i][j] = input.read();
            }
        }
    }

    for (int wn = 0; wn < CONV3_WEIGHT_NUM; wn++) {

        conv3_temp acc = conv3_bias[wn];

        for (int wch = 0; wch < CONV3_WEIGHT_CH; wch++) {
            for (int wr = 0; wr < WEIGHT_ROW; wr++) {
                for (int wc = 0; wc < WEIGHT_COL; wc++) {
                    acc += (conv3_temp)(input_3d[wch][wr][wc] * conv3_weight[wn][wch][wr][wc]);
                }
            }
        }

        if (acc > 0) output.write((conv3_t)acc);
        else         output.write((conv3_t)0.0);

    }
}

void full1_layer(stream_conv3 &input, stream_full1 &output) {
    conv3_t input_1d[CONV3_OUTPUT_NUM] = { 0, };

    for (int i = 0; i < CONV3_OUTPUT_NUM; i++) {
        input_1d[i] = input.read();
    }

    for (int row = 0; row < FULL1_WEIGHT_ROW; row++) {
        full1_temp acc = full1_bias[row];

        for (int col = 0; col < FULL1_WEIGHT_COL; col++) {
            acc += (full1_temp)(input_1d[col] * full1_weight[row][col]);
        }

        if (acc > 0) output.write((full1_t)acc);
        else         output.write((full1_t)0.0);

    }
}

void full2_layer(stream_full1 &input, stream_full2 &output) {
    full1_t input_1d[FULL1_OUTPUT_SIZE] = { 0, };

    for (int i = 0; i < FULL1_OUTPUT_SIZE; i++) {
        input_1d[i] = input.read();
    }


    for (int row = 0; row < FULL2_WEIGHT_ROW; row++) {
        full2_temp acc = full2_bias[row];

        for (int col = 0; col < FULL2_WEIGHT_COL; col++) {
            acc += (full2_temp)(input_1d[col] * full2_weight[row][col]);
        }

        output.write(acc);
    }
}

void write_output(stream_full2 &input, uint8_t* output) {

    full2_t input_1d[FULL2_OUTPUT_SIZE] = { 0, };

    for (int i = 0; i < FULL2_OUTPUT_SIZE; i++) {
        input_1d[i] = input.read();
    }

    full2_t max = input_1d[0];

    uint8_t max_index = 0;

    for (int i = 1; i < 10; i++) {
        if (max < input_1d[i]) {
            max = input_1d[i];
            max_index = (uint8_t)i;
        }
    }

    *output = (uint8_t)max_index;
}
