#include "3party/googletest/googletest/include/gtest/gtest.h"
#include "common/memory/stack_allocator.h"
#include "common/memory/stack_arena.h"
#include <vector>

class StackAllocatorTests : public ::testing::Test {
};

TEST_F(StackAllocatorTests, Basic) {
	{
		constexpr std::size_t vecSize = 8; // elements
		constexpr std::size_t bufSize = sizeof(uint32_t) * vecSize; // bytes
		std::vector<uint32_t, StackAllocator<uint32_t, bufSize>>::allocator_type::arena_type stackArena;
		std::vector<uint32_t, StackAllocator<uint32_t, bufSize>> vec{stackArena};

		ASSERT_GT(sizeof(stackArena), bufSize);

		vec.reserve(vecSize);
		vec.push_back(1);
		vec.push_back(1);
		vec.push_back(1);
		vec.push_back(1);
		vec.push_back(1);
		vec.push_back(1);
		vec.push_back(1);
		vec.push_back(1);
		// vec.push_back(1);
	}
}