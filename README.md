# Generic Serialization
Lightweight generic serialization library.

Comes with binary serialization. To use it include [gs/Binary.h](include/gs/Binary.h).

## Usage example
See [example.cpp](test_package/example.cpp).

## Adding new stream types
Specialize `gs::is_input` and `gs::is_output` type traits for your input and output stream types.

Provide input & output `gs::serialize(Stream& stream, T& value)` function overloads that call read/write function specialized for the stream type.
For example see [Binary.h](include/gs/Binary.h).
