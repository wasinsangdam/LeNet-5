#include "sdCard.h"

static FATFS fatfs;

int sdInit() {
    FRESULT fr;

    const char* path = "0:/";

    fr = f_mount(&fatfs, path, 0);
    if (fr) {
        printf("[ERROR] f_mount(sdInit) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    return XST_SUCCESS;
}

int sdEject() {
    
    FRESULT fr;
    
    const char* path = "0:/";
    
    fr = f_mount(&fatfs, path, 1);
    if (fr) {
        printf("[ERROR] f_mount(sdEject) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    return XST_SUCCESS;
}

int readFileFixed(char *fileName, u16* destAddr) {
    FIL file;
    FRESULT fr;
    FILINFO fi;
    UINT br;
    u32 fileSize;

    fr = f_stat(fileName, &fi);
    if (fr) {
        printf("[ERROR] f_stat(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }


    fr = f_open(&file, fileName, FA_READ);
    if (fr) {
        printf("[ERROR] f_open(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    
    fileSize = fi.fsize;

    fr = f_lseek(&file, 0);
    if (fr) {
        printf("[ERROR] f_lseek(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    fr = f_read(&file, (void*)destAddr, fileSize, &br);
    if (fr) {
        printf("[ERROR] f_read(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    fr = f_close(&file);
    if (fr) {
        printf("[ERROR] f_close(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    Xil_DCacheFlush();
    return XST_SUCCESS;
}

int readFileFloat(char *fileName, float* destAddr) {
    FIL file;
    FRESULT fr;
    FILINFO fi;
    UINT br;
    u32 fileSize;

    fr = f_stat(fileName, &fi);
    if (fr) {
        printf("[ERROR] f_stat(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    fr = f_open(&file, fileName, FA_READ);
    if (fr) {
        printf("[ERROR] f_open(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    fileSize = fi.fsize;

    fr = f_lseek(&file, 0);
    if (fr) {
        printf("[ERROR] f_lseek(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    fr = f_read(&file, (void*)destAddr, fileSize, &br);
    if (fr) {
        printf("[ERROR] f_read(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    fr = f_close(&file);
    if (fr) {
        printf("[ERROR] f_close(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    Xil_DCacheFlush();
    return XST_SUCCESS;
}

int readAnswer(const char *fileName, int* destAddr) {
    FIL file;
    FRESULT fr;
    FILINFO fi;
    UINT br;
    u32 fileSize;

    fr = f_stat(fileName, &fi);
    if (fr) {
        printf("[ERROR] f_stat(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    fr = f_open(&file, fileName, FA_READ);
    if (fr) {
        printf("[ERROR] f_open(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    fileSize = fi.fsize;

    fr = f_lseek(&file, 0);
    if (fr) {
        printf("[ERROR] f_lseek(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    fr = f_read(&file, (void*)destAddr, fileSize, &br);
    if (fr) {
        printf("[ERROR] f_read(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    fr = f_close(&file);
    if (fr) {
        printf("[ERROR] f_close(readFile) FAILED %d\r\n", fr);
        return XST_FAILURE;
    }

    int sdStatus = sdEject();
    if (sdStatus != XST_SUCCESS) {
        printf("[ERROR] SD Card Eject FAILED \r\n");

        return XST_FAILURE;
    }
    printf("[INFO] SD Eject PASSED \r\n");

    Xil_DCacheFlush();
    return XST_SUCCESS;
}

int sdSetupFloat(float** destAddrFloat, int testNum) {
    
    std::string inputFloatStr = "fp_";
    std::string ext           = ".bin";

    std::string num;
    std::string strFloat;

    char* fileNameFloat;

    int sdStatus = sdInit();
    if (sdStatus != XST_SUCCESS) {
        printf("[ERROR] SD Card Init FAILED \r\n");

        return XST_FAILURE;
    }
    printf("[INFO] SD Init PASSED \r\n");

    
    for (int i = 0; i < testNum; i++) {
        num = std::to_string(i);
        strFloat = inputFloatStr + num + ext;
        
        fileNameFloat = const_cast<char*>(strFloat.c_str());

        sdStatus = readFileFloat(fileNameFloat, destAddrFloat[i]);
        if (sdStatus != XST_SUCCESS) {
            printf("[ERROR] SD Card Read FAILED \r\n");

            return XST_FAILURE;
        }

        if (i % 8 == 0)
            printf("[INFO] Read %4d binary file PASSED\r\n", i);

    }
    printf("[INFO] SD Card Read PASSED \r\n");

    return XST_SUCCESS;
}

int sdSetupFixed(u16** destAddrFixed, int testNum) {
    
    std::string inputFixedStr = "fx_";
    std::string ext           = ".bin";

    std::string num;
    std::string strFixed;

    char* fileNameFixed;

    int sdStatus = sdInit();
    if (sdStatus != XST_SUCCESS) {
        printf("[ERROR] SD Card Init FAILED \r\n");

        return XST_FAILURE;
    }
    printf("[INFO] SD Init PASSED \r\n");

    
    for (int i = 0; i < testNum; i++) {
        num = std::to_string(i);
        strFixed = inputFixedStr + num + ext;
        
        fileNameFixed = const_cast<char*>(strFixed.c_str());

        sdStatus = readFileFixed(fileNameFixed, destAddrFixed[i]);
        if (sdStatus != XST_SUCCESS) {
            printf("[ERROR] SD Card Read FAILED \r\n");

            return XST_FAILURE;
        }

        if (i % 8 == 0)
            printf("[INFO] Read %4d binary file PASSED\r\n", i);

    }

    printf("[INFO] SD Card Read PASSED \r\n");

    return XST_SUCCESS;
}