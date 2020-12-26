#include "pch.h"
#include "../Quicksort/Quicksort.h"

struct TestingStruct
{
public:
	int number;
	TestingStruct() : number(0) {}
	TestingStruct(int num) : number(num){}
};

const size_t ArrSize_int = 8;
const int ArrToSort_int[] { 6, 1, 3, 5, 8, 2, 7, 4 };
const int CorrectRes_int[] { 1, 2, 3, 4, 5, 6, 7, 8 };

const size_t ArrSize_float = 6;
const float ArrToSort_float[] { 73.4f, .11f, 73.0f, 44.001f, 6.9f, 44.0009f };
const float CorrectRes_float[] { .11f, 6.9f,  44.0009f,  44.001f, 73.0f, 73.4f };

const size_t ArrSize_struct = 4;
const int ArrToSort_struct[] { 21, 5, 17, 9 };
const int CorrectRes_struct[] { 5, 9, 17, 21 };

TEST(ISorting, SortInt) {
	int arrayToSort[ArrSize_int];
	copy(begin(ArrToSort_int), end(ArrToSort_int), begin(arrayToSort));
	myinsort<int>(arrayToSort, arrayToSort + ArrSize_int - 1, [](int a, int b) { return a < b; });
	for (size_t i = 0; i < ArrSize_int; i++)
	{
		ASSERT_EQ(arrayToSort[i], CorrectRes_int[i]);
	}
}
TEST(ISorting, SortFloat) {
	float arrayToSort[ArrSize_float];
	copy(begin(ArrToSort_float), end(ArrToSort_float), begin(arrayToSort));
	myinsort<float>(arrayToSort, arrayToSort + ArrSize_float - 1, [](float a, float b) { return a < b; });
	for (size_t i = 0; i < ArrSize_float; i++)
	{
		ASSERT_EQ(arrayToSort[i], CorrectRes_float[i]);
	}
}
TEST(ISorting, SortStruct) {
	TestingStruct arrayToSort[ArrSize_struct];
	for (size_t i = 0; i < ArrSize_struct; i++)
	{
		arrayToSort[i].number = ArrToSort_struct[i];
	}
	myinsort<TestingStruct>(arrayToSort, arrayToSort + ArrSize_struct - 1, [](TestingStruct a, TestingStruct b) { return a.number < b.number; });
	for (size_t i = 0; i < ArrSize_struct; i++)
	{
		ASSERT_EQ(arrayToSort[i].number, CorrectRes_struct[i]);
	}
}

TEST(QSorting, SortInt) {
	int arrayToSort[ArrSize_int];
	copy(begin(ArrToSort_int), end(ArrToSort_int), begin(arrayToSort));
	myqsort<int>(arrayToSort, arrayToSort + ArrSize_int - 1, [](int a, int b) { return a < b; });
	for (size_t i = 0; i < ArrSize_int; i++)
	{
		ASSERT_EQ(arrayToSort[i], CorrectRes_int[i]);
	}
}
TEST(QSorting, SortFloat) {
	float arrayToSort[ArrSize_float];
	copy(begin(ArrToSort_float), end(ArrToSort_float), begin(arrayToSort));
	myqsort<float>(arrayToSort, arrayToSort + ArrSize_float - 1, [](float a, float b) { return a < b; });
	for (size_t i = 0; i < ArrSize_float; i++)
	{
		ASSERT_EQ(arrayToSort[i], CorrectRes_float[i]);
	}
}
TEST(QSorting, SortStruct) {
	TestingStruct arrayToSort[ArrSize_struct];
	for (size_t i = 0; i < ArrSize_struct; i++)
	{
		arrayToSort[i].number = ArrToSort_struct[i];
	}
	myqsort<TestingStruct>(arrayToSort, arrayToSort + ArrSize_struct - 1, [](TestingStruct a, TestingStruct b) { return a.number < b.number; });
	for (size_t i = 0; i < ArrSize_struct; i++)
	{
		ASSERT_EQ(arrayToSort[i].number, CorrectRes_struct[i]);
	}
}