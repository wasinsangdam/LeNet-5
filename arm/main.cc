#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>

#include "xaxidma.h"
#include "xparameters.h"
#include "xstatus.h"
#include "xscugic.h"
#include "xtmrctr.h"

#include "xpredict.h"
#include "xpredict_hw.h"

#include "sdCard.h"
#include "reference.h"
#include "origin.h"

#define __HW
// #define __SW
// #define __ORG

XScuGic intr;
XScuGic_Config *intrCfg;

XTmrCtr timer;
XTmrCtr_Config *timerCfg;

XPredict predCore;
XPredict_Config *predConfig;

XScuGic scuGic;

XAxiDma dmaInst;
XAxiDma_Config *dmaCfg;

#ifdef __HW

u8* outputHw;
int doneCnt;

u32 totalStartTime;
u32 totalEndTime;

typedef struct {

    u32 hwStart;
    u32 hwEnd;
    u32 hwCycle;

    u32 dmaStart;
    u32 dmaEnd;
    u32 dmaCycle;

    u32 intrStart;
    u32 intrEnd;
    u32 intrCycle;

    u32 testStart;
    u32 testEnd;
    u32 testCycle;

} time;

time* timeTable;

int initDma();
int predictInit();
int predictStart();
void predictIsr();
int predictIntr();
int predictSetup(u16** inputAddr, int inputSize);
int runAccel(u16* inputAddr, int inputSizeOne);

#endif


#define NUM_TESTS   4

#ifndef IMAGE_SIZE
#define IMAGE_SIZE  1024
#endif

#define ANSWER_NUM  10000



