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
            cleanString();
        }

        string getInput() {
            return this->input;
        }

        string getOutput() {
            return this->output;
        }


    private:
        
        string input;
        string output;
        string ioString;

        int find_n_Occurance(string input, char character, int n) {

            int cnt = 0;

            for(int i = 0; i < input.length(); i++) {
                if(input[i] == character) {
                    cnt++;
                }
                if(cnt == n) {
                    return i;
                }
            }
            return 0;
        }

        string subString(string str, int pos1, int pos2) {

            int len_To_Copy = abs(pos2 - pos1) + 1;

            return str.substr(pos1, len_To_Copy);
        }

        void cleanString() {
        
            trim_left(ioString);
            trim_right(ioString);

            input = subString(ioString, find_n_Occurance(ioString, '(', 2), ioString.find(')'));
            output = subString(ioString, ioString.find_last_of(',') + 1, ioString.find_last_of(')') - 1);

            
        }


};