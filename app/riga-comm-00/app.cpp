// This source file belongs to riga-comm-00 project.
#include "./app.h"
#include "if/mcu/tick.h"


namespace app {
namespace {
uint32_t ledRxCntLast = 0;
uint32_t ledSysTickCntLast = 0;
bool ledOn = 0;

constexpr uint8_t txBuf[8] = {'q','w','e','r','t','y',' ', ' ',};
uint8_t txBufPtr;

void (*ptrNotifyDataReady)(void);
}

unsigned rxCnt = 0;

}

void app::init(void (&notifyDataReady)(void)) {
	ptrNotifyDataReady = notifyDataReady;
}

void app::consumeByteFromISR(uint8_t) {
	rxCnt++;
	// buf[curBufIdx][curBufPtr++] = b;
}

/*
Called from the idle hook or a low priority thread.
*/
void app::processLeds(void (*ledAssertFunc)(bool)) {
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

void app::pollFrom1HzTimer() {
	txBufPtr = 0;
	ptrNotifyDataReady();

}

std::optional<uint8_t> app::getNextTxByte() {
	return (txBufPtr < sizeof(txBuf)) ? std::make_optional(txBuf[txBufPtr++]) : std::nullopt;
}

