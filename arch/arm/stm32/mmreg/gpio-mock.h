#pragma once

namespace mocks {

/*
Mock that pretends to be a real GPIO module.
*/
template<typename GPIO>
class GpioMock {
public:
	GpioMock(GPIO &gpio) : gpio(gpio) {};
	void update();
	void reset();
private:
	GPIO &gpio;

};

}