int main (void) {

	printf("---------- LeNet-5 Start ----------\r\n");

    int status;
    int answer[ANSWER_NUM] = { 0, };

    /* Dynamic allocation of input and output array */

    #ifdef __HW
    
    u16** inputFixed;
    int inputFixedSize    = NUM_TESTS * sizeof(u16) * IMAGE_SIZE;
    int inputFixedSizeOne = sizeof(u16) * IMAGE_SIZE;

    inputFixed = new u16*[NUM_TESTS];

    for (int i = 0; i < NUM_TESTS; i++) {
        inputFixed[i] = new u16[IMAGE_SIZE];
    }

    outputHw  = new u8[NUM_TESTS];
    timeTable = new time[NUM_TESTS];



    #elif defined __SW
    float** inputFloat;
    inputFloat = new float*[NUM_TESTS];

    for (int i = 0; i < NUM_TESTS; i++) {
        inputFloat[i] = new float[IMAGE_SIZE];
    }

    u8* outputSw;

    outputSw  = new u8[NUM_TESTS];


    #elif defined __ORG
    float** inputFloat;
    inputFloat = new float*[NUM_TESTS];

    for (int i = 0; i < NUM_TESTS; i++) {
        inputFloat[i] = new float[IMAGE_SIZE];
    }

    u8* outputOrg;

    outputOrg = new u8[NUM_TESTS];

    #endif
    


    #ifdef __HW
    /* Read fixed data in SD card */
    status = sdSetupFixed(inputFixed, NUM_TESTS);
    if (status != XST_SUCCESS) {
        printf("[ERROR] SD Card setting FAILED! \r\n");
        return XST_FAILURE;
    }
    printf("[INFO] Input initialize PASSED \r\n");

    #elif defined __SW
    /* Read float data in SD card */
    status = sdSetupFloat(inputFloat, NUM_TESTS);
    if (status != XST_SUCCESS) {
        printf("[ERROR] SD Card setting FAILED! \r\n");
        return XST_FAILURE;
    }
    printf("[INFO] Input initialize PASSED \r\n");

    #elif defined __ORG
    /* Read float data in SD card */
    status = sdSetupFloat(inputFloat, NUM_TESTS);
    if (status != XST_SUCCESS) {
        printf("[ERROR] SD Card setting FAILED! \r\n");
        return XST_FAILURE;
    }
    printf("[INFO] Input initialize PASSED \r\n");

    #endif

    /* Read Answer in SD card */
    status = readAnswer((const char*)"answer.bin", answer);
    if (status != XST_SUCCESS) {
        printf("[ERROR] Read answer FAILED \r\n");
    }
    

    /* DMA Controller Setup */

    #ifdef __HW
    status = initDma();
    if (status != XST_SUCCESS) {
        printf("[ERROR] DMA initilize FAILED! \r\n");
        return XST_FAILURE;
    }
    printf("[INFO] DMA initialize PASSED \r\n");
    #endif


    /* Timer Setup */
    status = XTmrCtr_Initialize(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    if (status != XST_SUCCESS) {
        printf("[ERROR] AXI Timer initialze FAILED \r\n");
        return XST_FAILURE;
    }
    XTmrCtr_SetOptions(&timer, XPAR_AXI_TIMER_0_DEVICE_ID, XTC_ENABLE_ALL_OPTION);
    printf("[INFO] AXI Timer initialzed PASSED \r\n");

    #ifdef __HW
    /* Measure HW Timer setup time */
    XTmrCtr_Reset(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    timeTable[0].testStart = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    timeTable[0].testEnd   = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    timeTable[0].testCycle = timeTable[0].testEnd - timeTable[0].testStart;

    u32 setupCycle = timeTable[0].testCycle;

    #elif __SW
    /* Measure HW Timer setup time */
    XTmrCtr_Reset(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    u32 initTime = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    u32 currTime = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    u32 setupTime = currTime - initTime;
    printf("[INFO] Set up time for Timer is %lu cycles. \n\r", setupTime);
    
    #elif __ORG
    /* Measure HW Timer setup time */
    XTmrCtr_Reset(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    u32 initTime = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    u32 currTime = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    u32 setupTime = currTime - initTime;
    printf("[INFO] Set up time for Timer is %lu cycles. \n\r", setupTime);
    #endif

    /* Measure loop time */
    XTmrCtr_Reset(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    u32 loopStart = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    for (int i = 0; i < NUM_TESTS; i++) {}
    u32 loopEnd = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);

    u32 loopCycle = loopEnd - loopStart - setupCycle;


    /* LeNet-5 in HW Accelerator */

    #ifdef __HW
    status = predictSetup(inputFixed, inputFixedSize);
    if (status != XST_SUCCESS) {
        printf("[ERROR] Predict Core initialze FAILED \r\n");
        return XST_FAILURE;
    }
    printf("[INFO] Predict Core initialized PASSED\n\n\r");

    XTmrCtr_Reset(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    totalStartTime = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    for (int i = 0; i < NUM_TESTS; i++) {
        runAccel(inputFixed[i], inputFixedSizeOne);
    }

    while(!(doneCnt == NUM_TESTS)) {}

    
    #elif defined __SW
    /* LeNet-5 in ARM Core */

    XTmrCtr_Reset(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    u32 swStartTime = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    for (int i = 0; i < NUM_TESTS; i++) {
        predict_ref(inputFloat[i], &outputSw[i]);
    }
    u32 swEndTime = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);

    
    #elif defined __ORG
    /* LeNet-5 original in ARM Core */

    XTmrCtr_Reset(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    u32 orgSwStartTime = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    for (int i = 0; i < NUM_TESTS; i++) {
        org_predict(inputFloat[i], &outputOrg[i]);
    }
    u32 orgSwEndTime = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);

    #endif
    

    /* Performance Chcek */

    #ifdef __HW

    for (int i = 0; i < NUM_TESTS; i++) {

        if (i < 1) 
            timeTable[i].hwCycle = timeTable[i].hwEnd - timeTable[i].hwStart - setupCycle;
        else 
            timeTable[i].hwCycle = timeTable[i].hwEnd - timeTable[i-1].hwEnd - setupCycle;
        
        timeTable[i].dmaCycle  = timeTable[i].dmaEnd  - timeTable[i].dmaStart  - setupCycle;
        timeTable[i].intrCycle = timeTable[i].intrEnd - timeTable[i].intrStart - setupCycle;
    }

    u32 totalCycle = totalEndTime - totalStartTime - setupCycle - loopCycle;

    printf("---------------------------------------------------\r\n"); 
    printf("[INFO] Timer setup    run time : %10lu cycles. \n\r", setupCycle);
    printf("[INFO] Loop iteration run time : %10lu cycles. (%d) \n\n\r", loopCycle, NUM_TESTS);
    printf("---------------------------------------------------\r\n"); 
    printf("[INFO] Total [HW]     run time : %10lu cycles over %d tests. \r\n", totalCycle, NUM_TESTS);
    printf("[INFO] One sample     run time : %10lu cycles. \r\n\n", totalCycle/NUM_TESTS);
    printf("---------------------------------------------------\r\n"); 


    for (int i = 0; i < NUM_TESTS; i++) {     
        printf("---------------------------------------------------\r\n"); 
        printf("[INFO] %2d iter DMA Tx run time : %10lu cycles. \r\n", i, timeTable[i].dmaCycle);
        printf("[INFO] %2d iter HW Acc run time : %10lu cycles. \r\n", i, timeTable[i].hwCycle);
        printf("[INFO] %2d iter Intr   run time : %10lu cycles. \r\n", i, timeTable[i].intrCycle);
    }
    printf("---------------------------------------------------\r\n"); 

    printf("---------------------------------------------------\r\n"); 
    
    printf("[INFO] Start point           : %10lu\r\n", totalStartTime);
    for (int i = 0; i < NUM_TESTS; i++) {
        printf("[INFO] %2d DMA Tx Start point : %10lu\r\n", i, timeTable[i].dmaStart);
        printf("[INFO] %2d DMA Tx End   point : %10lu\r\n", i, timeTable[i].dmaEnd);

        printf("[INFO] %2d HW ACC Start point : %10lu\r\n", i, timeTable[i].hwStart);
        printf("[INFO] %2d HW ACC End   point : %10lu\r\n", i, timeTable[i].hwEnd);

        printf("[INFO] %2d Intr   Start point : %10lu\r\n", i, timeTable[i].intrStart);
        printf("[INFO] %2d Intr   End   point : %10lu\r\n", i, timeTable[i].intrEnd);

    }

    printf("[INFO] End point             : %10lu\r\n", totalEndTime);
    
    printf("---------------------------------------------------\r\n"); 

    

    
    #elif defined __SW
    u32 swCycle    = swEndTime    - swStartTime    - setupTime; //- loopTime;

    printf("[INFO] Total [SW]     run time : %lu cycles over %d tests. \r\n", swCycle, NUM_TESTS);
    printf("[INFO] One sample     run time : %lu cycles. \n\n\r", swCycle/NUM_TESTS);

    #elif defined __ORG
    u32 orgCycle   = orgSwEndTime - orgSwStartTime - setupTime - loopTime;

    printf("[INFO] Total [ORG]    run time : %lu cycles over %d tests. \r\n", orgCycle, NUM_TESTS);
    printf("[INFO] One sample     run time : %lu cycles. \n\n\r", orgCycle/NUM_TESTS);
    
    #endif
    

    /* Accuracy Chcek */

    #ifdef __HW
    int errHw = 0;

    for (int i = 0; i < NUM_TESTS; i++) {
        if (answer[i] != outputHw[i]) errHw++;
    }

    printf("\r\n[HW Result]\r\n");
    printf("Accuracy : %.2f [%%] \r\n", ((float)(NUM_TESTS - errHw) / (float)(NUM_TESTS)) * 100);
    printf("Error    : %5d  [cases] \r\n", errHw);

    #elif defined __SW
    int errSw = 0;

    for (int i = 0; i < NUM_TESTS; i++) {
        if (answer[i] != outputSw[i]) errSw++;
    }

    printf("[SW Result]\r\n");
    printf("Accuracy : %.2f [%%] \r\n", ((float)(NUM_TESTS - errSw) / (float)(NUM_TESTS)) * 100);
    printf("Error    : %5d  [cases] \r\n", errSw);

    #elif defined __ORG
    int errOrg = 0;

    for (int i = 0; i < NUM_TESTS; i++) {
        if (answer[i] != outputOrg[i]) errOrg++;
    }

    printf("[ORG Result]\r\n");
    printf("Accuracy : %.2f [%%] \r\n", ((float)(NUM_TESTS - errOrg) / (float)(NUM_TESTS)) * 100);
    printf("Error    : %5d  [cases] \r\n", errOrg);
    
    #endif
    
    

    /* Deallocation */

    #ifdef __HW
    for (int i = 0; i < NUM_TESTS; i++) {
        delete[] inputFixed[i];
    }
    
    delete[] inputFixed;
    delete[] outputHw;
    delete[] timeTable;

    #elif defined __SW
    for (int i = 0; i < NUM_TESTS; i++) {
        delete[] inputFloat[i];
    }
    delete[] inputFloat;
    delete[] outputSw;

    #elif defined __ORG
    for (int i = 0; i < NUM_TESTS; i++) {
        delete[] inputFloat[i];
    }
    delete[] inputFloat;
    delete[] outputOrg;

    #endif
    

    printf("----------- LeNet-5 End -----------\r\n");

    return XST_SUCCESS;

}

#ifdef __HW 

int initDma() {

    int dmaStatus;

    dmaCfg = XAxiDma_LookupConfig(XPAR_AXI_DMA_0_DEVICE_ID);
    if (!dmaCfg) {
        printf("[ERROR] No AXI DMA config\r\n");
        return XST_FAILURE;
    }

    dmaStatus = XAxiDma_CfgInitialize(&dmaInst, dmaCfg);
    if (dmaStatus != XST_SUCCESS) {
        printf("[ERROR] Initializing DMA\r\n");
        return XST_FAILURE;
    }

    if (XAxiDma_HasSg(&dmaInst)) {
        printf("[ERROR] Scatter Gather mode is not allowed.\r\n");
        return XST_FAILURE;
    }

    XAxiDma_IntrDisable(&dmaInst, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
    XAxiDma_IntrDisable(&dmaInst, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);

    // XAxiDma_Reset(&dmaInst);
    // while (!XAxiDma_ResetIsDone(&dmaInst)) {}

    return XST_SUCCESS;
}

int predictInit() {
    int predStatus = XPredict_Initialize(&predCore, XPAR_PREDICT_0_DEVICE_ID);
    if (predStatus != XST_SUCCESS) {
        printf("[ERROR] Initialize predict core FAILED\r\n");
        return XST_FAILURE;
    }

    return XST_SUCCESS;
}

int predictStart() {
    
    XPredict_InterruptEnable(&predCore, 0x1);

    XPredict_InterruptGlobalEnable(&predCore);

    XPredict_EnableAutoRestart(&predCore);

    XPredict_Start(&predCore);
    
    return XST_SUCCESS;
}

void predictIsr() {
    
    static int index = 0;

    timeTable[index].hwEnd     = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    timeTable[index].intrStart = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);

    if (XPredict_Get_output_r_vld(&predCore)) {
        outputHw[index] = (u8)XPredict_Get_output_r(&predCore);
        doneCnt++; 
    }

    if (doneCnt == NUM_TESTS) {
        totalEndTime = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    }
    
    XPredict_InterruptClear(&predCore, 0x1);
    timeTable[index].intrEnd = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);

    index++;
}


int predictIntr() {
    int intrStatus;

    XScuGic_Config* intrConfig = XScuGic_LookupConfig(XPAR_SCUGIC_0_DEVICE_ID);
    if (intrConfig == NULL) {
        printf("[ERROR] Lookup interrupt config FAILED\r\n");
        return XST_FAILURE;
    }

    intrStatus = XScuGic_CfgInitialize(&scuGic, intrConfig, intrConfig->CpuBaseAddress);
    if (intrStatus != XST_SUCCESS) {
        printf("[ERROR] Scugic config initilize FAILED\r\n");
        return XST_FAILURE;
    }

    intrStatus = XScuGic_SelfTest(&scuGic);
    if (intrStatus != XST_SUCCESS) {
        printf("[ERROR] Scugic self test FAILED\r\n");
        return XST_FAILURE;
    }

    Xil_ExceptionInit();

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, &scuGic);

    Xil_ExceptionEnable();

    intrStatus = XScuGic_Connect(&scuGic, XPAR_FABRIC_PREDICT_0_INTERRUPT_INTR, (Xil_InterruptHandler)predictIsr, &predCore);
    if (intrStatus != XST_SUCCESS) {
        printf("[ERROR] Scugic connect FAILED\r\n");
        return XST_FAILURE;
    }
    XScuGic_Enable(&scuGic, XPAR_FABRIC_PREDICT_0_INTERRUPT_INTR);

    return XST_SUCCESS;
}

int predictSetup(u16** inputAddr, int inputSize) {

    int status = predictInit();
    if (status != XST_SUCCESS) {
        printf("[ERROR] Initialize predict core FAILED\r\n");
        return XST_FAILURE;
    }

    status = predictIntr();
    if (status != XST_SUCCESS) {
        printf("[ERROR] Interrupt setup FAILED\r\n");
        return XST_FAILURE;
    }

    status = predictStart();
    if (status != XST_SUCCESS) {
        printf("[ERROR] Start predict core FAILED\r\n");
        return XST_FAILURE;
    }

    Xil_DCacheFlushRange((u32)inputAddr , inputSize);

    return XST_SUCCESS;
}



int runAccel(u16* inputAddr, int inputSizeOne) {

    static int index = 0;

    timeTable[index].dmaStart = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);

    int status = XAxiDma_SimpleTransfer(&dmaInst, (u32)inputAddr, inputSizeOne, XAXIDMA_DMA_TO_DEVICE);
    if (status != XST_SUCCESS) {
        printf("[ERROR] DMA Transfer to HLS predict core FAILED %d\r\n", status);
        return XST_FAILURE;
    }
    
    while (XAxiDma_Busy(&dmaInst, XAXIDMA_DMA_TO_DEVICE));

    timeTable[index].dmaEnd  = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
    timeTable[index].hwStart = XTmrCtr_GetValue(&timer, XPAR_AXI_TIMER_0_DEVICE_ID);

    index++;

    return XST_SUCCESS;
}

#endif