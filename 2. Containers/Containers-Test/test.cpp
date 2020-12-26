#include "pch.h"
#include "../Containers_mono/MyList.h"
#include "../Containers_mono/MyArray.h"
#include "../Containers_mono/MyItem.h"

TEST(ListTests, InsertHead) {
	MyList<int> list = MyList<int>();
	list.insertHead(5);
	ASSERT_EQ(list.head(), 5);
	list.insertHead(10);
	ASSERT_EQ(list.head(), 10);
}

TEST(ListTests, CustomClass) {
	MyList<MyItem> list = MyList<MyItem>();
	list.insertHead(MyItem("One"));
	ASSERT_EQ(list.head().getName(), "One");
	list.insertHead(MyItem("Two"));
	ASSERT_EQ(list.head().getName(), "Two");
}

TEST(ListTests, InsertTail) {
	MyList<int> list = MyList<int>();
	list.insertTail(10);
	ASSERT_EQ(list.tail(), 10);
	list.insertTail(5);
	ASSERT_EQ(list.tail(), 5);
}

TEST(ListTests, RemoveHead) {
	MyList<int> list = MyList<int>();
	list.insertHead(5);
	list.insertHead(10);
	list.insertHead(15);
	ASSERT_EQ(list.head(), 15);
	list.removeHead();
	ASSERT_EQ(list.head(), 10);
	list.removeHead();
	ASSERT_EQ(list.head(), 5);
}

TEST(ListTests, RemoveTail) {
	MyList<int> list = MyList<int>();
	list.insertTail(5);
	list.insertTail(10);
	list.insertTail(15);
	ASSERT_EQ(list.tail(), 15);
	list.removeTail();
	ASSERT_EQ(list.tail(), 10);
	list.removeTail();
	ASSERT_EQ(list.tail(), 5);
}

TEST(ListTests, GetHeadTail) {
	MyList<int> list = MyList<int>();
	list.insertHead(5);
	list.insertTail(10);
	ASSERT_EQ(list.head(), 5);
	ASSERT_EQ(list.tail(), 10);
}

TEST(ListTests, GetSize) {
	MyList<int> list = MyList<int>();
	list.insertHead(5);
	list.insertTail(10);
	list.insertTail(15);
	ASSERT_EQ(list.size(), 3);
}

TEST(ListTests, IteratorTest) {
	MyList<int> list = MyList<int>();
	list.insertHead(5);
	list.insertTail(10);
	list.insertTail(15);
	auto i = list.iterator();
	ASSERT_EQ(i.get(), 5);
	ASSERT_EQ(i.hasNext(), true);
	ASSERT_EQ(i.hasPrev(), false);
	i.next();
	i.next();
	ASSERT_EQ(i.get(), 15);
	ASSERT_EQ(i.hasNext(), false);
	ASSERT_EQ(i.hasPrev(), true);
	i.prev();
	ASSERT_EQ(i.get(), 10);
	i.set(50);
	ASSERT_EQ(i.get(), 50);
}


/// 
/// ARRAY
/// 

TEST(ArrayTests, Inserts) {
	MyArray<int> myarray = MyArray<int>();
	myarray.insert(5);
	myarray.insert(10);
	myarray.insert(20);
	myarray.insert(15, 2);
	ASSERT_EQ(myarray[0], 5);
	ASSERT_EQ(myarray[1], 10);
	ASSERT_EQ(myarray[2], 15);
	ASSERT_EQ(myarray[3], 20);
}

TEST(ArrayTests, CustomClass) {
	MyArray<MyItem> myarray = MyArray<MyItem>();
	myarray.insert(MyItem("One"));
	myarray.insert(MyItem("Two"));
	ASSERT_EQ(myarray[0].getName(), "One");
	ASSERT_EQ(myarray[1].getName(), "Two");
}

TEST(ArrayTests, Remove) {
	MyArray<int> myarray = MyArray<int>();
	myarray.insert(10);
	myarray.insert(15);
	myarray.insert(20);
	myarray.remove(1);
	ASSERT_EQ(myarray[0], 10);
	ASSERT_EQ(myarray[1], 20);
}

TEST(ArrayTests, Size) {
	MyArray<int> myarray = MyArray<int>();
	myarray.insert(5);
	myarray.insert(10);
	myarray.insert(20);
	myarray.insert(15, 2);
	ASSERT_EQ(myarray.size(), 4);
	myarray.remove(0);
	ASSERT_EQ(myarray.size(), 3);
}

TEST(ArrayTests, IteratorTest) {
	MyArray<int> myarray = MyArray<int>();
	myarray.insert(0);
	myarray.insert(5);
	myarray.insert(15);
	myarray.insert(20);
	auto i = myarray.iterator();
	ASSERT_EQ(i.get(), 0);
	ASSERT_EQ(i.hasNext(), true);
	ASSERT_EQ(i.hasPrev(), false);
	i.next();
	i.next();
	i.insert(10);
	ASSERT_EQ(i.get(), 10);
	ASSERT_EQ(i.hasNext(), true);
	ASSERT_EQ(i.hasPrev(), true);
	i.next();
	ASSERT_EQ(i.get(), 15);
	i.remove();
	ASSERT_EQ(i.get(), 20);
	ASSERT_EQ(i.hasNext(), false);
	ASSERT_EQ(i.hasPrev(), true);
	i.toIndex(1);
	i.prev();
	ASSERT_EQ(i.get(), 0);
	i.set(100);
	ASSERT_EQ(i.get(), 100);
}