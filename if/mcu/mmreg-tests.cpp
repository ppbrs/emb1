#include "gtest/gtest.h"

#include "./mmreg.h"

class RegistersTests : public ::testing::Test {
};

TEST_F(RegistersTests, TestSetFunctions) {
	using mmreg::setBits, mmreg::clearBits, mmreg::testBitsMasked, mmreg::getBits, mmreg::setBitsMasked;
	uint32_t reg, msk, bts;

	reg = 0;
	setBits(reg, 1, 3);
	ASSERT_EQ(reg, 0b1000u);

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

