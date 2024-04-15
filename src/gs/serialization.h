#pragma once

#include <vector>
#include <string>

namespace serialize
{
	template<typename T>
	void write(std::vector<std::byte>& data, T const& x)
	{
		auto pointer = reinterpret_cast<std::byte const*>(&x);
		for(size_t i = 0; i < sizeof(x); ++i)
			data.push_back(*pointer++);
	};

	// advances the data pointer
	template<typename T>
	void read(std::byte const*& data, T& x)
	{
		auto pointer = reinterpret_cast<std::byte*>(&x);
		for (size_t i = 0; i < sizeof(x); ++i) {
			pointer[i] = *data;
			++data;
		}
	}

	template<typename T>
	T read(std::byte const*& data)
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