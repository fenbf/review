// "Top 7 Beautiful std::algorithm Examples"
// found in various places
// Bartlomiej Filipek, www.bfilipek.com
// August-November 2014

#include <iostream>
#include <algorithm>
#include <string>
#include <locale> // isspace
#include <numeric> // iota
#include <vector>
#include <random>
//#include <functional>   // std::not1

#ifndef __func__
	#define __func__ __FUNCTION__
#endif

#define PRINT_TEST_TITLE() std::cout << std::endl << "*** " << __func__ << " ***" << std::endl;

//
// helper functions
//

template <typename T> void printAll(T start, T end, const std::string &title = "")
{
	if (!title.empty())
		std::cout << title << " : ";

	for (auto i = start; i != end; ++i)
		std::cout << *i << ", ";
	std::cout << std::endl;
}

//
// X: random shuffle
// 
template <typename T, typename V> void generateRand(T start, T end, V startValue)
{
	std::iota(start, end, startValue);
	
	// deprecated in C++14:
	// std::random_shuffle(start, end);
	
	std::random_device rd;
    std::mt19937 gen(rd());
	std::shuffle(start, end, gen);
}

//
// 1: insertionSort in just two lines of code
//
template <typename T> void insertionSort(T start, T end)
{
	for (auto i = start; i != end; ++i)
		std::rotate(std::upper_bound(start, i, *i), i, std::next(i));
}

void insertionSortTest()
{
	PRINT_TEST_TITLE();

	int intArray[5];
	generateRand(intArray, intArray + 5, 1);
	printAll(intArray, intArray + 5, "before");

	insertionSort(intArray, intArray + 5);
	printAll(intArray, intArray + 5, "after");
}

//
// 2. quick sort made with std::algorithm building blocks
//
// source: http://stackoverflow.com/a/24650627/486617 "Algorithmic building blocks"
template<class FwdIt, class Compare = std::less<>>
void quickSort(FwdIt first, FwdIt last, Compare cmp = Compare{})
{
	auto const N = std::distance(first, last);
	if (N <= 1) return; 
	auto const pivot = std::next(first, N / 2);
	std::nth_element(first, pivot, last, cmp);
	quickSort(first, pivot, cmp); // assert(std::is_sorted(first, pivot, cmp));
	quickSort(pivot, last, cmp);  // assert(std::is_sorted(pivot, last, cmp));

	// can be optimized by adding insertionSort call for small ranges (like 7...)
}

void quickSortTest()
{
	PRINT_TEST_TITLE();

	int intArray[5];
	generateRand(intArray, intArray + 5, 1);
	printAll(intArray, intArray + 5, "before");

	quickSort(intArray, intArray + 5);
	printAll(intArray, intArray + 5, "after");
}

//
// 3. slide from Cpp Seasoning
//
// use case: list of items, make continous selection and move that selection into a new 'p' position.
//
// bug in GCC std: https://gcc.gnu.org/ml/gcc-help/2013-10/msg00000.html
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=58357
// http://stackoverflow.com/questions/23993333/stdrotate-return-value-in-gcc-4-9
// std::rotate returns only void... but should an iterator...

#ifdef __GNUC__
void slideTest() 
{
	#warning "GCC version of this code is missing due to a bug in std lib"
}
#else
template <typename randIter> auto slide(randIter f, randIter l, randIter p) -> std::pair<randIter, randIter>
{
	if (p < f) return { p, std::rotate(p, f, l) };
	if (l < p) return { std::rotate(f, l, p), p };
	return { f, l };
}

