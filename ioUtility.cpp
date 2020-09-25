#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;


class ioUtil {

    public:

        int getNumofArguments() {
            return numofArguments;
        }

        int getNumofIOPairs() {
            return ioPairs.size();
        }

        void setNumberofIO(int numofIO) {
            this->numofIO = numofIO;
        }

        void setIOfile(string IOfilename) {
            this->IOfilename = IOfilename;

            readIOfile();
        }

        void getUserIO() {

            string tempIO;

            for(int i = 0; i < numofIO; i++) {

                cin >> tempIO;
                strManu.trimString(tempIO);
                userIO.push_back(tempIO);
            }

            createIOMap();
        }

        vector<string> getUserIOVec() {
            return userIO;
        }

        map<string, string> getIOPairs() {
            return ioPairs;
        }


    private:
        
        int numofIO;
        int numofArguments;
        string IOfilename;

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

            countArguments();
        }

        void countArguments() {
            
            /*Able to add functionality to check if number of Argument correspond to inputs*/
            
            map<string, string>::const_iterator pt = ioPairs.begin();

            numofArguments = count(pt->first.begin(), pt->first.end(), ',') + 1;

        }

        void readIOfile() {

            string str;
            ifstream file(IOfilename);

            while(getline(file, str)) {

                strManu.trimString(str);
                userIO.push_back(str);

            }
            
            createIOMap();
        }
};
