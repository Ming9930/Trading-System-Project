/*
* depthofheap.cpp
*
* author: Ming Fu
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	// input unsorted array
	int n;
	cout << "Please enter the size of heap: ";
	cin >> n;
	
	if (n < 1) cout << "invalid heap size\n";
	else cout << "depth of the heap: " << int(log2(n)) + 1;

	return 0;
}