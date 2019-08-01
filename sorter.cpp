// sorter.cpp
// by Kingsley Bowen
// 11/06/2016
// Purpose: Implementation of the the interface. Also runs the main work
// loop, and creates a new file that saves data output when needed. Has two
// functional modes: interactive and taking in a file.   

#include <iostream>
#include <fstream>
#include <vector>
#include "sortAlgs.h"

using namespace std;
bool inputCheck(int numArgs, string alg, string mode);
void interactiveParse(vector<int> *numbers);
void parseFile(vector<int> *numbers, string file);
void copyIntsFrom(vector<int> *numbers, istream &input);
void sort(vector<int> *numbers, string alg);
void printOutput(vector<int> numbers);
void saveOutput(vector<int> numbers, string listOrigin, string alg);


int main(int argc, char *argv[]){
    string alg = argv[1];
    string mode = argv[2];

    // error message if program incorrectly used
    if(!inputCheck(argc, alg, mode)){
        cerr << "Usage:  sorter sortAlg outputMode [fileName]" << endl
             << "            where:  sortAlg is -s1, -s2, or -s3" << endl
             << "            and     outputMode is --print or --save" << endl;
        return 1;
    }

    vector<int> *numbers = new vector<int>;

    // interface
    if(argc == 3) interactiveParse(numbers);
    else parseFile(numbers, argv[3]); 

    sort(numbers, alg);

    // either save or print sorted data
    if(mode == "--print") printOutput(*numbers);
    else{
        if(argc == 3){
            saveOutput(*numbers, "cin", alg);
        }
        else{
            saveOutput(*numbers, argv[3], alg);
        }
    } 

    delete numbers;
    return 0;
}
// Parameters: pointer to a vector for storage and which algorithm to use
// Effect: determines which sorting algorithm to use
void sort(vector<int> *numbers, string alg){
    sortAlgs sorts;
    if(alg == "-s1") sorts.insertionSort(numbers);
    else if (alg == "-s2") sorts.mergeSort(numbers);
    else sorts.radixSort(numbers);
}

// Parameters: number of arguments, which algorithm to check, 
// which mode to check
// Returns true if the input is in the correct format in command line and 
// false otherwise. 
bool inputCheck(int numArgs, string alg, string mode){
    if(!(numArgs == 3 or numArgs == 4)){
        return false;
    }

    if(!(alg == "-s1" or alg == "-s2" or alg == "-s3")){
        return false;
    }

    if(!(mode == "--save" or mode == "--print")){
        return false;
    }

    return true;
}

// Parameters: pointer to a vector for storage
// Effect: takes in numbers given from client and stores them in a vector
void interactiveParse(vector<int> *numbers){
    int num;

    cin >> num;
    while(!cin.eof()){
        numbers->push_back(num);
        cin >> num;
    }
}

// Parameter: pointer to a vector for storage, name of file
// Effect: opens the file, and if not successful prints error message. 
void parseFile(vector<int> *numbers, string file){
    ifstream input;

    input.open(file);
    if(not input.is_open()){
        cerr << "Unable to open " << file << endl;
    }

    copyIntsFrom(numbers,input);
}

// Parameter: pointer to a vector for storage, address of istream
// Effect: copies the ints from the file and puts them into a vector. 
void copyIntsFrom(vector<int> *numbers, istream &input){
    int num;
    for(input >> num; not input.eof(); input >> num){
        numbers->push_back(num);
    }
}

// Parameter: vector for storage
// Effect: Prints output
void printOutput(vector<int> numbers){
    int size = numbers.size();
    for(int i=0; i<size; i++){
        cout << numbers[i] << endl;
    }
}

// Parameter: vector for storage, name of listOrigin, name of which algorithm
// Effect: creates a text file and saves the sorted output in the text file
void saveOutput(vector<int> numbers, string listOrigin, string alg){
    string fileName = "";

    fileName = fileName + listOrigin + "_";

    if(alg == "-s1") fileName = fileName + "1_";
    else if (alg == "-s2") fileName = fileName + "2_";
    else fileName = fileName + "3_";

    fileName = fileName + to_string(numbers.size()) + "_";

    fileName = fileName + "sorted.txt";

    ofstream myFile;
    myFile.open(fileName);

    int size = numbers.size();
    for(int i=0; i<size; i++){
        myFile << numbers[i] << endl;
    }

    myFile.close();
}