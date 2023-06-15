#include "../inc/predict.h"

void predict(stream_axis &input, uint8_t* output) {
    #pragma HLS INTERFACE axis port=input

    #pragma HLS INTERFACE s_axilite     port=output bundle=CONTROL_BUS
    #pragma HLS INTERFACE s_axilite     port=return	bundle=CONTROL_BUS
    #pragma HLS INTERFACE ap_ctrl_chain port=return bundle=CONTROL_BUS

    #pragma HLS DATAFLOW

    stream_input input_stream;
    
    stream_conv1 conv1_stream;
    stream_conv1 pool1_stream;

    stream_conv2 conv2_stream;
    stream_conv2 pool2_stream;

    stream_conv3 conv3_stream;

    stream_full1 full1_stream;
    
    stream_full2 full2_stream;

    read_input(input, input_stream);

    /* 1st CONV layer */
    conv1_layer(input_stream, conv1_stream);

    /* 1st POOL layer */
    pool1_layer(conv1_stream, pool1_stream);

    /* 2nd CONV layer */
    conv2_layer(pool1_stream, conv2_stream);

    /* 2nd POOL layer */
    pool2_layer(conv2_stream, pool2_stream);

    /* 3rd CONV layer */
    conv3_layer(pool2_stream, conv3_stream);

    /* 1st FULL layer */
    full1_layer(conv3_stream, full1_stream);
    
    /* 2nd FULL layer */
    full2_layer(full1_stream, full2_stream);

    /* Return result */
    write_output(full2_stream, output);
}