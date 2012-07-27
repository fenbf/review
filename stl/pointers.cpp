#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <iomanip>
#include <ctime>
#include <memory>

using namespace std;

struct Data
{
	int a, b, c;
	float f;
	Data(int v) : a(v), b(v), c(v) { f = (float)(a + b + c); cout << "Data::Data(int)" << endl; }
	~Data() { cout << "Data::~Data()" << endl; }
	
	friend ostream & operator<< (ostream &stream, const Data &s) 
	{
		return stream << "(" << s.a << ", " << s.b << ", " << s.c << ")";
	}
};
typedef shared_ptr<Data> DataSharedPtr;

void doSomething(DataSharedPtr p)
{
	p->a = 10;
	cout << "use count " << p.use_count() << endl;
}

int main(/*int argc, const char **argv*/)
{
	DataSharedPtr p = make_shared<Data>(12);
	//DataSharedPtr p(new Data(12));

	doSomething(p);
	
	cout << "use count " << p.use_count() << endl;
	cout << *p << endl;
	
	return 0;
}