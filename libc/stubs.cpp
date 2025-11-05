
namespace {
void enterInfiniteLoop() {
	__asm__ volatile("bkpt #0\n");
	while(1) {
	};
}
}

namespace std {

// void __throw_bad_function_call() {
// 	// while(1);
// }

[[gnu::weak]] void __throw_out_of_range_fmt(const char *, ...) {
	enterInfiniteLoop();
}
}

/*
Without [[gnu::weak]], linker reports:
multiple definition of `abort'

Without this definition, linker reports:
undefined reference to `abort'
*/
extern "C" [[gnu::weak, gnu::noreturn]] void abort(void) {
	enterInfiniteLoop();
	__builtin_unreachable();
}
