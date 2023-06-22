#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

#include "../../../floating-point/inc/weight.h"
#include "../../../floating-point/inc/parameter.h"


/* Data from ../floating-point/ directory, ./main --all=true commmand */
#define CONV1_MAX   4.71154
#define CONV1_MIN  -2.97152

#define CONV2_MAX   12.2852
#define CONV2_MIN  -20.4851

#define CONV3_MAX   36.0140
#define CONV3_MIN  -33.7252

#define FULL1_MAX   33.5324
#define FULL1_MIN  -14.5665

#define FULL2_MAX   27.2409
#define FULL2_MIN  -30.0438

using namespace std;

int fx_integer(float max, float min) {
    int QI;

    QI = ceil(log2(std::max(abs(max),abs(min)) + 1)) + 1;

    return QI;
}

int main (void) {

    /* For check MAX, MIN value in weights and biases */
    float max_conv1_weight = *max_element((float*)conv1_weight, (float*)conv1_weight + CONV1_WEIGHT_SIZE);
    float max_conv1_bias   = *max_element(conv1_bias  , conv1_bias   + CONV1_BIAS_SIZE);

    float min_conv1_weight = *min_element((float*)conv1_weight, (float*)conv1_weight + CONV1_WEIGHT_SIZE);
    float min_conv1_bias   = *min_element(conv1_bias  , conv1_bias   + CONV1_BIAS_SIZE);

    float max_conv2_weight = *max_element((float*)conv2_weight, (float*)conv2_weight + CONV2_WEIGHT_SIZE);
    float max_conv2_bias   = *max_element(conv2_bias  , conv2_bias   + CONV2_BIAS_SIZE);

    float min_conv2_weight = *min_element((float*)conv2_weight, (float*)conv2_weight + CONV2_WEIGHT_SIZE);
    float min_conv2_bias   = *min_element(conv2_bias  , conv2_bias   + CONV2_BIAS_SIZE);

    float max_conv3_weight = *max_element((float*)conv3_weight, (float*)conv3_weight + CONV3_WEIGHT_SIZE);
    float max_conv3_bias   = *max_element(conv3_bias  , conv3_bias   + CONV3_BIAS_SIZE);

    float min_conv3_weight = *min_element((float*)conv3_weight, (float*)conv3_weight + CONV3_WEIGHT_SIZE);
    float min_conv3_bias   = *min_element(conv3_bias  , conv3_bias   + CONV3_BIAS_SIZE);

    float max_full1_weight = *max_element((float*)full1_weight, (float*)full1_weight + FULL1_WEIGHT_SIZE);
    float max_full1_bias   = *max_element(full1_bias  , full1_bias   + FULL1_BIAS_SIZE);

    float min_full1_weight = *min_element((float*)full1_weight, (float*)full1_weight + FULL1_WEIGHT_SIZE);
    float min_full1_bias   = *min_element(full1_bias  , full1_bias   + FULL1_BIAS_SIZE);

    float max_full2_weight = *max_element((float*)full2_weight, (float*)full2_weight + FULL2_WEIGHT_SIZE);
    float max_full2_bias   = *max_element(full2_bias  , full2_bias   + FULL2_BIAS_SIZE);

    float min_full2_weight = *min_element((float*)full2_weight, (float*)full2_weight + FULL2_WEIGHT_SIZE);
    float min_full2_bias   = *min_element(full2_bias  , full2_bias   + FULL2_BIAS_SIZE);

    /* Determine integer part of output */
    int conv1_output_int = fx_integer(CONV1_MAX, CONV1_MIN);
    int conv2_output_int = fx_integer(CONV2_MAX, CONV2_MIN);
    int conv3_output_int = fx_integer(CONV3_MAX, CONV3_MIN);
    int full1_output_int = fx_integer(FULL1_MAX, FULL1_MIN);
    int full2_output_int = fx_integer(FULL2_MAX, FULL2_MIN);

    /* Determine integer part of weight */
    int conv1_weight_int = fx_integer(max_conv1_weight, min_conv1_weight);
    int conv2_weight_int = fx_integer(max_conv2_weight, min_conv2_weight);
    int conv3_weight_int = fx_integer(max_conv3_weight, min_conv3_weight);
    int full1_weight_int = fx_integer(max_full1_weight, min_full1_weight);
    int full2_weight_int = fx_integer(max_full2_weight, min_full2_weight);

    /* Determine integer part of bias */
    int conv1_bias_int = fx_integer(max_conv1_bias, min_conv1_bias);
    int conv2_bias_int = fx_integer(max_conv2_bias, min_conv2_bias);
    int conv3_bias_int = fx_integer(max_conv3_bias, min_conv3_bias);
    int full1_bias_int = fx_integer(max_full1_bias, min_full1_bias);
    int full2_bias_int = fx_integer(max_full2_bias, min_full2_bias);

    cout << "[CONV1_OUTPUT] integer part : " << conv1_output_int << "\n"; 
    cout << "[CONV2_OUTPUT] integer part : " << conv2_output_int << "\n"; 
    cout << "[CONV3_OUTPUT] integer part : " << conv3_output_int << "\n"; 
    cout << "[FULL1_OUTPUT] integer part : " << full1_output_int << "\n"; 
    cout << "[FULL2_OUTPUT] integer part : " << full2_output_int << "\n";
    cout << "\n";

    cout << "[CONV1_WEIGHT] integer part : " << conv1_weight_int << "\n"; 
    cout << "[CONV2_WEIGHT] integer part : " << conv2_weight_int << "\n"; 
    cout << "[CONV3_WEIGHT] integer part : " << conv3_weight_int << "\n"; 
    cout << "[FULL1_WEIGHT] integer part : " << full1_weight_int << "\n"; 
    cout << "[FULL2_WEIGHT] integer part : " << full2_weight_int << "\n";
    cout << "\n";

    cout << "[CONV1_BIAS]   integer part : " << conv1_bias_int << "\n"; 
    cout << "[CONV2_BIAS]   integer part : " << conv2_bias_int << "\n"; 
    cout << "[CONV3_BIAS]   integer part : " << conv3_bias_int << "\n"; 
    cout << "[FULL1_BIAS]   integer part : " << full1_bias_int << "\n"; 
    cout << "[FULL2_BIAS]   integer part : " << full2_bias_int << "\n";
    cout << "\n";

}