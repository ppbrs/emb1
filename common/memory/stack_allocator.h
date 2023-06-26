#pragma once

#include "./stack_arena.h"
#include "if/error.h"


template<class T, std::size_t N, std::size_t Align = alignof(std::max_align_t)>
class StackAllocator {
	public:
	using value_type = T;
	static auto constexpr alignment = Align;
	static auto constexpr size = N;
	using arena_type = StackArena<size, alignment>;

	private:
	arena_type &a_;

	public:
	StackAllocator(const StackAllocator &) = default; // copy constructor
	StackAllocator &operator=(const StackAllocator &) = delete; // assignment operator

	StackAllocator(arena_type &a) noexcept :
			a_(a) {
		static_assert(size % alignment == 0, "size N needs to be a multiple of alignment Align");
	}
	template<class U>
	StackAllocator(const StackAllocator<U, N, alignment> &a) noexcept
			:
			a_(a.a_) {
	}

	/*
	Rebind is for allocating memory for a type that differs from the element type
	of the container being implemented.
	*/
	template<class OtherT>
	struct rebind {
		using other = StackAllocator<OtherT, N, alignment>;
	};

	T *allocate(std::size_t n) {
		auto res = a_.template allocate<alignof(T)>(n * sizeof(T));
		return reinterpret_cast<T *>(res);
	}

	void deallocate(T *p, std::size_t n) noexcept {
		a_.deallocate(reinterpret_cast<char *>(p), n * sizeof(T));
	}
};
