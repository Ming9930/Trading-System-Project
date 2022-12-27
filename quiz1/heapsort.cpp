/*
* heapsort.cpp
* 
* author: Ming Fu
*/

#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int>& arr, int n, int i)
{
	int largest = i; 
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	// left child larger than root
	if (l < n && arr[l] > arr[largest])
		largest = l;
	// right child larger than largest
	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i) {
		swap(arr[i], arr[largest]);
		// Recursively heapify
		heapify(arr, n, largest);
	}
}

void heapSort(vector<int>& arr, int n)
{
	// Build heap
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// sift element one by one
	for (int i = n - 1; i >= 0; i--) {
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}


int main()
{
	// input unsorted array
	int n;
	cout << "Please enter the size of array: ";
	cin >> n;
	cout << "Please enter the int array: ";
	vector<int> arr = {};
	int temp;
	for (int i = 0; i < n; ++i) {
		cin >> temp;
		arr.push_back(temp);
	}
		
	// heapify
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(arr, n, i);
	}

	// heapsort
	heapSort(arr, n);

	// output sorted array
	cout << "\nSorted array is: ";
	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	cout << "\n";

	return 0;
}