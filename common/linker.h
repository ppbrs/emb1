#pragma once

#define SECTION_DATA_FAST __attribute__((section(".data.fast"))) /*[[gnu::section(".data.fast")]]*/
#define SECTION_DATA_REGULAR1 __attribute__((section(".data.regular1")))
#define SECTION_DATA_REGULAR SECTION_DATA_REGULAR1
#define SECTION_DATA_REGULAR2 __attribute__((section(".data.regular2")))
#define SECTION_DATA_REGULAR3 __attribute__((section(".data.regular3")))

#define SECTION_BSS_FAST __attribute__((section(".bss.fast")))
#define SECTION_BSS_REGULAR1 __attribute__((section(".bss.regular1")))
#define SECTION_BSS_REGULAR SECTION_BSS_REGULAR1
#define SECTION_BSS_REGULAR2 __attribute__((section(".bss.regular2")))
#define SECTION_BSS_REGULAR3 __attribute__((section(".bss.regular3")))
