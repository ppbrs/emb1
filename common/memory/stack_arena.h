#pragma once

#include "if/error.h"
#include <cstddef>
#include <cstdint>


template<std::size_t N, std::size_t alignment = alignof(std::max_align_t)>
class StackArena {
	alignas(alignment) char buf_[N];
	char *ptr_;

	public:
	~StackArena() {
		ptr_ = nullptr;
		// cout << "arena::~arena" << endl;
	}
	StackArena() noexcept :
			ptr_(buf_) {
	}
	StackArena(const StackArena &) = delete;
	StackArena &operator=(const StackArena &) = delete;

	template<std::size_t ReqAlign>
	char *allocate(std::size_t n) {
		static_assert(ReqAlign <= alignment, "alignment is too small for this arena");
		// assert(pointer_in_buffer(ptr_) && "short_alloc has outlived arena");
		const auto aligned_n = align_up(n);
		if(static_cast<decltype(aligned_n)>(buf_ + N - ptr_) >= aligned_n) {
			char *r = ptr_;
			ptr_ += aligned_n;
			return r;
		}
		error::fatal(false);
		// We'll never get here.
		return nullptr;
	}

	void deallocate(char *p, std::size_t n) noexcept {
		// assert(pointer_in_buffer(ptr_) && "short_alloc has outlived arena");
		if(pointer_in_buffer(p)) {
			n = align_up(n);
			if(p + n == ptr_)
				ptr_ = p;
		} else {
			error::fatal(false);
		}
	}

	static constexpr std::size_t size() noexcept {
		return N;
	}
	std::size_t used() const noexcept {
		return static_cast<std::size_t>(ptr_ - buf_);
	}
	void reset() noexcept {
		ptr_ = buf_;
	}

	private:
	static std::size_t align_up(std::size_t n) noexcept {
		return (n + (alignment - 1)) & ~(alignment - 1);
	}

	bool pointer_in_buffer(char *p) noexcept {
		return std::uintptr_t(buf_) <= std::uintptr_t(p) && std::uintptr_t(p) <= std::uintptr_t(buf_) + N;
	}
};
