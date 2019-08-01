#include <iostream>
#include "sortAlgs.h"

using namespace std;


class sorter{
public:
    bool inputCheck(int numArgs, string alg, string mode);
    void interactiveParse();
    void parseFile(string file);
    void sort(string alg);
    void printOutput();
    void saveOutput(string listOrigin, string alg);
private:
    void copyIntsFrom(istream &inputStream);

    vector<int> numbers;
    sortAlgs sorts;
};