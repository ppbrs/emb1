#include "app-containers.h"
#include "common/memory/stack_allocator.h"
#include "common/memory/stack_arena.h"
#include <vector>

/*
template<class T, class Allocator = std::allocator<T>> class vector;
*/
using ValueType = uint32_t;
constexpr std::size_t bufSize = sizeof(ValueType) * 8; // bytes
template<class T, std::size_t BufSize = bufSize>
using StackVector = std::vector<T, StackAllocator<T, BufSize, alignof(T)>>;


void app_containers::start() {
	// Create the stack-based arena from which to allocate
	StackVector<ValueType>::allocator_type::arena_type a;
	// Create the vector which uses that arena.
	StackVector<ValueType> v{a};
	v.reserve(4);
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.insert(v.cbegin(), 4);
}