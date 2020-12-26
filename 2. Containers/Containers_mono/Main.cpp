#include "MyList.h"
#include "MyItem.h"
#include "MyArray.h"

int main()
{
	MyArray<MyItem> myarray = MyArray<MyItem>();
	myarray.insert(MyItem("One"));
	myarray.insert(MyItem("three"));
	myarray.insert(MyItem("Two"), 2);
}