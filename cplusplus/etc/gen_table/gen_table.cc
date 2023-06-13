#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <string.h>

#include <ap_fixed.h>

#include "../../floating-point/inc/parameter.h"

#define CONV1_WEIGHT    "../../../data/weight/conv1_weight.data"
#define CONV1_BIAS      "../../../data/bias/conv1_bias.data"
#define CONV2_WEIGHT    "../../../data/weight/conv2_weight.data"
#define CONV2_BIAS      "../../../data/bias/conv2_bias.data"
#define CONV3_WEIGHT    "../../../data/weight/conv3_weight.data"
#define CONV3_BIAS      "../../../data/bias/conv3_bias.data"
#define FULL1_WEIGHT    "../../../data/weight/full1_weight.data"
#define FULL1_BIAS      "../../../data/bias/full1_bias.data"
#define FULL2_WEIGHT    "../../../data/weight/full2_weight.data"
#define FULL2_BIAS      "../../../data/bias/full2_bias.data"

typedef float data_t;


void read_data(std::string file_name, data_t* array, size_t size) {
    std::fstream fs;

    fs.open(file_name);

    if (!fs.is_open()) {
        std::cout << "Open file failed!\n";
        exit(1);
    }

    for (size_t i = 0; i < size; i++) {
        fs >> array[i];
    }
}

void gen_table(std::string d_type, std::string name, data_t* array, size_t size) {
    std::cout << "const ";
    std::cout << d_type << " ";
    std::cout << name;
    std::cout << "[" << size << "] = {\n";

    for (size_t i = 0; i < size; i++) {
        std::cout << std::setw(17) << std::setprecision(10) << array[i];

        if (i != size - 1) std::cout << ", ";
        else               std::cout << "\n};\n";

        if (i % 8 == 7)      std::cout << "\n";
        else if (i % 8 == 1) std::cout << "\t";
    }

    std::cout << "\n";
}

void gen_table_3d(data_t* weight, std::string name, size_t num, size_t row, size_t col) {

    std::cout << "const data_t " << name;
    printf(" [%ld][%ld][%ld] = \n{ ", num, row, col);

    for (size_t i = 0; i < num; i++) {
        if (i == 0) printf("{ ");
        else        printf("  { ");

        for (size_t j = 0; j < row; j++) {
            if (j == 0) printf("{");
            else        printf("    {");

            for (size_t k = 0; k < col; k++) {
                if (k == col - 1) printf("%17.10f ", weight[i * row * col + j * col + k]);
                else              printf("%17.10f , ", weight[i * row * col + j * col + k]);
            }
            if (j == row - 1) printf("} ");
            else              printf("}, \n");
        }
        if (i == num - 1) printf("} ");
        else              printf("}, \n\n");
    }

    printf("};");
    printf("\n\n");
}

void gen_table_4d(data_t* weight, std::string name, size_t num, size_t ch, size_t row, size_t col) {

    std::cout << "const data_t " << name;
    printf(" [%ld][%ld][%ld][%ld] = \n{ ", num, ch, row, col);

    for (size_t n = 0; n < num; n++) {
        if (n == 0) printf("{ ");
        else        printf("  { ");

        for (size_t c = 0; c < ch; c++) {
            if (c == 0) printf("{ ");
            else        printf("   { ");

            for (size_t r = 0; r < row; r++) {
                if (r == 0) printf(" {");
                else        printf("      {");

                for (size_t k = 0; k < col; k++) {
                    if (k == col - 1) printf("%17.10f ",   weight[(n * ch * row * col) + (c * row * col) + (r * col) + k]);
                    else              printf("%17.10f , ", weight[(n * ch * row * col) + (c * row * col) + (r * col) + k]);
                }
                if (r == row - 1) printf("  } ");
                else              printf("  }, \n");
            }
            if (c == ch - 1) printf("} ");
            else             printf("}, \n\n");
        }
        if (n == num - 1) printf("} ");
        else              printf("}, \n\n");
    }

    printf("};");
    printf("\n\n");
}

void gen_table_2d(data_t* weight, std::string name, size_t row, size_t col) {
    
    std::cout << "const data_t " << name;
    printf(" [%ld][%ld] = \n{ ", row, col);

    for (size_t i = 0; i < row; i++) {
        if (i == 0) printf("{");
        else        printf("  {");

        for (size_t j = 0; j < col; j++) {
            if (j == col - 1) printf("%17.10f ", weight[i * col + j]);
            else              printf("%17.10f , ", weight[i * col + j]);

            if (j % 6 == 5) printf("\n   ");
        }
        if (i == row - 1) printf("} ");
        else              printf("}, \n\n");
    }

    printf("};");
    printf("\n\n");
}



