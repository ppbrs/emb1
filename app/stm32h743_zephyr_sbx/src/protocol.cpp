
#include "./protocol.h"
#include "common/memory/stack_allocator.h"
#include "common/memory/stack_arena.h"
#include "common/protocol/process.h"
#include "common/protocol/protocol.h"

#include <zephyr/console/console.h>

#include <cstring>
#include <vector>
#include <string_view>


// thread1 parameters
constexpr size_t protocolThreadStackSize = 1024;
K_THREAD_STACK_DEFINE(/*sym*/ protocolThreadStackArea, /*size*/ protocolThreadStackSize);
struct k_thread protocolThreadData;
constexpr int protocolThreadPriority = 7; // Numerically lower priorities takes precedence over numerically higher values.
void protocolThreadFunc(void *, void *, void *);


int protocolInit(){
	/* Initialize pull-style access to console. */
	console_getline_init();

	k_tid_t tid1 = k_thread_create(
		&protocolThreadData,
		protocolThreadStackArea, // stack
		K_THREAD_STACK_SIZEOF(protocolThreadStackArea), // stack_size in bytes
		protocolThreadFunc, // entry
		NULL, NULL, NULL,
		protocolThreadPriority, // prio
		0, // options
		K_NO_WAIT); // delay, K_NO_WAIT


	printk("I: protocolInit:\n");

	return 0;
}

template<class T, std::size_t BufSize = sizeof(std::string_view) * protocol::MAX_WORDS_NUM>
using StackVector = std::vector<T, StackAllocator<T, BufSize, alignof(T)>>;

void protocolThreadFunc(void *, void *, void *) {
	while (1) {
		// There is echo after every symbol.
		// The input string gets truncated to (CONFIG_CONSOLE_INPUT_MAX_LINE_LEN - 1) characters,
		// other characters are ignored.
		// Under the hood, `console_getline` uses two buffers. Once the first buffer is returned,
		// the second is being filled and will be returned on the next call to `console_getline`.
		char *s = console_getline();
		// printk("D: line: %s @%p, len=%u\n", s, s, strnlen(s, CONFIG_CONSOLE_INPUT_MAX_LINE_LEN - 1));
		printk("D: line: %s @%p, len=%u\n", s, s, strlen(s));

		const std::string_view sv {s};

		StackVector<std::string_view>::allocator_type::arena_type a;
		StackVector<std::string_view> v{a};
		v.reserve(protocol::MAX_WORDS_NUM);
		protocol::process::split(sv, v);
		printk("D: split: len=%u:", v.size());
		for(std::size_t i = 0; i < v.size(); i++) {
			printk(" (%.*s)", static_cast<int>(v[i].length()), v[i].data());
		}
		printk("\n");
	}
}

