#include <iostream>
#include <typeinfo>
#include <string>
#include <stdio.h> 
#include <time.h>

#include <include/table.h>

using namespace std;

int main()
{
	HashTable<string, int> convtest(10);
	convtest.Add("One", 5);
	convtest.Add("Two", 6);
	cout << convtest.Find("Two") << endl;
	return 0;
}