#include <iostream>
#include "MyDictionary.h"

using namespace std;


int main()
{
	MyDictionary<std::string, int> map = MyDictionary<std::string, int>();
	std::string key9 = "Nine";
	std::string key7 = "Seven";
	std::string key11 = "Eleven";
	std::string key2 = "Two";
	map.put(key9, 9);
	map.put(key7, 7);
	map.put(key11, 11);
	map.put(key2, 2);

	auto it = map.iterator();
	return 0;
}