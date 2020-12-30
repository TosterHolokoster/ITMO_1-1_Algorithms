#pragma once
#include <functional>
#include <string>


const size_t BUCKET_COUNT_TABLE[5] = { 17, 31, 61, 127, 257 };

template<typename K, typename V>
class MyDictionary final
{
public:
	struct Item
	{
	private:
		K key;
		V value;
	public:
		Item(const K& _key, const V& _value) : key(_key), value(_value) {}
		~Item() { key.~K(); value.~V(); }

		K& GetKey() { return key; }
		const K& GetKey() const { return key; }

		V& GetValue() { return value; }
		const V& GetValue() const { return value; }

		void SetValue(const V& _value) { value = _value; }
	};
	typedef Item* Bucket;


private:

	size_t BUCKET_COUNT = 17;
	const size_t BUCKET_SIZE = 8;
	const float LOAD_FACTOR = .75f;


	Bucket* buckets;
	size_t* bucketLoad;

	std::hash<K> defaultHash;

	size_t (*hash_function)(const K& Key);

	inline size_t getBucketIndex(const K& Key) const
	{
		if(hash_function != nullptr)
			return hash_function(Key) % BUCKET_COUNT;
		else
			return defaultHash(Key) % BUCKET_COUNT;
	}

	bool CheckOverload(size_t bucketID) { return bucketLoad[bucketID] + 1 >= BUCKET_SIZE * LOAD_FACTOR; }

	void FixOverload()
	{
		// Allocated new memory
		size_t newBucketCount = getNextBucketCount(BUCKET_COUNT);
		Bucket* newBucket = static_cast<Bucket*>(malloc(newBucketCount * sizeof(Bucket)));
		size_t* newBucketLoad = static_cast<size_t*>(malloc(newBucketCount * sizeof(size_t)));

		for (size_t i = 0; i < newBucketCount; i++)
		{
			newBucket[i] = static_cast<Bucket>(malloc(BUCKET_SIZE * sizeof(Item)));
			newBucketLoad[i] = 0;
		}

		// Copy elements and free old memory
		for (size_t i = 0; i < BUCKET_COUNT; i++)
		{
			for (size_t q = 0; q < bucketLoad[i]; q++)
			{
				size_t bucketID = getBucketIndex(buckets[i][q].GetKey());
				new (newBucket[bucketID] + newBucketLoad[bucketID]) Item(buckets[i][q].GetKey(), buckets[i][q].GetValue());
				newBucketLoad[bucketID]++;
				buckets[i][q].~Item();
			}
			free(buckets[i]);
		}
		free(buckets);
		free(bucketLoad);

		// Rebind pointers
		BUCKET_COUNT = newBucketCount;
		buckets = newBucket;
		bucketLoad = newBucketLoad;
	}

	size_t getNextBucketCount(size_t currentBucketCount)
	{
		for (size_t capacity : BUCKET_COUNT_TABLE)
		{
			if (capacity > currentBucketCount)
				return capacity;
		}
		throw std::exception("Max BUCKET_COUNT reached.");
	}

public:
	MyDictionary(size_t (*customHashFunction)(const K& Key) = nullptr)
	{
		hash_function = customHashFunction;

		// Initialzation of Buckets Array
		buckets = static_cast<Bucket*>(malloc(BUCKET_COUNT * sizeof(Bucket)));
		bucketLoad = static_cast<size_t*>(malloc(BUCKET_COUNT * sizeof(size_t)));

		// Initialzation of each Bucket; Set zero load of buckets;
		for (size_t i = 0; i < BUCKET_COUNT; i++)
		{
			buckets[i] = static_cast<Bucket>(malloc(BUCKET_SIZE * sizeof(Item)));
			bucketLoad[i] = 0;
		}
	}
	~MyDictionary()
	{
		for (size_t i = 0; i < BUCKET_COUNT; i++)
		{
			for (size_t q = 0; q < bucketLoad[i]; q++)
			{
				buckets[i][q].~Item();
			}
			free(buckets[i]);
		}
		free(buckets);
		free(bucketLoad);
	}

