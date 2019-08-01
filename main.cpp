#include <iostream>
#include "sortAlgs.h"

int main(int argc, char* argv[]){
    sortAlgs sorter;
    string file = argv[1];
    sorter.run(file);
}
