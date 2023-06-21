#ifndef __TYPE_H__
#define __TYPE_H__

#include <ap_fixed.h>
#include <hls_stream.h>
#include <ap_axi_sdata.h>

/*  
    For an equation for determining the bits of integer part
    and fractional part, refer to the ../etc/data_type directory. 

    Input has only a value from 0 to 1.
    
    Temporary fixed-point data type with enough width 
    to prevent saturation/overflow and avoid any loss of 
    precision while accumulating the sum over all products. [2*QI, 2*QF]  
*/

typedef ap_axiu<16, 0, 0, 0> axis_t;                    // Data types for AXI streaming with side-channel

typedef ap_ufixed<16,  1, AP_RND, AP_SAT> input_t;

typedef  ap_fixed<16,  2, AP_RND, AP_SAT> weight_t;

typedef  ap_fixed<16,  4, AP_RND, AP_SAT> conv1_t;      // Integer part : 4,  Fractional part : 12
typedef  ap_fixed<16,  5, AP_RND, AP_SAT> conv2_t;      // Integer part : 5,  Fractional part : 11
typedef  ap_fixed<16,  7, AP_RND, AP_SAT> conv3_t;      // Integer part : 7,  Fractional part : 9
typedef  ap_fixed<16,  7, AP_RND, AP_SAT> full1_t;      // Integer part : 7,  Fractional part : 9
typedef  ap_fixed<16,  7, AP_RND, AP_SAT> full2_t;      // Integer part : 7,  Fractional part : 9

typedef  ap_fixed<32,  8, AP_RND, AP_SAT> conv1_temp;   // Integer part : 8,  Fractional part : 24
typedef  ap_fixed<32, 10, AP_RND, AP_SAT> conv2_temp;   // Integer part : 10, Fractional part : 22
typedef  ap_fixed<32, 14, AP_RND, AP_SAT> conv3_temp;   // Integer part : 14, Fractional part : 18
typedef  ap_fixed<32, 14, AP_RND, AP_SAT> full1_temp;   // Integer part : 14, Fractional part : 18
typedef  ap_fixed<32, 14, AP_RND, AP_SAT> full2_temp;   // Integer part : 14, Fractional part : 18

typedef hls::stream<axis_t> stream_axis;                // Stream data types for AXI streaming with side-channel

typedef hls::stream<input_t> stream_input;
typedef hls::stream<conv1_t> stream_conv1;
typedef hls::stream<conv2_t> stream_conv2;
typedef hls::stream<conv3_t> stream_conv3;
typedef hls::stream<full1_t> stream_full1;
typedef hls::stream<full2_t> stream_full2;
typedef hls::stream<uint8_t> stream_output;

#endif