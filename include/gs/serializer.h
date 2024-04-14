#pragma once

namespace gs
{
	// takes a parameter pack of objects and serializes them into a stream
	template<typename Stream>
	struct serializer_t
	{
		Stream& stream;

		template<typename ...Ts>
		constexpr serializer_t(Stream& stream, Ts&&... args) : stream(stream)
		{
			serialize_(std::forward<Ts>(args)...);
		}


		// call free function with stream argument
		template<typename T>
		constexpr void serialize_stream(const T& value)
		{
			serialize(stream, const_cast<T&>(value));	// prevent "Conversion loses qualifiers"
		}

		// serialize variadic template
		template<typename T>
		constexpr void serialize_(T&& value)
		{
			serialize_stream(std::forward<T>(value));
		}

		template<typename T, typename ...Ts>
		constexpr void serialize_(T&& value, Ts&&... args)
		{
			serialize_(std::forward<T>(value));
			serialize_(std::forward<Ts>(args)...);
		}
	};

	//NOTE: class template argument deduction not supported yet
	template<typename Stream, typename ...Ts>
	constexpr auto serializer(Stream&& stream, Ts&&... args) {
		return serializer_t<Stream>(std::forward<Stream>(stream), std::forward<Ts>(args)...);
	};
}
