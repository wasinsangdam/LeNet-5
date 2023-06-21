#ifndef __SD_CARD_H__
#define __SD_CARD_H__

#include <stdio.h>
#include <string>
#include "ff.h"
#include "xstatus.h"
#include "xil_cache.h"

int sdInit();
int sdEject();
int readFileFixed(char *fileName, u16* destAddr);
int readFileFloat(char *fileName, float* destAddr);
int readAnswer(const char* fileName, int* destAddr);
int sdSetupFloat(float** destAddrFloat, int testNum);
int sdSetupFixed(u16** destAddrFixed, int testNum);

#endif