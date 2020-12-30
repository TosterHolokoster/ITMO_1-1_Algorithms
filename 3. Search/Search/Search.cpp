#include <iostream>
#include "MyDictionary.h"

using namespace std;

class MyItem
{
	int number;
public:
	MyItem() : number(-1)
	{
		cout << "MyItem()\n";
	}
	MyItem(int n) : number(n)
	{
		cout << "MyItem(" << n <<"):\n";
	}
	~MyItem()
	{
		cout << "~MyItem(): number - " << number << "\n";
	}
	int GetNumber() { return number; }
};

int main()
{
	MyDictionary<int, MyItem> map = MyDictionary<int, MyItem>();
	for (size_t i = 0; i < 17; i++)
	{
		map.put(i, MyItem(i));
	}
	cout << "DONE\n";
	//map.put("1", 1);
	//map.put("2", 2);
	//map.put("3", 3);
	//map.put("4", 4);
	//map.put("5", 5);
	//map.put("6", 6);
	//map.put("7", 7);
	//map.put("8", 8);
	//map.put("9", 9);
	//map.put("10", 10);
	//map.put("11", 11);
	//map.put("12", 12);
	//map.put("13", 13);
	//map.put("14", 14);
	//map.put("15", 15);
	//map.put("16", 16);
	//map.put("17", 17);
	//map.put("18", 18);
	//map.put("19", 19);
	//map.put("20", 20);
	return 0;
}