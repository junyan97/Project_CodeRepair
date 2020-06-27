#include <string>
#include <iostream>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>

#include "ioUtility.cpp"

using namespace std;

int main() {

    ioUtil test("(1 ,3)");

    cout << test.getInput() << endl;
    cout << test.getOutput() << endl;
   
}