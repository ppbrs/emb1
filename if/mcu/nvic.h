#pragma once

namespace nvic {

void defaultHandler();
void nmiHandler();
void hardFaultHandler();

void svcISR(); // SuperVisor Call
void pendsvISR(); // Pendable SerVice

}
