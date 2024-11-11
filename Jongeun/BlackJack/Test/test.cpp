#include <iostream>
#include <string_view>

//struct test
//{
//	int a{};
//	int b{};
//};


int main()
{
	//const test t1;
	//test& t2 = t1;

	int v2 = 3;
	const int& v = v2;

	const int v3 = 3;
	int& v4 = v3;

	
	return 0;
}