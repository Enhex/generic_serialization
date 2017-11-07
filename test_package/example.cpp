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
#define _CRT_SECURE_NO_WARNINGS

#include <gs/binary.h>
#include <cassert>
#include <iostream>

using namespace std;

void n() {
	cout << '\n';
}


// Example for serializing a POD type (without references/pointers since memory addresses change)
struct Vector3 {
	float x, y, z;

	void print() const {
		std::cout <<
			"x: " << x << '\n' <<
			"x: " << y << '\n' <<
			"y: " << z << '\n';
	}
};

template<typename S>
void serialize(S& serializer, Vector3& value) {
	gs::read_or_write_bytes(serializer.stream, value);
}


// example class
struct A
{
	int x = 0;
	float y = 0;
	char z[3];
	Vector3 vec3;

	void print() const {
		cout
			<< "x: " << x << '\n'
			<< "x: " << y << '\n'
			<< "z: " << z << '\n'
			<< "vec3:\n";
		vec3.print();

	}
};

namespace gs
{
	//TODO alternatively can be a member function so we don't have to pass A and we can access members directly. Requires using SFINAE to check if the method is available.
	template<typename Stream>
	void serialize(Serializer<Stream>& serializer, A& value) {
		// choose which members to serialize
		serializer(value.x, value.y, value.z, value.vec3);	// members' types' already have serialization implemented
	}														/*TODO
															can provide a wrapper around the Stream type that overloads operator() so we can write concisely:
															f(value.x, value.y);
															*/
}

namespace test
{
	void serialization()
	{
		A a;

		a.x = 5;
		a.y = 7.5;
		a.z[0] = 'a';
		a.z[1] = 'b';
		a.z[2] = '\0';
		a.vec3 = { 1,2,3 };

		cout << "writing:";
		n();
		cout << "========";
		n();
		a.print();
		n();

		// serialize to file
		{
			ofstream f("test", ofstream::binary);
			//auto& f = *static_cast<gs::oFile*>(fopen("test", "wb"));
			
			auto serializer = gs::make_serializer(f);
			serializer(a);

			//fclose(&f);
		}

		a.x = 0;
		a.y = 0;
		a.z[0] = '0';
		a.z[1] = '0';
		a.vec3 = { 0,0,0 };

		// read back from file
		{
			ifstream f("test", ios::binary);
			//auto& f = *static_cast<gs::iFile*>(fopen("test", "rb"));

			auto serializer = gs::make_serializer(f);
			serializer(a);

			//fclose(&f);
		}

		cout << "reading:";
		n();
		cout << "========";
		n();
		a.print();
		n();

		assert(a.x == 5);
		assert(a.y == 7.5);
		assert(a.z[0] == 'a');
		assert(a.z[1] == 'b');
		assert(a.z[2] == '\0');
		assert(a.vec3.x == 1);
		assert(a.vec3.y == 2);
		assert(a.vec3.z == 3);
	}
}


int main()
{
	cout <<
		"Serialization test\n"
		"==================\n";

	test::serialization();
}