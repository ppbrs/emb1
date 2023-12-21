
#include "if/mcu/memory.h"

/*
0x20000000 - 0x20020000 = DTCM-RAM = Data Tightly Coupled Memory, 128 Kbytes, 7 ECC bits per 32-bit word
0x24000000 - 0x2407FFFF = D1 AXI SRAM, 512 Kbytes, 8 ECC bits per 64-bit word
0x30000000 - 0x3001FFFF = D2 AHB SRAM1, 128 Kbytes, 7 ECC bits per 32-bit word
0x30020000 - 0x3003FFFF = D2 AHB SRAM2, 128 Kbytes, 7 ECC bits per 32-bit word
0x30040000 - 0x30047FFF = D2 AHB SRAM3, 32 Kbytes, 7 ECC bits per 32-bit word
0x38000000 - 0x3800FFFF = D3 AHB SRAM4, Low power SRAM, 64 Kbytes, 7 ECC bits per 32-bit word
0x38800000 - 0x38800FFF, D3 backup SRAM, BKPRAM, 4 Kbytes, 7 ECC bits per 32-bit word
*/
bool mcu::memory::isReadable(uint32_t startAddr, uint32_t endAddr) {
	return (
		// ITCM
		((startAddr >= 0x00000000) and (endAddr < 0x00010000))
		// User flash memory
		or ((startAddr >= 0x08000000) and (endAddr < 0x08200000))
		// System flash memory
		or ((startAddr >= 0x1FF00000) and (endAddr < 0x1FF1FFFF)));
}
