#include "./mmreg.h"
#include "3party/googletest/googletest/include/gtest/gtest.h"

class MmregTests : public ::testing::Test {
};

TEST_F(MmregTests, TestSetClearGetFunctions) {
	using mmreg::setBits, mmreg::clearBits, mmreg::testBitsMasked, mmreg::getBits, mmreg::setBitsMasked;
	uint32_t reg, msk, bts;

	reg = 0b1000'0001u;
	setBits(reg, 1, 3);
	ASSERT_EQ(reg, 0b1000'1001u);

	reg = 0b1111'1111u;
	clearBits(reg, 1, 7);
	ASSERT_EQ(reg, 0b0111'1111u);

	reg = 0b1111'1111u;
	msk = 0b1100'0011u;
	bts = 0b0100'0010u;
	setBitsMasked(reg, msk, bts);
	ASSERT_EQ(reg, 0b0111'1110u);

	reg = 0b0011'1111u;
	msk = 0b0110'0000u;
	ASSERT_EQ(getBits(reg, msk, 0), 0b0010'0000u);
	ASSERT_TRUE(testBitsMasked(reg, 0b0110'0000u, 0b0010'0000u, 0));
}
