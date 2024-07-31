// This source file belongs to riga-comm-00 project.
#include "./app.h"
#include "./freertos/freertos.h"
#include "common/io/char-stream.h"
#include "if/mcu/tick.h"
#include <array>

namespace app {

enum class Mode : uint8_t {
	/* This is the default mode when the application reports the stats
	every second. */
	REPORT,
	ECHO,
};
namespace {
uint32_t ledRxCntLast = 0;
uint32_t ledSysTickCntLast = 0;
bool ledOn = 0;

uint32_t rxCnt = 0;
uint32_t txCnt = 0;
uint32_t echoRxCnt = 0;
uint32_t echoTxCnt = 0;
uint32_t echoRxErrCnt = 0;

std::array<char, 128> reportChStrBuf;
std::string_view reportSV;

Mode mode = Mode::REPORT;

constexpr size_t echoBufferSizeBytes = 128;
constexpr size_t echoBufferTriggerLevel = 1;
uint8_t echoBufferStorage[echoBufferSizeBytes + 1];
StaticStreamBuffer_t echoBuffer;
StreamBufferHandle_t echoBufferHandle;


void (*ptrNotifyDataReady)(void);
}
}

void app::init(void (*notifyDataReady)(void)) {
	ptrNotifyDataReady = notifyDataReady;
}

void app::initFromTask() {
	echoBufferHandle = xStreamBufferCreateStatic(
		echoBufferSizeBytes,
		echoBufferTriggerLevel,
		echoBufferStorage,
		&echoBuffer);
}

void app::consumeByteFromISR(uint8_t rxChar) {
	switch(mode) {
		case Mode::ECHO: {
			if(rxChar == 0x13) { // XOFF received
				mode = Mode::REPORT;
			} else {
				if(xStreamBufferSendFromISR(echoBufferHandle, &rxChar, 1, nullptr)) {
					echoRxCnt++;
				} else {
					echoRxErrCnt++;
				}
			}
			break;
		}
		case Mode::REPORT: {
			if(rxChar == 0x11) { // XON received
				mode = Mode::ECHO;
			}
			break;
		}
	}
	rxCnt++;
}

void app::pollFrom1HzTimer() {
	switch(mode) {
		case Mode::REPORT: {
			using namespace std::string_view_literals;
			io::CharStream reportChStr(reportChStrBuf.data(), reportChStrBuf.size());
			reportChStr
				<< "\r\n"sv
				<< "rxCnt="sv << rxCnt << ", "sv
				<< "txCnt="sv << txCnt << ", "sv
				<< "echoRxCnt="sv << echoRxCnt << ", "sv
				<< "echoTxCnt="sv << echoTxCnt << ", "sv
				<< "echoRxErrCnt="sv << echoRxErrCnt << ", "sv;
			reportSV = reportChStr.view();
			if(reportSV.size()) {
				ptrNotifyDataReady();
			}
			break;
		}
		default: {
			break;
		}
	};
}

void app::pollFromTask() {
	switch(mode) {
		default: {
			break;
		}
		case Mode::ECHO: {
			if(xStreamBufferBytesAvailable(echoBufferHandle)) {
				ptrNotifyDataReady();
			}
			break;
		}
	}
}

std::optional<uint8_t> app::getNextTxByte() {
	switch(mode) {
		default:
		case Mode::REPORT: {
			if(reportSV.size()) {
				char byte = reportSV.front();
				reportSV = reportSV.substr(1);
				txCnt++;
				return std::make_optional(byte);
			} else {
				return std::nullopt;
			}
		}
		case Mode::ECHO: {
			uint8_t byte;
			if(xStreamBufferReceiveFromISR(echoBufferHandle, &byte, 1, nullptr)) {
				echoTxCnt++;
				txCnt++;
				return std::make_optional(byte);
			} else {
				return std::nullopt;
			}
		}
	}
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
