#pragma once

namespace mcuInit {

void init();

namespace systemClock {
void initTree();
void initChrono();
}

namespace io {
void init();
}

namespace comm {
void init();
}

}
