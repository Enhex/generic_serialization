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
#ifndef gs_Serializer_h
#define gs_Serializer_h

namespace gs
{
	template<typename Stream>
	struct Serializer
	{
		Serializer(Stream& stream) : stream(stream) {}

		Stream& stream;

		template<typename ...Ts> inline
		auto& operator()(Ts&&... args)
		{
			serialize_(std::forward<Ts>(args)...);
			return *this;
		}

		// call free function with stream argument
		template<typename T> inline
		void serialize_stream(T&& value)
		{
			serialize(*this, std::forward<T>(value));
		}

		// serialize variadic template
		template<typename T> inline
		void serialize_(T&& value)
		{
			serialize_stream(std::forward<T>(value));
		}

		template<typename T, typename ...Ts> inline
		void serialize_(T&& value, Ts&&... args)
		{
			serialize_(std::forward<T>(value));
			serialize_(std::forward<Ts>(args)...);
		}
	};

	//NOTE: class template argument deduction not supported yet
	template<typename Stream> inline
	auto make_serializer(Stream&& stream) {
		return Serializer<Stream>(std::forward<Stream>(stream));
	};
}

#endif//guard