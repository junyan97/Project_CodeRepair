#include <string>
#include <iostream>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>

using namespace std;

class ioUtil {

    public:

        ioUtil(string ioString) {
            this->ioString = ioString;
            cleanString();
        }

        int getInput() {
            return this->input;
        }

        int getOutput() {
            return this->output;
        }

    private:
        
        int input;
        int output;
        string ioString;

        void cleanString() {
        
            boost::trim_left(ioString);
            boost::trim_right(ioString);
   
            input = stoi(ioString.substr(ioString.find("(") + 1, ioString.find(",")));
            output = stoi(ioString.substr(ioString.find(",") + 1, ioString.find(")") - 1));
            
        }


};