void slideTest()
{
	PRINT_TEST_TITLE();

	int intArray[10] = { 0 };
	intArray[1] = intArray[2] = intArray[3] = 1;
	printAll(std::begin(intArray), std::end(intArray), "initial");

	// move to the right those three '1'

	auto p = slide(intArray + 1, intArray + 4, intArray + 6);
	printAll(std::begin(intArray), std::end(intArray), "to id 6");
	std::cout << "new range from " << std::distance(intArray, p.first) << " to " << std::distance(intArray, p.second) << " position" << std::endl;

	// go back:
	auto p2 = slide(p.first, p.second, intArray + 1);
	printAll(std::begin(intArray), std::end(intArray), "back");
	std::cout << "new range from " << std::distance(intArray, p2.first) << " to " << std::distance(intArray, p2.second) << " position" << std::endl;
}
#endif

//
// 4. gather (cpp seasoning)
//
// use case: list of items, select some of items (good guys) and move the to position around p.
// for instance: multiple selection on a list
//
// problem with std::not1: http://channel9.msdn.com/Events/GoingNative/2013/Cpp-Seasoning#c635149692925101916

template <typename I, // I models BidirectionalIterator
	typename S> // S models UnaryPredicate
	auto gather(I f, I l, I p, S s) -> std::pair < I, I >
{
	using value_type = typename std::iterator_traits<I>::value_type;
	return{ std::stable_partition(f, p, [&](const value_type& x){ return !s(x); }),
			std::stable_partition(p, l, s) };
}

void gatherTest()
{
	PRINT_TEST_TITLE();
	
	int intArray[10] = { 0 };
	intArray[0] = intArray[2] = intArray[7] = intArray[8] = 1;
	printAll(intArray, intArray + 10, "before");
	
	// gather all '1's and move them around 4th place in the array
	auto range = gather(intArray, intArray + 10, intArray + 4, [](int x) { return x == 1; });
	printAll(intArray, intArray + 10, "after");

	std::cout << "selected items from " << std::distance(intArray, range.first) << " to " << std::distance(intArray, range.second) << " position" << std::endl;
}

//
// 5. trim for strings
//
// source: http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
std::string trimLeft(const std::string &s) {
	auto temp = s;
	temp.erase(std::begin(temp), std::find_if(std::begin(temp), std::end(temp), [](char c){return !std::isspace(c, std::locale()); }));
	return temp;
}

#ifdef __GNUC__
std::string trimRight(const std::string &s) {
	auto temp = s;
	const auto tempRbeg = temp.rbegin();
	const auto tempRend = temp.rend();
	temp.erase(std::find_if(tempRbeg, tempRend, [](char c){return !std::isspace(c, std::locale()); }).base(), std::end(temp));
	return temp;
}
#else
std::string trimRight(const std::string &s) {
	auto temp = s;
	temp.erase(std::find_if(std::rbegin(temp), std::rend(temp), [](char c){return !std::isspace(c, std::locale()); }).base(), std::end(temp));
	return temp;
}
#endif

std::string trim(const std::string &s) {
	return trimLeft(trimRight(s));
}

void trimStringTest()
{
	PRINT_TEST_TITLE();

	std::string test = "   Hello World 1   ";
	std::cout << "\"" << test << "\" -> \"" << trimLeft(test) << "\"" << std::endl;
	std::string test2 = "   Hello World 2   ";
	std::cout << "\"" << test2 << "\" -> \"" << trimRight(test2) << "\"" << std::endl;
	std::string test3 = "   Hello World 3   ";
	std::cout << "\"" << test3 << "\" -> \"" << trim(test3) << "\"" << std::endl;
}

//
// bonus :) sort with next_permutation
//
template <typename T> void permuteSort(T start, T end)
{
	while (std::next_permutation(start, end));
}

void permuteSortTest()
{
	PRINT_TEST_TITLE();

	int intArray[7];
	generateRand(intArray, intArray + 7, 10);
	printAll(intArray, intArray + 7, "before");

	permuteSort(intArray, intArray + 7);
	printAll(intArray, intArray + 7, "after");
}

int main()
{
	// 1:
	insertionSortTest();

	// 2:
	quickSortTest();

	// 3:
	slideTest();
	
	// 4:
	gatherTest();
	
	// 5:
	trimStringTest();
	
	// bonus: :)
	permuteSortTest();
}