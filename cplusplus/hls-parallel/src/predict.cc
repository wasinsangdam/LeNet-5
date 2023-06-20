#include "../inc/predict.h"

void predict(stream_axis &input, uint8_t* output_r) {

    stream_input sub0_input;
    stream_input sub1_input;
    stream_input sub2_input;

    stream_conv1 sub0_conv1;
    stream_conv1 sub1_conv1;
    stream_conv1 sub2_conv1;

    stream_conv1 sub0_pool1;
    stream_conv1 sub1_pool1;
    stream_conv1 sub2_pool1;
    stream_conv1 sub3_pool1;
    stream_conv1 sub4_pool1;
    stream_conv1 sub5_pool1;

    stream_conv2 sub0_conv2;
    stream_conv2 sub1_conv2;
    stream_conv2 sub2_conv2;
    stream_conv2 sub3_conv2;
    stream_conv2 sub4_conv2;
    stream_conv2 sub5_conv2;

    stream_conv2 pool2_stream;

    stream_conv3 conv3_stream;

    stream_full1 full1_stream;

    stream_full2 full2_stream;

    read_input(input, sub0_input,
                      sub1_input,
                      sub2_input);

    /* 1st CONV layer */
    sub0_conv1_layer(sub0_input, sub0_conv1);
    sub1_conv1_layer(sub1_input, sub1_conv1);
    sub2_conv1_layer(sub2_input, sub2_conv1);


    /* 1st POOL layer */
    pool1_layer(sub0_conv1, sub1_conv1, sub2_conv1, 
                sub0_pool1, sub1_pool1, sub2_pool1,
                sub3_pool1, sub4_pool1, sub5_pool1);

    /* 2nd CONV layer */
    sub0_conv2_layer(sub0_pool1, sub0_conv2);
    sub1_conv2_layer(sub1_pool1, sub1_conv2);
    sub2_conv2_layer(sub2_pool1, sub2_conv2);
    sub3_conv2_layer(sub3_pool1, sub3_conv2);
    sub4_conv2_layer(sub4_pool1, sub4_conv2);
    sub5_conv2_layer(sub5_pool1, sub5_conv2);


    /* 2nd POOL layer */
    pool2_layer(sub0_conv2,
                sub1_conv2,
                sub2_conv2, 
                sub3_conv2,
                sub4_conv2,
                sub5_conv2, pool2_stream);

    /* 3rd CONV layer */
    conv3_layer(pool2_stream, conv3_stream);

    /* 1st FULL layer */
    full1_layer(conv3_stream, full1_stream);

    /* 2nd FULL layer */
    full2_layer(full1_stream, full2_stream);

    /* Return result */
    write_output(full2_stream, output_r);
}
