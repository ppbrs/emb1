#include "./protocol.h"
#include "common/protocol/parser.h"
#include "common/protocol/prog.h"
#include "common/protocol/splitter.h"
#include "if/mcu/memory.h"
#include <cstring>
#include <optional>
#include <string_view>
#include <variant>
#include <vector>
#include <zephyr/console/console.h>
#include <zephyr/random/rand32.h>
// #include <functional>

namespace protocol {
namespace {

// protocol thread parameters
constexpr size_t threadStackSize = 2048;
K_THREAD_STACK_DEFINE(/*sym*/ threadStackArea, /*size*/ threadStackSize);
struct k_thread threadData;
constexpr int threadPriority = 7; // Numerically lower priorities takes precedence over numerically higher values.

using ProgVar = std::variant<
	ProgUnknown,
	ProgMemory,
	ProgRandom>;
using OptProgVar = std::optional<ProgVar>;

void threadFunc(void *, void *, void *) {
	while(1) {
		// There is echo after every symbol.
		// The input string gets truncated to (CONFIG_CONSOLE_INPUT_MAX_LINE_LEN - 1) characters,
		// other characters are ignored.
		// Under the hood, `console_getline` uses two buffers. Once the first buffer is returned,
		// the second is being filled and will be returned on the next call to `console_getline`.
		char *cmdChars = console_getline();

		// printk("D: line: %s @%p, len=%u\n", s, s, strnlen(s, CONFIG_CONSOLE_INPUT_MAX_LINE_LEN - 1));
		// printk("D: line: %s @%p, len=%u\n", cmdChars, cmdChars, strlen(cmdChars));

		const std::string_view cmd{cmdChars};

		OptProgVar optProgVar = std::nullopt;
		ParseResult parseResult = parseCmd(cmd, optProgVar);
		switch(parseResult) {
			case ParseResult::SUCCESS: {
				if(optProgVar.value().index() == get_variant_type_index<ProgMemory, ProgVar>::value) {
					ProgMemory prog = std::get<ProgMemory>(optProgVar.value());
					prog.execute();
				} else if(optProgVar.value().index() == get_variant_type_index<ProgRandom, ProgVar>::value) {
					ProgRandom prog = std::get<ProgRandom>(optProgVar.value());
					prog.execute();
				} else {
					// TODO: Fatal error.
				}
				break;
			}
			case ParseResult::EMPTY_COMMAND: {
				break;
			}
			case ParseResult::UNKNOWN_COMMAND: {
				printk("protocol: ERROR: Unknown command.\n");
				break;
			}
			case ParseResult::OPTION_MISSING: {
				printk("protocol: ERROR: Missing option.\n");
				break;
			}
			case ParseResult::OPTION_PARAMETER_MISSING: {
				printk("protocol: ERROR: Missing option parameter.\n");
				break;
			}
			case ParseResult::OPTION_PARAMETER_ERROR: {
				printk("protocol: ERROR: Option parameter parse error.\n");
				break;
			}
			case ParseResult::UNKNOWN_OPTION: {
				printk("protocol: ERROR: Unknown option.\n");
				break;
			}
			case ParseResult::HELP_REQUEST: {
				if(optProgVar.value().index() == get_variant_type_index<ProgMemory, ProgVar>::value) {
					printk("%.*s", ProgMemory::helpString.size(), ProgMemory::helpString.data());
				} else if(optProgVar.value().index() == get_variant_type_index<ProgRandom, ProgVar>::value) {
					printk("%.*s", ProgRandom::helpString.size(), ProgRandom::helpString.data());
				} else {
					// TODO: Fatal error.
				}
				break;
			}
			default: {
				printk("protocol: ERROR: Unknown error.\n");
				break;
			}
		}
	}
}
}
}

int protocol::init() {
	/* Initialize pull-style access to console. */
	console_getline_init();

	k_tid_t tid1 = k_thread_create(
		&threadData,
		threadStackArea, // stack
		K_THREAD_STACK_SIZEOF(threadStackArea), // stack_size in bytes
		threadFunc, // entry
		NULL, NULL, NULL,
		threadPriority, // prio
		0, // options
		K_NO_WAIT); // delay, K_NO_WAIT
	(void)tid1;

	printk("I: protocol::init:\n");

	return 0;
}

/*
memory --address 0x08000000 -t u32 -s 16
*/

