#include <iostream>
#include <memory>

///////////////////////////////////////////////////////////////////////////////
class Test
{
public:
  Test():m_value(0) { std::cout << "Test::Test" << std::endl; }
	Test(const Test &t):m_value(0) { std::cout << "Test::Test copy" << std::endl; }
	~Test() { std::cout << "Test::~Test destructor" << std::endl; }

	int m_value;
};

typedef std::auto_ptr<Test> TestAutoPtr;
typedef std::unique_ptr<Test> TestUniquePtr;

///////////////////////////////////////////////////////////////////////////////
void AutoPtrTest();
void UniquePtrTest();
void UniquePtrArrayTest();
void SharedPtrTest();
void SharedPtrArrayTest();
void SharedPtrParamTest();
///////////////////////////////////////////////////////////////////////////////

void main()
{
	//AutoPtrTest();
	
	//UniquePtrTest();

	//UniquePtrArrayTest();

	//SharedPtrTest();

	//SharedPtrArrayTest();

	SharedPtrParamTest();

	int a = 0;
	return;
}

///////////////////////////////////////////////////////////////////////////////
// auto ptr tests

void doSomethig(TestAutoPtr myPtr)
{
	myPtr->m_value = 11;
}

void AutoPtrTest()
{
	TestAutoPtr myTest(new Test());
	doSomethig(myTest);
	
	myTest->m_value = 10;
}

///////////////////////////////////////////////////////////////////////////////
// unique ptr tests

void doSomethig(TestUniquePtr myPtr)
{
	myPtr->m_value = 11;
}

void UniquePtrTest()
{
	TestUniquePtr myTest(new Test());
	doSomethig(std::move(myTest));
	
	// myTest->m_value = 10;	// runtime error, but this time on purpose!
}

///////////////////////////////////////////////////////////////////////////////
// unique ptr array tests

void UniquePtrArrayTest()
{
	// posiible, but generates runtime error
	// std::unique_ptr<int> p(new int[10]); // only delete will be called

	std::unique_ptr<Test[]> tests(new Test[3]);
}

///////////////////////////////////////////////////////////////////////////////
// shared ptr tests

void SharedPtrTest()
{
	std::shared_ptr<Test> sp(new Test());

	std::shared_ptr<Test> sp2 = std::make_shared<Test>();

	int a;
}

///////////////////////////////////////////////////////////////////////////////
// shared ptr array tests

void SharedPtrArrayTest()
{
	std::shared_ptr<Test> sp(new Test[2], [](Test *p) { delete [] p; });
}

///////////////////////////////////////////////////////////////////////////////
// shared ptr param tests

void testSharedFunc(std::shared_ptr<Test> sp)
{
	sp->m_value = 10;
}

void testSharedFuncRef(const std::shared_ptr<Test> &sp)
{
	sp->m_value = 10;
}

void SharedPtrParamTest()
{
	std::shared_ptr<Test> sp = std::make_shared<Test>();

	testSharedFunc(sp);
	testSharedFuncRef(sp);
}
