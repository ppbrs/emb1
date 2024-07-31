#include "3party/googletest/googletest/include/gtest/gtest.h"
#include <iostream>

int main(int argc, char **argv) {
	std::cout
		<< std::endl
		<< "Running main() from " << __FILE__ << std::endl
		<< __DATE__ << " " << __TIME__ << std::endl
		<< __VERSION__ << std::endl
		<< argv[0] << std::endl
		<< std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
