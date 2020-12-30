#include <iostream>
#include "MyDictionary.h"

using namespace std;


int main()
{
	MyDictionary<std::string, int> map = MyDictionary<std::string, int>();
	map.put("Nine", 9);
	map.put("Seven", 7);
	map.put("Eleven", 11);
	map.put("Two", 2);

	cout << map["Two"] << endl;
	cout << map["Seven"] << endl;
	cout << map["Nine"] << endl;
	cout << map["Eleven"] << endl;
	return 0;
}