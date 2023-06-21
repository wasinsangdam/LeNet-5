#include <hls_math.h>
#include <ap_fixed.h>

#define NUM 32

typedef int   data_t;
//typedef short data_t;
//typedef float data_t;
// typedef half  data_t;
//typedef ap_fixed<32, 16> data_t;
//typedef ap_fixed<16, 8> data_t;

void mac(data_t input[NUM], data_t weight[NUM][NUM], data_t bias[NUM], data_t output[NUM]) {


	for (int i = 0; i < NUM; i++) {

		data_t result = bias[i];

		for (int j = 0; j < NUM; j++) {
			result += input[j] * weight[i][j];
		}

		output[i] = result;
	}
}
