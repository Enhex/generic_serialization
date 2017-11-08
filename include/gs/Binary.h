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
#ifndef Generic_Serialization_h
#define Generic_Serialization_h

#include <gs/binary/FILE.h>
#include <gs/binary/fstream.h>
#include <gs/Serializer.h>

namespace gs
{
	// binary trait
	template<typename T>
	struct is_binary : std::false_type {};

	template<typename T>
	constexpr bool is_binary_v = is_binary<std::remove_reference_t<T>>::value;

	template<> struct is_binary<std::ifstream> : std::true_type {};
	template<> struct is_binary<std::ofstream> : std::true_type {};
	template<> struct is_binary<oFile> : std::true_type {};
	template<> struct is_binary<iFile> : std::true_type {};


	// binary read type
	template<typename T>
	void read_bytes(std::ifstream& f, T& value) {
		f.read((char*)(&value), sizeof(value));
	}

	template<typename T>
	void read_bytes(iFile& f, T& value) {
		fread(&value, sizeof(value), 1, &f);
	}


	// binary write type
	template<typename T>
	void write_bytes(std::ofstream& f, T& value) {
		f.write((char*)(&value), sizeof(value));
	}

	template<typename T>
	void write_bytes(oFile& f, T& value) {
		fwrite(&value, sizeof(value), 1, &f);
	}


	// Read or write. Useful for defining a single serialize() specialization for both read and write.
	template<typename Stream, typename T>
	typename std::enable_if_t<
		is_binary_v<Stream> &&
		is_input_v<Stream>
	>
	read_or_write_bytes(Stream& f, T& value) {
		read_bytes(f, value);
	}
	template<typename Stream, typename T>
	typename std::enable_if_t<
		is_binary_v<Stream> &&
		is_output_v<Stream>
	>
	read_or_write_bytes(Stream& f, T& value) {
		write_bytes(f, value);
	}

	//automatically provide default binary serialization implementation for arithmetic & array of arithmetic types
	template<typename Stream, typename T>
	typename std::enable_if_t<
		is_binary_v<Stream> &&
		std::is_arithmetic_v<T>
		>
	serialize(Stream& stream, T& value) {
		read_or_write_bytes(stream, value);
	}

	template<typename Stream, typename T>
	typename std::enable_if_t<
		is_binary_v<Stream> &&
		std::is_array_v<T> &&
		std::is_arithmetic_v<std::decay_t<decltype(std::declval<T&>()[0])>>	// array's element type is arithmetic
		>
	serialize(Stream& stream, T& value) {
		read_or_write_bytes(stream, value);
	}
}

#endif//guard