	void put(const K& key, const V& value)
	{
		size_t itemHash = getBucketIndex(key);

		if (CheckOverload(itemHash))
			FixOverload();

		new (buckets[itemHash] + bucketLoad[itemHash]) Item(key, value);
		bucketLoad[itemHash]++;
	}
	void remove(const K& key)
	{
		if (contains(key))
		{
			size_t bucketID = getBucketIndex(key);
			Bucket bucket = buckets[bucketID];
			for (size_t i = 0; i < bucketLoad[bucketID]; i++)
			{
				Item item = bucket[i];
				if (item.GetKey() == key)
				{
					item.~Item();

					// Shift items in bucket;
					for (; i < bucketLoad[bucketID] - 1; i++)
					{
						std::swap(bucket[i], bucket[i + 1]);
					}
					break;
				}
			}
			bucketLoad[bucketID]--;
		}
	}

	bool contains(const K& key) const
	{
		size_t itemHash = getBucketIndex(key);
		for (size_t q = 0; q < bucketLoad[itemHash]; q++)
		{
			if (buckets[itemHash][q].GetKey() == key)
				return true;
		}
		return false;
	}
	size_t size() const
	{
		size_t result = 0;
		for (size_t i = 0; i < BUCKET_COUNT; i++)
		{
			result += bucketLoad[i];
		}
		return result;
	}

	V& operator[](const K& key)
	{
		size_t itemHash = getBucketIndex(key);
		if (contains(key))
		{
			for (size_t i = 0; i < bucketLoad[itemHash]; i++)
			{
				Item item = buckets[itemHash][i];
				if (item.GetKey() == key)
					return item.GetValue();
			}
		}
		else
		{
			if (CheckOverload(itemHash))
				FixOverload();

			Item* item = buckets[itemHash] + bucketLoad[itemHash];
			new (item) Item(key, V());
			bucketLoad[itemHash]++;
			return item->GetValue();
		}
	}
	const V& operator[](const K& key) const
	{
		if (contains(key))
		{
			size_t itemHash = getBucketIndex(key);
			for (size_t i = 0; i < bucketLoad[itemHash]; i++)
			{
				Item item = buckets[itemHash][i];
				if (item.GetKey() == key)
					return item.GetValue();
			}
		}
		return V();
	}

	class Iterator
	{
		MyDictionary* dictionary;
		size_t currentBucket;
		size_t bucketOffet;
	public:
		Iterator(MyDictionary* _dictionary, size_t bucket) : dictionary(_dictionary), currentBucket(bucket), bucketOffet(0) {}

		const K& key() const { return dictionary->buckets[currentBucket][bucketOffet].GetKey(); }
		const V& value() const { return dictionary->buckets[currentBucket][bucketOffet].GetValue(); }

		void set(const V& value) { dictionary->buckets[currentBucket][bucketOffet].SetValue(value); }

		void next()
		{
			if (bucketOffet + 1 < dictionary->bucketLoad[currentBucket])
			{
				bucketOffet++;
			}
			else
			{
				bucketOffet = 0;
				do
				{
					currentBucket++;
				} while (dictionary->bucketLoad[currentBucket] == 0);
			}
		}
		void prev()
		{
			if (bucketOffet - 1 > 0)
			{
				bucketOffet--;
			}
			else
			{
				do
				{
					currentBucket--;
				} while (dictionary->bucketLoad[currentBucket] == 0);
				bucketOffet = dictionary->bucketLoad[currentBucket] - 1;
			}
		}

		bool hasNext() const
		{
			if (bucketOffet + 1 < dictionary->bucketLoad[currentBucket])
				return true;

			for (size_t i = currentBucket + 1; i < dictionary->BUCKET_COUNT; i++)
			{
				if (dictionary->bucketLoad[i] > 0)
					return true;
			}
			return false;
		}
		bool hasPrev() const
		{
			if (bucketOffet != 0)
				return true;

			for (size_t i = currentBucket - 1; i != 0; i--)
			{
				if (dictionary->bucketLoad[i] != 0)
					return true;
			}
			return false;
		}
	};

	Iterator iterator()
	{
		if (size() > 0)
		{
			for (size_t i = 0; i < BUCKET_COUNT; i++)
			{
				if (bucketLoad[i] > 0)
					return Iterator(this, i);
			}
		}
		return Iterator(this, 0);
	}
	const Iterator iterator() const
	{
		if (size() > 0)
		{
			for (size_t i = 0; i < BUCKET_COUNT; i++)
			{
				if (bucketLoad[i] > 0)
					return Iterator(this, i);
			}
		}
		return Iterator(this, 0);
	}
};