#pragma once

#include <vector>
#include <string>

namespace serialize
{
	template<typename T, typename byte_t>
	void write(std::vector<byte_t>& data, T const& x)
	{
		static_assert(sizeof(byte_t) == 1);
		auto const pointer = reinterpret_cast<byte_t const*>(&x);
		for(size_t i = 0; i < sizeof(x); ++i)
			data.push_back(pointer[i]);
	};

	// advances the data pointer
	template<typename T, typename byte_t>
	void read(byte_t const*& data, T& x)
	{
		static_assert(sizeof(byte_t) == 1);
		auto pointer = reinterpret_cast<byte_t*>(&x);
		for (size_t i = 0; i < sizeof(x); ++i) {
			pointer[i] = *data;
			++data;
		}
	}

	template<typename T, typename byte_t>
	T read(byte_t const*& data)
	{
		T x;
		read(data, x);
		return x;
	}


	template<>
	void write(std::vector<std::byte>& data, std::string const& x);

	template<>
	void read(std::byte const*& data, std::string& x);
}