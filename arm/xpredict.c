// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xpredict.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XPredict_CfgInitialize(XPredict *InstancePtr, XPredict_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_bus_BaseAddress = ConfigPtr->Control_bus_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XPredict_Start(XPredict *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPredict_ReadReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_AP_CTRL) & 0x80;
    XPredict_WriteReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_AP_CTRL, Data | 0x01);
}

u32 XPredict_IsDone(XPredict *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPredict_ReadReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XPredict_IsIdle(XPredict *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPredict_ReadReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XPredict_IsReady(XPredict *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPredict_ReadReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XPredict_Continue(XPredict *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPredict_ReadReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_AP_CTRL) & 0x80;
    XPredict_WriteReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_AP_CTRL, Data | 0x10);
}

void XPredict_EnableAutoRestart(XPredict *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPredict_WriteReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_AP_CTRL, 0x80);
}

void XPredict_DisableAutoRestart(XPredict *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPredict_WriteReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_AP_CTRL, 0);
}

u32 XPredict_Get_output_r(XPredict *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPredict_ReadReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_OUTPUT_R_DATA);
    return Data;
}

u32 XPredict_Get_output_r_vld(XPredict *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPredict_ReadReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_OUTPUT_R_CTRL);
    return Data & 0x1;
}

void XPredict_InterruptGlobalEnable(XPredict *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPredict_WriteReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_GIE, 1);
}

void XPredict_InterruptGlobalDisable(XPredict *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPredict_WriteReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_GIE, 0);
}

void XPredict_InterruptEnable(XPredict *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XPredict_ReadReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_IER);
    XPredict_WriteReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_IER, Register | Mask);
}

void XPredict_InterruptDisable(XPredict *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XPredict_ReadReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_IER);
    XPredict_WriteReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_IER, Register & (~Mask));
}

void XPredict_InterruptClear(XPredict *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPredict_WriteReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_ISR, Mask);
}

u32 XPredict_InterruptGetEnabled(XPredict *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XPredict_ReadReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_IER);
}

u32 XPredict_InterruptGetStatus(XPredict *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XPredict_ReadReg(InstancePtr->Control_bus_BaseAddress, XPREDICT_CONTROL_BUS_ADDR_ISR);
}

