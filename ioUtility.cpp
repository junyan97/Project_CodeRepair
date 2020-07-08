#include <cmath>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

class ioUtil {


    public:

        ioUtil(string ioString) {
            this->ioString = ioString;
            strManu.trimString(ioString);
            extractIO();
            countInputs();
        }

        string getInput() {
            return this->input;
        }

        string getOutput() {
            return this->output;
        }

        int numberofInput() {
            return this->numofInput;
        }


    private:
        
        int numofInput;
        string input;
        string output;
        string ioString;

        stringManupulation strManu;

        void extractIO() {

            input = strManu.subString(ioString, strManu.find_n_Occurance(ioString, '(', 2), ioString.find(')'));
            output = strManu.subString(ioString, ioString.find_last_of(',') + 1, ioString.find_last_of(')') - 1);

        }

        void countInputs() {

            numofInput = count(input.begin(), input.end(), ',') + 1;

        }


};