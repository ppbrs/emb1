#pragma once

#include <cstdint>

namespace mcu {

namespace memory {

bool isReadable(uint32_t startAddr, uint32_t endAddr);

}
}