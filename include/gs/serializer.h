/*
The MIT License (MIT)
Copyright (c) 2017 Yehonatan Ballas
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef gs_serializer_h
#define gs_serializer_h

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

#endif//guard