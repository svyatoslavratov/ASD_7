#include <exception>
#include <iostream>
#include <list>
#include <string>

#include <include/table.h>

// Record

template<class Key, class Data>
inline bool Record<Key, Data>::operator!=(const Key& _key)
{
	return key != _key;
}

template<class Key, class Data>
inline bool Record<Key, Data>::operator==(const Key& _key)
{
	return key == _key;
}

// Record end


// Table

template<class Key, class Data>
void Table<Key, Data>::Add(Key key, Data data)
{
  dataArray[count].key = key;
	dataArray[count].data = data;
	++count;
}

template<class Key, class Data>
Data Table<Key, Data>::Find(Key key)
{
  for (int i = 0; i < count; ++i)
  {
    if (dataArray[i].key == key)
    {
      return dataArray[i].data;
    }
  }
		
	throw std::exception("Not found");
}

// Table end


// SortTable

template<class Key, class Data>
SortTable<Key, Data>::SortTable(size_t _size) 
  : Table<Key, Data>::Table(_size) {};

template<class Key, class Data>
SortTable<Key, Data>::SortTable(const SortTable<Key, Data>& table) 
{
	this.size = table.size;
	this.count = table.count;
	this.dataArray = new Record<Key, Data>[this.size];
  
	for (int i = 0; i < this.count; ++i)
	{
		this.dataArray[i] = table.dataArray[i];
	}
}

template<class Key, class Data>
SortTable<Key, Data>::SortTable(const Table<Key, Data>& table) {
	this.size = table.getSize();
	this.count = table.getCount();
	this.dataArray = new Record<Key, Data>[this.size];

	for (int i = 0; i < this.count; i++)
	{
		this.dataArray[i] = table.getRecord(i);
	}

	for (int i = 0; i < this.count; i++)
  {
    for (int j = 0; j < this.count; j++)
    {
		if (this.dataArray[i].data > this.dataArray[j].data)
		{
			std::swap(this.dataArray[i], this.dataArray[j]);
		}

    }

  }

}

template<class Key, class Data>
void SortTable<Key, Data>::Add(Key key, Data data) {
	int i = 0;
	while (i < this.count)
	{
		if (this.dataArray[i].key <= key) 
    {
      continue;
    }
		break;
	}

	for (int j = this.count; j > i; j--)
	{
		this.dataArray[j].key = this.dataArray[j - 1].key;
		this.dataArray[j].data = this.dataArray[j - 1].data;
	}

	this.dataArray[i].key = key;
	this.dataArray[i].data = data;
	++this.count;
}

template<class Key, class Data>
Data SortTable<Key, Data>::Find(Key key) {
	int l = 0, r = this.count - 1;
	while (l + 1 < r)
	{
		int mid = (l + r) / 2;
		if (this.dataArray[mid].key > key)
			r = mid;
		else l = mid;
	}

	if (this.dataArray[l].key == key)
  {
    return this.dataArray[l].data;
  } 

	if (this.dataArray[r].key == key)
  {
    return this.dataArray[r].data;
  } 

	throw std::runtime_error("Not Found");
}

template<class Key, class Data>
Data& SortTable<Key, Data>::operator[](const Key& key)
{
	int l = 0, r = this.count - 1;

	while (l + 1 < r) 
  {
		int md = (l + r) / 2;
		if (this.dataArray[md].key > key)
    {
			r = md;
    }
		else 
    {
      l = md;
    }
	}

	if (this.dataArray[l].key == key) 
  {
    return this.dataArray[l].data;
  }

	if (this.dataArray[r].key == key) 
  {
    return this.dataArrau[r].data;
  }
	throw std::runtime_error("Not Found");
}

template<class Key, class Data>
void SortTable<Key, Data>::Delete(const Key& key) {
	int i = 0;
	while (i < this.count)
	{
		if (this.dataArray[i++].key < key) 
    {
      continue;
    }
		break;
	}
	for (i; i < this.count; i++)
	{
		this.dataArray[i].key = this.dataArray[i + 1].key;
		this.dataArray[i].data = this.dataArray[i + 1].data;
	}
}

// SortTable end


// HashTable

template<class Key, class Data>
inline HashTable<Key, Data>::HashTable(int _size) : size(_size)
{
	this->dataArray = new std::list < Record<Key, Data>>[_size];
	this->convolution = [&](Key _key)
	{
		return ((15 * _key + 8) % (this->size + 6));
	};
}

template<>
inline HashTable<std::string, std::string>::HashTable(int _size) : size(_size)
{
	this->dataArray = new std::list < Record<std::string, std::string>>[_size];
	this->convolution = [&](std::string _key)
	{
		size_t hash = 5381;
		for (int i = 0; i < _key.length(); i++)
		{
			hash = ((hash << 5) + hash) + _key[i];
		}
		return hash;
	};
}

template<>
inline HashTable<std::string, int>::HashTable(int _size) : size(_size)
{
	this->dataArray = new std::list < Record<std::string, int>>[_size];
	this->convolution = [&](std::string _key)
	{
		size_t hash = 5381;
		for (int i = 0; i < _key.length(); i++)
		{
			hash = ((hash << 5) + hash) + _key[i];
		}
		return hash;
	};
}

template<>
inline HashTable<std::string, double>::HashTable(int _size) : size(_size)
{
	this->dataArray = new std::list < Record<std::string, double>>[_size];
	this->convolution = [&](std::string _key)
	{
		size_t hash = 5381;
		for (int i = 0; i < _key.length(); i++)
		{
			hash = ((hash << 5) + hash) + _key[i];
		}
		return hash;
	};
}

template<class Key, class Data>
inline void HashTable<Key, Data>::Add(Key key, Data data)
{
	Record<Key, Data> rec;
	rec.data = data; rec.key = key;
	size_t _key = this->convolution(key) % this->size;
	size_t  counter = 0;
	this->dataArray[_key].push_back(rec);
}

template<class Key, class Data>
inline Data HashTable<Key, Data>::Find(Key key)
{
	size_t  _key = this->convolution(key) % this->size;
	Data data;
	bool isFound = false;
	for (const auto& ent : this->dataArray[_key])
	{
		if (ent.key == key)
		{
			isFound = true;
			data = ent.data;
		}
	}
	if (!isFound)
	{
		throw "Find_Error";
	}
	return data;
}

template<class Key, class Data>
inline void HashTable<Key, Data>::Delete(const Key& key)
{
	size_t _key = this->convolution(key) % this->size;
	bool isFound = false;
	for (auto i = this->dataArray[_key].begin(); i != this->dataArray[_key].end(); i++)
	{
		if (i->key == key)
		{
			this->dataArray[_key].erase(i);
			isFound = true;
			break;
		}
	}
	if (!isFound)
	{
		throw "Find_Error";
	}
}

template<class Key, class Data>
inline Data HashTable<Key, Data>::operator[](const Key& key)
{
	return this->Find(key);
}

// HastTable end