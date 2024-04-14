#pragma once

#include <gs/binary/FILE.h>
#include <gs/binary/fstream.h>
#include <gs/forward/serializer.h>

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
