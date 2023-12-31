// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XPREDICT_H
#define XPREDICT_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xpredict_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_bus_BaseAddress;
} XPredict_Config;
#endif

typedef struct {
    u32 Control_bus_BaseAddress;
    u32 IsReady;
} XPredict;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XPredict_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XPredict_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XPredict_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XPredict_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XPredict_Initialize(XPredict *InstancePtr, u16 DeviceId);
XPredict_Config* XPredict_LookupConfig(u16 DeviceId);
int XPredict_CfgInitialize(XPredict *InstancePtr, XPredict_Config *ConfigPtr);
#else
int XPredict_Initialize(XPredict *InstancePtr, const char* InstanceName);
int XPredict_Release(XPredict *InstancePtr);
#endif

void XPredict_Start(XPredict *InstancePtr);
u32 XPredict_IsDone(XPredict *InstancePtr);
u32 XPredict_IsIdle(XPredict *InstancePtr);
u32 XPredict_IsReady(XPredict *InstancePtr);
void XPredict_Continue(XPredict *InstancePtr);
void XPredict_EnableAutoRestart(XPredict *InstancePtr);
void XPredict_DisableAutoRestart(XPredict *InstancePtr);

u32 XPredict_Get_output_r(XPredict *InstancePtr);
u32 XPredict_Get_output_r_vld(XPredict *InstancePtr);

void XPredict_InterruptGlobalEnable(XPredict *InstancePtr);
void XPredict_InterruptGlobalDisable(XPredict *InstancePtr);
void XPredict_InterruptEnable(XPredict *InstancePtr, u32 Mask);
void XPredict_InterruptDisable(XPredict *InstancePtr, u32 Mask);
void XPredict_InterruptClear(XPredict *InstancePtr, u32 Mask);
u32 XPredict_InterruptGetEnabled(XPredict *InstancePtr);
u32 XPredict_InterruptGetStatus(XPredict *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
