#include "serialization.h"

namespace serialize
{
	template<>
	void write(std::vector<std::byte>& data, std::string const& x)
	{
		for(auto c : x)
			data.push_back((std::byte)c);
		data.push_back(std::byte(0)); // null terminator
	}

	template<>
	void read(std::byte const*& data, std::string& x)
	{
		x = (char const*&)data;
		data += x.size() + 1;
	}
}