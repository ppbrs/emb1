#pragma once

#include <cstdint>

namespace chrono {

/*
system_clock is RTC
steady_clock is 1us
high_resolution_clock is the fastest possible
*/

namespace system_clock {
}

namespace steady_clock {
void overflow();
void init();
}

namespace high_resolution_clock {
void overflow();
void init();
}
}
