#include "pch.h"
#include "../Search/MyDictionary.h"

TEST(MyDictionary, CreateEmptyDictionary) {
	MyDictionary<std::string, int> map = MyDictionary<std::string, int>();
}

TEST(MyDictionary, PutElements) {
	MyDictionary<std::string, int> map = MyDictionary<std::string, int>();
	std::string key9 = "Nine";
	std::string key7 = "Seven";
	std::string key11 = "Eleven";
	std::string key2 = "Two";
	map.put(key9, 9);
	map.put(key7, 7);
	map.put(key11, 11);
	map.put(key2, 2);
	int res;
	res = map[key9];
	EXPECT_EQ(res, 9);
	res = map[key7];
	EXPECT_EQ(res, 7);
	res = map[key11];
	EXPECT_EQ(res, 11);
	res = map[key2];
	EXPECT_EQ(res, 2);
}

TEST(MyDictionary, Contain) {
	MyDictionary<int, bool> map = MyDictionary<int, bool>();
	int key = 5;
	map.put(key, true);
	EXPECT_TRUE(map.contains(key));
}
TEST(MyDictionary, Size) {
	MyDictionary<std::string, int> map = MyDictionary<std::string, int>();
	std::string key9 = "Nine";
	std::string key7 = "Seven";
	std::string key11 = "Eleven";
	std::string key2 = "Two";
	map.put(key9, 9);
	map.put(key7, 7);
	map.put(key11, 11);
	map.put(key2, 2);
	EXPECT_EQ(map.size(), 4);
}

TEST(MyDictionary, RemoveElements) {
	MyDictionary<std::string, int> map = MyDictionary<std::string, int>();
	std::string key9 = "Nine";
	std::string key7 = "Seven";
	std::string key11 = "Eleven";
	std::string key2 = "Two";
	map.put(key9, 9);
	map.put(key7, 7);
	map.put(key11, 11);
	map.put(key2, 2);
	EXPECT_TRUE(map.contains(key9) && map.contains(key7) && map.contains(key11) && map.contains(key2));

	map.remove(key9);
	map.remove(key11);
	EXPECT_EQ(map.size(), 2);
	EXPECT_TRUE(map.contains(key7) && map.contains(key2));
}

TEST(MyDictionary, IteratorTest) {
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
	EXPECT_FALSE(it.hasPrev());
	EXPECT_TRUE(it.hasNext());
	it.next();
	EXPECT_TRUE(it.hasPrev());
	EXPECT_TRUE(it.hasNext());
	it.set(666);
	EXPECT_EQ(it.value(), 666);
	it.next();
	it.next();
	EXPECT_TRUE(it.hasPrev());
	EXPECT_FALSE(it.hasNext());
}