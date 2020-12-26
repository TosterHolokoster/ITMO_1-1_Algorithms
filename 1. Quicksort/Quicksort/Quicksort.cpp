#include "Quicksort.h"
#include <chrono>

using namespace std::chrono;

const int arrayToSort[] { 53, 52, 21, 89, 46, 87, 55, 94, 72, 49, 45, 96, 20, 58, 100, 42, 68, 13, 66, 19, 32, 70, 56, 61, 99, 51, 37, 11, 65, 98, 7, 38 };
//const int arrayToSort[] { 29, 59, 25, 21, 40, 79, 75, 86, 98, 80, 76, 70, 32, 13, 68, 6 };

const size_t ArrSize_int = sizeof(arrayToSort) / sizeof(int);


int main()
{
	steady_clock::time_point start;
	steady_clock::time_point stop;

	int i_arrayToSort[ArrSize_int];
	int q_arrayToSort[ArrSize_int];
	copy(begin(arrayToSort), end(arrayToSort), begin(i_arrayToSort));
	copy(begin(arrayToSort), end(arrayToSort), begin(q_arrayToSort));


	start = high_resolution_clock::now();
	myinsort<int>(i_arrayToSort, i_arrayToSort + ArrSize_int - 1, [](int a, int b) { return a < b; });
	stop = high_resolution_clock::now();
	cout << "Insert Sorting duration: " << duration_cast<microseconds>(stop - start).count() << endl;

	start = high_resolution_clock::now();
	myqsort<int>(q_arrayToSort, q_arrayToSort + ArrSize_int - 1, [](int a, int b) { return a < b; });
	stop = high_resolution_clock::now();
	cout << "Quick Sorting duration: " << duration_cast<microseconds>(stop - start).count() << endl;

	return 0;
}