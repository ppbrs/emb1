#pragma once

namespace nvic {


using ExceptionHandlerType = void (*)();

void defaultHandler();
void nmiHandler();
void hardFaultHandler();
void memManageHandler();
void busFaultHandler();
void usageFaultHandler();
void debugMonHandler();

void svcISR(); // SuperVisor Call
void pendsvISR(); // Pendable SerVice
void sysTickISR();

}
