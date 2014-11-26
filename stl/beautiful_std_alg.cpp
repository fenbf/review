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

#ifndef __func__
	#define __func__ __FUNCTION__
#endif

#define PRINT_TEST_TITLE() std::cout << std::endl << "*** " << __func__ << " ***" << std::endl;

template <typename T> void printAll(T start, T end, const std::string &title = "")
{
	if (!title.empty())
		std::cout << title << " : ";

	for (auto i = start; i != end; ++i)
		std::cout << *i << ", ";
	std::cout << std::endl;
}

template <typename T, typename V> void generateRand(T start, T end, V startValue)
{
	std::iota(start, end, startValue);
	std::random_shuffle(start, end);
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
// template<class FwdIt, class Compare = std::less<>>
// void quickSort(FwdIt first, FwdIt last, Compare cmp = Compare{})
// {
	// auto const N = std::distance(first, last);
	// if (N <= 1) return; 
	// auto const pivot = std::next(first, N / 2);
	// std::nth_element(first, pivot, last, cmp);
	// quickSort(first, pivot, cmp); // assert(std::is_sorted(first, pivot, cmp));
	// quickSort(pivot, last, cmp);  // assert(std::is_sorted(pivot, last, cmp));

	// // can be optimized by adding insertionSort call for small ranges (like 7...)
// }

// void quickSortTest()
// {
	// PRINT_TEST_TITLE();

	// int intArray[5];
	// generateRand(intArray, intArray + 5, 1);
	// printAll(intArray, intArray + 5, "before");

	// quickSort(intArray, intArray + 5);
	// printAll(intArray, intArray + 5, "after");
// }

//
// 3. slide from Cpp Seasoning
//
// bug in GCC std: https://gcc.gnu.org/ml/gcc-help/2013-10/msg00000.html
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=58357
// http://stackoverflow.com/questions/23993333/stdrotate-return-value-in-gcc-4-9
// std::rotate returns only void... but should an iterator...

template <typename randIter> auto slide(randIter f, randIter l, randIter p) -> std::pair<randIter, randIter>
{
	if (p < f) return { p, std::rotate(p, f, l) ); 
	if (l < p) return { std::rotate(f, l, p), p };
	return { f, l };
}

void slideTest()
{
	PRINT_TEST_TITLE();

	std::vector<double> dvec(10);
	std::iota(std::begin(dvec), std::end(dvec), -10.0);
	printAll(std::begin(dvec), std::end(dvec), "initial");

	auto p = slide(std::begin(dvec), std::next(std::begin(dvec), 3), std::end(dvec));
	printAll(std::begin(dvec), std::end(dvec), "+ 3 right");
	std::cout << *(p.first) << std::endl;
}

//
// X. trim for strings
//
// std::string trimLeft(const std::string &s) {
	// auto temp = s;
	// temp.erase(std::begin(temp), std::find_if(std::begin(temp), std::end(temp), [](char c){return !std::isspace(c, std::locale()); }));
	// return temp;
// }

// std::string trimRight(const std::string &s) {
	// auto temp = s;
	// temp.erase(std::find_if(std::rbegin(temp), std::rend(temp), [](char c){return !std::isspace(c, std::locale()); }).base(), std::end(temp));
	// return temp;
// }

// std::string trim(const std::string &s) {
	// return trimLeft(trimRight(s));
// }

// void trimStringTest()
// {
	// PRINT_TEST_TITLE();

	// std::string test = "   Hello World 1   ";
	// std::cout << "\"" << test << "\" -> \"" << trimLeft(test) << "\"" << std::endl;
	// std::string test2 = "   Hello World 2   ";
	// std::cout << "\"" << test2 << "\" -> \"" << trimRight(test2) << "\"" << std::endl;
	// std::string test3 = "   Hello World 3   ";
	// std::cout << "\"" << test3 << "\" -> \"" << trim(test3) << "\"" << std::endl;
// }

//
// X. sort with next_permutation
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
	insertionSortTest();
	// quickSortTest();
	// trimStringTest();
	slideTest();
	permuteSortTest();
}