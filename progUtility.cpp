#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>

using namespace std;

class progUtil {

    response res;
    errorUtil err;
    parser simpleParser;
    fileOperation fOperation;
    
    public:

        progUtil(string path) {
            this->path = path;
        }

        void setIO(ioUtil io) {
            this->io = io;
        }

        bool correctFormat() {
            if(openFile()) {
                return true;
            }else {
                return false;
            }
        }

        void previewFile() {
            
            fOperation.previewFile(path);
        }


    private:

        string path;
        ioUtil io;

        bool openFile() {
            string line;
            ifstream readFile(path);
            
            //check to see if file opens.
            fOperation.openFile(readFile);

            //check file extension.
            fOperation.checkExtension(path, ".c");

            while(getline(readFile, line)) {
                simpleParser.tokenizedLine(line);
            }

            readFile.close();
            testInitialProg();

            return true;
        }

        string generateAsserts(string funName, string input, string expected) {
            return "assert(" + funName + input + "==" + expected + ")";
        }

        void copyFile(ifstream &input, ofstream &output) {

            string line;
            string endofLine = "\n";

            if(input.is_open()) {

                while(getline(input, line)) {
                    output << line << endofLine;
                }
            }

            input.close();
            
        }

        void testInitialProg() {

            int numofArguments;
            int numofIOPairs;
            string semicolon = ";";
            string endofLine = "\n";
            ifstream input_prog(path);
            ofstream test_prog("test_prog.c");
            map<string, string> ioPairs;

            copyFile(input_prog, test_prog);
            numofIOPairs = io.getNumofIOPairs();
            numofArguments = io.getNumofArguments();
            ioPairs = io.getIOPairs();

            res.message("generating inital test file");

            map<string, int> functionMap = simpleParser.getProgFunc();

            test_prog << "int main(){ " << endofLine;

                for(map<string, int>::const_iterator it = functionMap.begin();
                it != functionMap.end(); it++) {
                    
                    if(it->second != numofArguments) {
                        err.incorrectInput(it->first);
                    }else{
                        /*test_prog << generateAsserts(it->first, io.getInput(), io.getOutput()) << semicolon << endofLine;*/
                        for(map<string, string>::const_iterator it1 = ioPairs.begin();
                        it1 != ioPairs.end(); it1++) {
                            test_prog << generateAsserts(it->first, it1->first, it1->second) << semicolon << endofLine;
                        }
                        
                    }
                }   

            test_prog << "return 0" << semicolon <<endofLine;
            test_prog << "}" << endofLine;

            test_prog.close();
        }

};



