#include "test.h"
#include <cstdint>

int main() {
	Test::suiteStarted = true;
	TestIMult testIMult{};
	Test::startCount++;
	{
		testIMult.setUp();
		testIMult.run();
		testIMult.tearDown();
	}
	Test::finishCount++;
	Test::suiteFinished = true;

	while(true) {
		asm("nop");
	}
}
