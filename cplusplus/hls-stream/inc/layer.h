#ifndef __LAYER_H__
#define __LAYER_H__

#include "type.h"
#include "parameter.h"
#include "weight.h"
#include "hls_math.h"

void read_input(stream_axis &input, stream_input &input_stream);

void conv1_layer(stream_input &input, stream_conv1 &output);
void pool1_layer(stream_conv1 &input, stream_conv1 &output);
void conv2_layer(stream_conv1 &input, stream_conv2 &output);
void pool2_layer(stream_conv2 &input, stream_conv2 &output);
void conv3_layer(stream_conv2 &input, stream_conv3 &output);
void full1_layer(stream_conv3 &input, stream_full1 &output);
void full2_layer(stream_full1 &input, stream_full2 &output);

void write_output(stream_full2 &input, uint8_t* output);

#endif
