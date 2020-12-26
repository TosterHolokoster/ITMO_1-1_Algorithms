#pragma once


template<typename K, typename V>
class MyDictionary final
{
	void FixOverload() { throw std::exception("Finction not implemented!"); }

public:
	struct Item
	{
	private:
		K key;
		V value;
	public:
		Item(K _key, V _value) : key(_key), value(_value) {}
		~Item() { key.~K(); value.~V(); }

		K& GetKey() { return key; }
		const K& GetKey() const { return key; }

		V& GetValue() { return value; }
		const V& GetValue() const { return value; }

		void SetValue(const V& _value) { value = _value; }
	};
	typedef Item* Bucket;


private:
	const size_t BUCKET_COUNT = 17;
	const size_t BUCKET_SIZE = 8;
	const float LOAD_FACTOR = .75f;

	Bucket* buckets;
	size_t* bucketLoad;

	inline size_t hash(const K& Key) const
	{
		return reinterpret_cast<unsigned long>(&Key) % BUCKET_COUNT;
	}

	bool CheckOverload(size_t bucketID) { return bucketLoad[bucketID] + 1 >= BUCKET_SIZE * LOAD_FACTOR; }

public:
	MyDictionary()
	{
		// Initialzation of Buckets Array
		buckets = static_cast<Bucket*>( malloc(BUCKET_COUNT * sizeof(Bucket)) );
		bucketLoad = static_cast<size_t*>( malloc(BUCKET_COUNT * sizeof(size_t)) );

		// Initialzation of each Bucket; Set zero load of buckets;
		for (size_t i = 0; i < BUCKET_COUNT; i++)
		{
			buckets[i] = static_cast<Bucket>( malloc(BUCKET_SIZE * sizeof(Item)) );
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
		size_t itemHash = hash(key);

		if (CheckOverload(itemHash))
			FixOverload();

		new (buckets[itemHash] + bucketLoad[itemHash]) Item(key, value);
		bucketLoad[itemHash]++;
	}
	void remove(const K& key)
	{
		if (contains(key))
		{
			size_t itemHash = hash(key);
			Bucket bucket = buckets[itemHash];
			for (size_t i = 0; i < bucketLoad[itemHash]; i++)
			{
				Item item = bucket[i];
				if (item.GetKey() == key)
				{
					item.~Item();

					// Shift items in bucket;
					for (; i < bucketLoad[itemHash] - 1; i++)
					{
						std::swap(bucket[i], bucket[i + 1]);
					}
					break;
				}
			}
			bucketLoad[itemHash]--;
		}
	}

	bool contains(const K& key) const
	{
		size_t itemHash = hash(key);
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
		if (contains(key))
		{
			size_t itemHash = hash(key);
			for (size_t i = 0; i < bucketLoad[itemHash]; i++)
			{
				Item item = buckets[itemHash][i];
				if (item.GetKey() == key)
					return item.GetValue();
			}
		}
		else
		{
			put(key, V());
		}
		return (*this)[key];
	}
	const V& operator[](const K& key) const
	{
		if (contains(key))
		{
			size_t itemHash = hash(key);
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