void protocol::ProgMemory::execute() {
	printk("memory:");
	uint32_t startAddr = options[ADDRESS].paramUint32;
	uint32_t size = options[SIZE].paramUint32;
	if((size == 0) or (size > 8)) {
		printk(" ERROR: Wrong size. %u\n", size);
		return;
	}

	// TODO: assert(options[FORMAT].optParamStr.has_value())
	std::string_view format = options[FORMAT].optParamStr.value();
	bool isAlignmentOk = true; // Which always is for u8.
	uint32_t endAddr = startAddr + size; // for u8, i8, u8h
	if((format == "u32") or (format == "u32h") or (format == "i32")) {
		isAlignmentOk = (startAddr & 3) == 0;
		endAddr = startAddr + 4 * size;
	} else if((format == "u16") or (format == "u16h") or (format == "i16")) {
		isAlignmentOk = (startAddr & 1) == 0;
		endAddr = startAddr + 2 * size;
	} else if((format == "u8") or (format == "u8h") or (format == "i8")) {
		// do nothing
	} else {
		printk(" ERROR: Unknown format.\n");
		return;
	}
	if(not isAlignmentOk) {
		printk(" ERROR: Bad alignment.\n");
		return;
	}

	bool isReadable = mcu::memory::isReadable(startAddr, endAddr);
	if(not isReadable) {
		printk(" ERROR: Memory not readable.\n");
		return;
	}

	printk(" @%08x:", startAddr);
	if(format == "u32") {
		uint32_t *pData = (uint32_t *)startAddr;
		for(uint32_t i = 0; i < size; i++) {
			printk(" %u", *pData++);
		}
	} else if(format == "u32h") {
		uint32_t *pData = (uint32_t *)startAddr;
		for(uint32_t i = 0; i < size; i++) {
			printk(" 0x%08x", *pData++);
		}
	} else if(format == "i32") {
		int32_t *pData = (int32_t *)startAddr;
		for(uint32_t i = 0; i < size; i++) {
			printk(" %i", *pData++);
		}
	} else if(format == "u16") {
		uint16_t *pData = (uint16_t *)startAddr;
		for(uint16_t i = 0; i < size; i++) {
			printk(" %u", *pData++);
		}
	} else if(format == "u16h") {
		uint16_t *pData = (uint16_t *)startAddr;
		for(uint16_t i = 0; i < size; i++) {
			printk(" 0x%04x", *pData++);
		}
	} else if(format == "i16") {
		int16_t *pData = (int16_t *)startAddr;
		for(uint16_t i = 0; i < size; i++) {
			printk(" %d", *pData++);
		}
	} else if(format == "u8") {
		uint8_t *pData = (uint8_t *)startAddr;
		for(uint8_t i = 0; i < size; i++) {
			printk(" %u", *pData++);
		}
	} else if(format == "u8h") {
		uint8_t *pData = (uint8_t *)startAddr;
		for(uint8_t i = 0; i < size; i++) {
			printk(" 0x%02x", *pData++);
		}
	} else if(format == "i8") {
		int8_t *pData = (int8_t *)startAddr;
		for(uint8_t i = 0; i < size; i++) {
			printk(" %d", *pData++);
		}
	} else {
		// logic error
	}
	printk("\n");
};

void protocol::ProgRandom::execute() {
	printk("random:");

	uint32_t size = options[SIZE].paramUint32;
	if((size == 0) or (size > 8)) {
		printk(" ERROR: Wrong size. %u\n", size);
		return;
	}

	// TODO: assert(options[FORMAT].optParamStr.has_value())
	std::string_view format = options[FORMAT].optParamStr.value();
	uint32_t buffer[8]; // TODO: Use max size.
	bool success = true;
	bool crypto = static_cast<bool>(options[CRYPTO].paramUint32);
	if(crypto) {
		success = sys_csrand_get(buffer, sizeof(buffer)) == 0;
	} else {
		sys_rand_get(buffer, sizeof(buffer)); // TODO: Use size dependent on type.
	}
	if(not success) {
		printk(" ERROR: Entropy reseed error.\n");
		return;
	}

	if(format == "u32") {
		for(size_t i = 0; i < size; i++) {
			printk(" %u", buffer[i]);
		}
	} else if(format == "u32h") {
		for(size_t i = 0; i < size; i++) {
			printk(" 0x%08x", buffer[i]);
		}
	} else if(format == "i32") {
		for(size_t i = 0; i < size; i++) {
			printk(" %i", (int32_t)buffer[i]);
		}
	} else if(format == "u16") {
		uint16_t *pData = (uint16_t *)buffer;
		for(uint16_t i = 0; i < size; i++) {
			printk(" %u", *pData++);
		}
	} else if(format == "u16h") {
		uint16_t *pData = (uint16_t *)buffer;
		for(uint16_t i = 0; i < size; i++) {
			printk(" 0x%04x", *pData++);
		}
	} else if(format == "i16") {
		int16_t *pData = (int16_t *)buffer;
		for(uint16_t i = 0; i < size; i++) {
			printk(" %d", *pData++);
		}
	} else if(format == "u8") {
		uint8_t *pData = (uint8_t *)buffer;
		for(uint8_t i = 0; i < size; i++) {
			printk(" %u", *pData++);
		}
	} else if(format == "u8h") {
		uint8_t *pData = (uint8_t *)buffer;
		for(uint8_t i = 0; i < size; i++) {
			printk(" 0x%02x", *pData++);
		}
	} else if(format == "i8") {
		int8_t *pData = (int8_t *)buffer;
		for(uint8_t i = 0; i < size; i++) {
			printk(" %d", *pData++);
		}
	} else {
		printk(" ERROR: Unknown format.\n");
		return;
	}

	printk("\n");
}
