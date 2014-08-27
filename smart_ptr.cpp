#include <iostream>
#include <memory>

///////////////////////////////////////////////////////////////////////////////
class Test
{
public:
	Test() :m_value(0) { std::cout << "Test::Test" << std::endl; }
	Test(const Test &t) :m_value(0) { std::cout << "Test::Test copy" << std::endl; }
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
void SharedPtrCastTest();
///////////////////////////////////////////////////////////////////////////////

void main()
{
	//AutoPtrTest();

	//UniquePtrTest();

	//UniquePtrArrayTest();

	//SharedPtrTest();

	//SharedPtrArrayTest();

	//SharedPtrParamTest();

	SharedPtrCastTest();
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
}

///////////////////////////////////////////////////////////////////////////////
// shared ptr array tests

void SharedPtrArrayTest()
{
	std::shared_ptr<Test> sp(new Test[2], [](Test *p) { delete[] p; });
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

///////////////////////////////////////////////////////////////////////////////
// shared ptr cast

class BaseA
{
protected:
	int a{ 0 };
public:
	virtual ~BaseA() { }

	void A(int p) { a = p; }
};

class ChildB : public BaseA
{
private:
	int b{ 0 };
public:
	void B(int p) { b = p; }
};

class BadChild
{
private:
	int c{ 0 };
public:
	void C(int p) { c = p; }
};

void SharedPtrCastTest()
{
	std::shared_ptr<BaseA> ptrBase = std::make_shared<ChildB>();
	ptrBase->A(10);
	std::cout << "use count A: " << ptrBase.use_count() << std::endl;
	
	// manual:
	ChildB *ptrMan = dynamic_cast<ChildB *>(ptrBase.get());
	ptrMan->B(10);

	// ok:
	std::shared_ptr<ChildB> ptrChild = std::dynamic_pointer_cast<ChildB>(ptrBase);
	if (ptrChild)
	{
		ptrChild->B(20);
		std::cout << "use count A: " << ptrBase.use_count() << std::endl;
		std::cout << "use count B: " << ptrChild.use_count() << std::endl;
	}	

	// bad:
	std::shared_ptr<BadChild> ptrBad = std::dynamic_pointer_cast<BadChild>(ptrBase);
	if (!ptrBad)
	{
		std::cout << "problem with cast!" << std::endl;
	}
}
