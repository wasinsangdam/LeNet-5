#ifndef __LAYER_H__
#define __LAYER_H__

#include "type.h"
#include "parameter.h"
#include "weight.h"
#include "hls_math.h"

void read_input(stream_axis &input, stream_input &sub0,
                                    stream_input &sub1,
                                    stream_input &sub2);

void sub0_conv1_layer(stream_input &input, stream_conv1 &output);
void sub1_conv1_layer(stream_input &input, stream_conv1 &output);
void sub2_conv1_layer(stream_input &input, stream_conv1 &output);

void pool1_layer(stream_conv1  &input0, stream_conv1  &input1, stream_conv1  &input2, 
                 stream_conv1 &output0, stream_conv1 &output1, stream_conv1 &output2,
                 stream_conv1 &output3, stream_conv1 &output4, stream_conv1 &output5);

void sub0_conv2_layer(stream_conv1 &input, stream_conv2 &output);
void sub1_conv2_layer(stream_conv1 &input, stream_conv2 &output);
void sub2_conv2_layer(stream_conv1 &input, stream_conv2 &output);
void sub3_conv2_layer(stream_conv1 &input, stream_conv2 &output);
void sub4_conv2_layer(stream_conv1 &input, stream_conv2 &output);
void sub5_conv2_layer(stream_conv1 &input, stream_conv2 &output);

void pool2_layer(stream_conv2 &input0,
                 stream_conv2 &input1,
                 stream_conv2 &input2, 
                 stream_conv2 &input3, 
                 stream_conv2 &input4,
                 stream_conv2 &input5, stream_conv2 &output);

void conv3_layer(stream_conv2 &input, stream_conv3 &output);

void full1_layer(stream_conv3 &input, stream_full1 &output);
void full2_layer(stream_full1 &input, stream_full2 &output);

void write_output(stream_full2 &input, uint8_t* output);

#endif
