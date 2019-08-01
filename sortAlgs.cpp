//sortAlgs.cpp
// by Kingsley Bowen
// 11/06/2016
// Purpose: implementation of three sorting algorithms: insertion sort, 
// merge sort, and radix sort.

#include "sortAlgs.h"
#include <fstream>

void swap(vector<int> *nums, int a, int b);
void parseFile(vector<int> *nums, string file);
void copyStringsFrom(vector<int> *nums, istream &input);
void print(vector<int> nums);
void merge(vector<int> *nums, int start, int mid, int end);
void mergeSortHelper(vector<int> *nums, int start, int end);
int getDigit(int num, int digit);
void appendBuckets(vector<int> *nums, vector<int> buckets[]);
void chooseBuckets(vector<int> *nums, vector<int> buckets[], int digit);
int getMaxInputLength(vector<int> *nums);
int getLength(int num);
void insert(vector<int> *nums, int num, int index);

// Parameter: vector for storage
// Effect: creates a sorted vector full of integers
void sortAlgs::insertionSort(vector<int> *nums){
    int size = nums->size();
    for (int i = 0; i < size; i++){
        int min = (*nums)[i]; 
        int minIndex = i;
        for (int j = i; j < size; j++){
            if ((*nums)[j] < min){
                min = (*nums)[j];
                minIndex = j;
            }
        }
        swap(nums, minIndex, i);
    }
}

// Parameter: vector for storage
// Effect: returns if base case and calls recursive mergeSortHelper
void sortAlgs::mergeSort(vector<int> *nums){
    if (nums->size() < 2) return;
    mergeSortHelper(nums, 0, nums->size());
}

// Parameter: vector for storage
// Effect: Main loop for choosing and appending buckets
void sortAlgs::radixSort(vector<int> *nums){
    vector<int> buckets[BASE];
    int digit = 1;
    int maxInputLength = getMaxInputLength(nums);
    for (int i = 0; i < maxInputLength; i++){
        chooseBuckets(nums, buckets, digit);
        appendBuckets(nums, buckets);
        digit++;
    }
    
}

// Parameter: vector for storage, two integer values to swap
// Effect: swaps two values in vector
void swap(vector<int> *nums, int a, int b){
    int temp = (*nums)[b];
    (*nums)[b] = (*nums)[a];
    (*nums)[a] = temp;
}

// Parameter: vector for storage, index of start and end of vector
// Effect: recursively splits up data into smaller vectors then calls merge
void mergeSortHelper(vector<int> *nums, int start, int end){
    //base case
    if (start == end-1) return;

    else{
        //split 
        int mid = (start+end)/2;

        //sort left half
        mergeSortHelper(nums, start, mid);

        //sort right half
        mergeSortHelper(nums, mid, end);

        //merge
        merge(nums, start, mid, end);
    }
}

// Parameter: vector for storage, index of start, middle, and end of vector
// Effect: combines smaller vectors 
void merge(vector<int> *nums, int start, int mid, int end){
    vector<int> merged;
    int indexA = start;
    int indexB = mid;
    for (int i = start; i < end; i++){
        if (indexA == mid){         //no remaining elements in left half
            merged.push_back((*nums)[indexB]);
            indexB++;
        }
        else if (indexB == end){    //no remaining elements in right half
            merged.push_back((*nums)[indexA]);
            indexA++;
        }
        else{
            if ((*nums)[indexA] < (*nums)[indexB]){ //left number lower
                merged.push_back((*nums)[indexA]);
                indexA++;
            }
            else {                                  //right number lower
                merged.push_back((*nums)[indexB]);
                indexB++;
            }
        }
    }
    //put merged elements back in nums vector
    int mergedSize = merged.size();
    for (int i = 0; i < mergedSize; i++){
        (*nums)[i+start] = merged[i];
    }
}

void print(vector<int> nums){
    int size = nums.size();
    for(int i=0; i<size; i++){
        cerr << nums[i] << " ";
    }
    cerr << endl;
}

// Parameters: original number and what is the least significant digit
// Returns the integer digit of the original in the least significant spot
int getDigit(int num, int digit){ 
    int place = pow(10, digit-1);
    return (num/place)%10;
}

// Parameter: vector for numbers, array for buckets
// Effect: Filling back nums vector in order they appear in bucket
void appendBuckets(vector<int> *nums, vector<int> buckets[]){
    nums->clear();
    for (int i = 0; i < BASE; i++){ // loops through array of buckets
        int size = buckets[i].size();
        for (int j = 0; j < size; j++){ // loops through bucket[i];
            nums->push_back(buckets[i][j]);
        }
        buckets[i].clear();
    }
}

// Parameter: vector for storage of intgers, array of buckets, least 
// significant digit
// Effect: From the least significant digit determine which bucket to place
// integer in in nums vector.
void chooseBuckets(vector<int> *nums, vector<int> buckets[],
                            int digit){
    int size = nums->size();
    for (int i = 0; i < size; i++){
        int bucket = getDigit((*nums)[i], digit);
        buckets[bucket].push_back((*nums)[i]);
    }
}

// returns the integer digit length of the greatest input number
int getMaxInputLength(vector<int> *nums){
    int size = nums->size();
    int maxLength = getLength((*nums)[0]);

    for (int i = 0; i < size; i++){
        if (maxLength < getLength((*nums)[i])){
            maxLength = getLength((*nums)[i]); 
        }
    }
    return maxLength;
}

// Returns the integer count of number of digits in max input length
int getLength(int num){
    int length = 0;
    while (num>0){
        num = num/10;
        length++;
    }
    return length;
}


void sortAlgs::realInsertionSort(vector<int> *nums){
    for (int i = 0; i < nums->size(); i++){
        for (int j = 0; j < i; j++){
            if (nums[i] < nums[j]){
                insert(nums[i], j);
                break;
            }
        }
    }
}

void insert(vector<int> *nums, int num, int index){
    nums->push_back(nums[nums->size()]);
    for (int i = size-2; i > index; i--){
        nums[i] = nums[i-1];
    }
    nums[index] = num;
}


