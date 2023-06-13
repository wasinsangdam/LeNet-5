#include "../inc/util.h"
#include "../inc/color.h"

void read_data(std::string file_name, float* array, size_t size) {
    std::fstream fs;

    fs.open(file_name);

    if (!fs.is_open()) {
        std::cout << "Open file failed!\n";
        exit(1);
    }

    for (size_t i = 0; i < size; i++) {
        fs >> array[i];
    }
    fs.close();
}


void print_3d(std::string name, float* array, size_t num, size_t row, size_t col, bool flag) {

    if (!flag) return;

    std::cout << "[" << name << "] ";
    printf("[%ld][%ld][%ld]\n\n", num, row, col);
    printf("================================================================================================================================================================\n\n");
    
    for (size_t i = 0; i < num; i++) {
        for (size_t j = 0; j < row; j++) {
            for (size_t k = 0; k < col; k++) { 
                if (array[(i * row * col) + (j * col) + k] > 0.0 ) 
                    printf(ANSI_COLOR_CYAN "%5.2f" ANSI_COLOR_RESET, *(array + (i * row * col) + (j * col) + k));
                    // printf(ANSI_COLOR_CYAN "%5.2f" ANSI_COLOR_RESET, array[(i * row * col) + (j * col) + k]);
                    // printf(ANSI_COLOR_CYAN "%s", ANSI_COLOR_RESET, array[(i * row * col) + (j * col) + k].to_string(10));
                else 
                    printf("%5.2f", *(array + (i * row * col) + (j * col) + k));
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

    printf("================================================================================================================================================================\n\n");
}

void print_1d(std::string name, float*array, size_t num, bool flag) {
    
    if (!flag) return;

    std::cout << "[" << name << "] ";
    printf("[%ld]\n\n", num);
    printf("================================================================================================================================================================\n\n");

    for (size_t i = 0; i < num; i++) {
        if (array[i] > 0.0) printf(ANSI_COLOR_CYAN "%7.2f" ANSI_COLOR_RESET, array[i]);
        else                printf("%7.2f", array[i]);

        if ((i % 12) == 11) printf("\n");
    }
    printf("\n");
    printf("================================================================================================================================================================\n\n");

}

void print_result(float* array) {
    float max = array[0];

    int max_index = 0;

    for (size_t i = 1; i < 10; i++) {
        if (max < array[i]) {
            max = array[i];
            max_index = i;
        }
    }
    printf("Number : %d\n", max_index);
}

void read_answer(std::string file_name, int* array, size_t size) {
    std::fstream fs;

    fs.open(file_name);

    if (!fs.is_open()) {
        std::cout << "Open file failed!\n";
        exit(1);
    }

    for (size_t i = 0; i < size; i++) {
        fs >> array[i];
    }

    fs.close();
}

