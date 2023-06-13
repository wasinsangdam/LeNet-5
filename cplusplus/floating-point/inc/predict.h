#ifndef __PREDICT_H__
#define __PREDICT_H__

#include "layer.h"
#include "util.h"
#include "weight.h"
#include <algorithm>

/* predict function for determining MAX/MIN value */
int predict(float* input, float* conv1_max, float* conv1_min,
                          float* conv2_max, float* conv2_min,
                          float* conv3_max, float* conv3_min,
                          float* full1_max, float* full1_min,
                          float* full2_max, float* full2_min);

/* Just predict function */
void predict(float* input, bool print_opt);

// uint8_t predict_ref(float* input);

#endif
