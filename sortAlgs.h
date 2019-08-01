// sortAlgs.h
// by Kingsley Bowen
// 11/06/2016
// Purpose: implementation of three sorting algorithms: insertion sort, 
// merge sort, and radix sort.

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

const int BASE = 10; 

class sortAlgs{

public:
    void insertionSort(vector<int> *nums);
    void mergeSort(vector<int> *nums);
    void radixSort(vector<int> *nums);
    void realInsertionSort(vector<int> *nums);

};