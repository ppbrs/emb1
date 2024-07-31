#pragma once

namespace protocol {
int init();
}

inline int protocolInit() {
	return protocol::init();
}
