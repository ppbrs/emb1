#include "common/console/console.h"
#include "if/mcu/tick.h"

namespace console {
namespace {
uint32_t ledRxCntLast = 0;
uint32_t ledSysTickCntLast = 0;
bool ledOn = 0;

/* The maximum number of symbols in a command line that can fit in one buffer. */
constexpr unsigned bufLen = 128;
/* The index of the current buffer */
constinit uint8_t curBufIdx = 0;
/* The index of the next empty place in the current buffer. */
constinit unsigned curBufPtr = 0;

uint8_t buf[2][bufLen];


}
}

unsigned console::rxCnt = 0;

void console::init() {
}

/*
Called from the idle hook or a low priority thread.
*/
void console::processLeds(void (*ledAssertFunc)(bool)) {
	if(rxCnt != ledRxCntLast) {
		ledRxCntLast = rxCnt;
		ledSysTickCntLast = tick::sysTickCnt;
		if(not ledOn) {
			ledAssertFunc(true);
			ledOn = true;
		} else {
		}
	} else if(ledOn) {
		unsigned ledOnTime = tick::sysTickCnt - ledSysTickCntLast;
		if(ledOnTime > 200) {
			ledAssertFunc(false);
			ledOn = false;
		}
	}
}

void console::byteReceived(uint8_t b) {
	rxCnt++;
	buf[curBufIdx][curBufPtr++] = b;
}
