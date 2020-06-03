#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <vector>
#include <functional>

template<class Key, class Data>
class Record {
public:
	Key key;
	Data data;

	Record(Key _key, Data _data) : key(_key), data(_data) {};

	bool operator ==(const Key&);
	bool operator !=(const Key&);
};

template<class Key, class Data>
class Table {
protected:
	int size;
	int count;
	Record<Key, Data>* dataArray;

public:
	Table(int _size) : size(_size), count(0), dataArray(new Record<Key, Data>[size]) {};

	void Add(Key, Data);
	Data Find(Key);
};


template<class Key, class Data>
class SortTable : public Table<Key, Data >
{
public:
	SortTable(size_t);
	SortTable(const SortTable<Key, Data>&);
	SortTable(const Table<Key, Data>& );

	void Add(Key, Data);
	Data Find(Key);
	void Delete(const Key&);
	Data& operator[](const Key&);
};


template<class Key, class Data>
class HashTable
{
private:
	using HashFunc = std::function<size_t(Key)>;
	int size;
	int count;
	HashFunc convolution;
	std::list<Record<Key, Data>>* dataArray;
public:
	HashTable(int _size = 5);
	HashTable(HashFunc  hFunc, int _size = 5) :size(_size), convolution(hFunc) {}
	void Add(Key key, Data data);
	Data Find(Key key);
	virtual void Delete(const Key& key);
	virtual Data operator[](const Key& key);
};


#endif // TABLE_H