int main (void) {
    data_t conv1_weight[CONV1_WEIGHT_SIZE];
    data_t conv2_weight[CONV2_WEIGHT_SIZE];
    data_t conv3_weight[CONV3_WEIGHT_SIZE];

    data_t full1_weight[FULL1_WEIGHT_SIZE];
    data_t full2_weight[FULL2_WEIGHT_SIZE];

    data_t conv1_bias[CONV1_BIAS_SIZE];
    data_t conv2_bias[CONV2_BIAS_SIZE];
    data_t conv3_bias[CONV3_BIAS_SIZE];

    data_t full1_bias[FULL1_BIAS_SIZE];
    data_t full2_bias[FULL2_BIAS_SIZE];

    read_data(CONV1_WEIGHT, conv1_weight, CONV1_WEIGHT_SIZE);
    read_data(CONV1_BIAS  , conv1_bias  , CONV1_BIAS_SIZE);

    read_data(CONV2_WEIGHT, conv2_weight, CONV2_WEIGHT_SIZE);
    read_data(CONV2_BIAS  , conv2_bias  , CONV2_BIAS_SIZE);

    read_data(CONV3_WEIGHT, conv3_weight, CONV3_WEIGHT_SIZE);
    read_data(CONV3_BIAS  , conv3_bias  , CONV3_BIAS_SIZE);

    read_data(FULL1_WEIGHT, full1_weight, FULL1_WEIGHT_SIZE);
    read_data(FULL1_BIAS  , full1_bias  , FULL1_BIAS_SIZE);

    read_data(FULL2_WEIGHT, full2_weight, FULL2_WEIGHT_SIZE);
    read_data(FULL2_BIAS  , full2_bias  , FULL2_BIAS_SIZE);

    // gen_table("data_t", "conv1_weight", conv1_weight, CONV1_WEIGHT_SIZE);
    // gen_table("data_t", "conv2_weight", conv2_weight, CONV2_WEIGHT_SIZE);
    // gen_table("data_t", "conv3_weight", conv3_weight, CONV3_WEIGHT_SIZE);

    // gen_table("data_t", "full1_weight", full1_weight, FULL1_WEIGHT_SIZE);
    // gen_table("data_t", "full2_weight", full2_weight, FULL2_WEIGHT_SIZE);

    // gen_table("data_t", "conv1_bias", conv1_bias, CONV1_BIAS_SIZE);
    // gen_table("data_t", "conv2_bias", conv2_bias, CONV2_BIAS_SIZE);
    // gen_table("data_t", "conv3_bias", conv3_bias, CONV3_BIAS_SIZE);

    // gen_table("data_t", "full1_bias", full1_bias, FULL1_BIAS_SIZE);
    // gen_table("data_t", "full2_bias", full2_bias, FULL2_BIAS_SIZE);

    gen_table_3d(conv1_weight, "conv1_weight", CONV1_WEIGHT_NUM, WEIGHT_ROW, WEIGHT_COL);
    gen_table_4d(conv2_weight, "conv2_weight", CONV2_WEIGHT_NUM, CONV2_WEIGHT_CH, WEIGHT_ROW, WEIGHT_COL);
    gen_table_4d(conv3_weight, "conv3_weight", CONV3_WEIGHT_NUM, CONV3_WEIGHT_CH, WEIGHT_ROW, WEIGHT_COL);
    
    gen_table_2d(full1_weight, "full1_weight", FULL1_WEIGHT_ROW, FULL1_WEIGHT_COL);
    gen_table_2d(full2_weight, "full2_weight", FULL2_WEIGHT_ROW, FULL2_WEIGHT_COL);

    
   //  typedef ap_fixed<16, 2, AP_RND, AP_SAT> weight_t;
    
   //  for (size_t n = 0; n < CONV2_WEIGHT_NUM; n++) {
   //      for (size_t ch = 0; ch < CONV2_WEIGHT_CH; ch++) {
   //          for (size_t i = 0; i < WEIGHT_ROW; i++) {
   //              for (size_t j = 0; j < WEIGHT_COL; j++) {
   //                  weight_t temp;
   //                  temp = (weight_t)conv2_weight_4d[n][ch][i][j];

   //                  std::cout << temp << " ";
   //              }
   //              std::cout << "\n";
   //          }
   //          std::cout << "\n";
   //      }
   //      std::cout << "\n";
   //  }
   //  std::cout << "\n";


}