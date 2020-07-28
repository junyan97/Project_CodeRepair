#include <cmath>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

class ioUtil {


    public:

        ioUtil(/*string ioString*/) {
            /*this->ioString = ioString;
            strManu.trimString(ioString);
            extractIO();
            countInputs();*/
        }

        /*string getInput() {
            return this->input;
        }

        string getOutput() {
            return this->output;
        }

        int numberofInput() {
            return this->numofInput;
        }*/

        void getUserIO(int numofIO) {

            string tempIO;

            for(int i = 0; i < numofIO; i++) {

                cin >> tempIO;
                strManu.trimString(tempIO);
                userIO.push_back(tempIO);
            }

            createIOMap();
        }

        vector<string> getUserIO() {
            return userIO;
        }

        map<string, string> getIOPairs() {
            return ioPairs;
        }

        /*void printIO() {

            for(int i = 0; i < userIO.size(); i++) {
                
                cout << userIO[i] << endl;
            }
        }

        void printMap() {

            for(map<string, string>::const_iterator it = ioPairs.begin(); it != ioPairs.end(); it++) {
                
                cout << "input: " << it->first << " output: " << it->second << endl;
            }
        }*/

    private:
        
        /*int numofInput;
        string input;
        string output;
        string ioString;*/

        stringManupulation strManu;

        /*Store user Input*/
        vector<string>userIO;

        /*Store user input and output as a map*/
        map<string, string>ioPairs;

        void createIOMap() {

            string tempInput;
            string tempOutput;
            string ioString;

            for(int i = 0; i < userIO.size(); i++) {
                
                ioString = userIO[i];
                tempInput = strManu.subString(ioString, strManu.find_n_Occurance(ioString, '(', 2), ioString.find(')'));
                tempOutput = strManu.subString(ioString, ioString.find_last_of(',') + 1, ioString.find_last_of(')') - 1);
                
                ioPairs.insert(make_pair(tempInput, tempOutput));
            }
        }


        /*void extractIO() {

            input = strManu.subString(ioString, strManu.find_n_Occurance(ioString, '(', 2), ioString.find(')'));
            output = strManu.subString(ioString, ioString.find_last_of(',') + 1, ioString.find_last_of(')') - 1);

        }*/

        /*void countInputs() {

            numofInput = count(input.begin(), input.end(), ',') + 1;

        }*/


};