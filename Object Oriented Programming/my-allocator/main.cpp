#include "MyAllocator.h"
#include "MyAllocator2.h"
#include <iostream>
#include <vector>
#include <Windows.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

class test
{
public:
	int a[10];
	char b[10];
};

int main()
{
	srand( (unsigned)NULL );
	int begin, end;
	vector<int, Allocator<test>> * vec1;
	vector<int, Allocator2<test>> * vec2;

	cout << "Constructor" << endl;
	begin = GetTickCount();
	for (int i = 0; i < 10000; ++i) {
		vec1 = new vector<int, Allocator<test>>(rand() % 1000);
		delete(vec1);
	}
	end = GetTickCount();
	cout << "Allocator with memory pool: " << end - begin << " ms" << endl;
	begin = GetTickCount();
	for (int i = 0; i < 10000; ++i) {
		vec2 = new vector<int, Allocator2<test>>(rand() % 1000);
		delete(vec2);
	}
	end = GetTickCount();
	cout << "Allocator without memory pool: " << end - begin << " ms" << endl;

	cout << "Resize" << endl;
	vec1 = new vector<int, Allocator<test>>;
	begin = GetTickCount();
	for (int i = 0; i < 100000; ++i) {
		vec1->resize(rand() % 1000);
	}
	end = GetTickCount();
	cout << "Allocator with memory pool: " << end - begin << " ms" << endl;
	vec2 = new vector<int, Allocator2<test>>;
	begin = GetTickCount();
	for (int i = 0; i < 100000; ++i) {
		vec2->resize(rand() % 1000);
	}
	end = GetTickCount();
	cout << "Allocator without memory pool: " << end - begin << " ms" << endl;

	return 0;
}