// nonstatic_members_init.cpp
// Feb 2015, bfilipek.com

#include <iostream>

class SimpleType
{
private:
	int a { 1 };    // << wow!
	int b { 1 };    // << wow2!
	std::string name { "string" }; // wow3!

public:
	SimpleType() {
		std::cout << "SimpleType::ctor, {" << a << ", " << b << ", \"" << name << "\"}" << std::endl;
	}
	SimpleType(int aa, int bb) : a(aa), b(bb) {
		std::cout << "SimpleType::ctor(aa, bb), {" << a << ", " << b << ", \"" << name << "\"}" << std::endl;
	}
	~SimpleType() { std::cout << "SimpleType::destructor" << std::endl; }
};

class AdvancedType
{
private:
	SimpleType simple;
	
public:
	AdvancedType() {
		std::cout << "AdvancedType::ctor" << std::endl;
	}
	AdvancedType(int a) : simple(a, a) {
		std::cout << "AdvancedType::ctor(a)" << std::endl;
	}
	~AdvancedType() { std::cout << "AdvancedType::destructor" << std::endl; }
};

int main()
{
	SimpleType simpleObj;
	AdvancedType advObj;
	AdvancedType advObj2(10);
}