
#include "mcu-init.h"
#include "chrono.h"

namespace mcuInit {
}

void mcuInit::init() {
	systemClock::initTree();
	systemClock::initChrono();
	io::init();
	comm::init();
}
