#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>

using namespace std;

class fileUtil {

    response res;
    errorUtil err;  
    parser simpleParser;
    
    public:

        fileUtil(string path) {
            this->path = path;
        }

        void setioString(string ioString) {
            this->ioString = ioString;
        }

        bool correctFormat() {
            if(openFile()) {
                return true;
            }else {
                return false;
            }
        }

        void previewFile() {
            string line;
            ifstream readFile(path);

            if(!readFile) {
                err.errorOpening();
            }

            if(readFile) {
                while(getline(readFile, line)) {
                    cout << line << endl;
                }
            }

            readFile.close();
        }


    private:

        string path;
        string ioString;

        bool openFile() {
            string line;
            ifstream readFile(path);
            
            //check to see if file opens.
            if(!readFile) {
                err.errorOpening();
            }
            if(!endsWith(path, ".c")) {
                err.incorrectFile();
            }

            while(getline(readFile, line)) {
                simpleParser.tokenizedLine(line);
            }

            readFile.close();
            generateTest();

            return true;
        }

        bool endsWith(string mainStr, string toMatch) {
            if(mainStr.size() >= toMatch.size() &&
                    mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
                    return true;
                else
                    return false;
        }

        string generateAsserts(string funName, string input, string expected) {
            return "assert(" + funName + input + "==" + expected + ")";
        }

        void generateTest() {
            
            int numofInput;
            string line;
            string semicolon = ";";
            string endofLine = "\n";
            ifstream input_prog (path);
            ofstream test_prog ("test_prog.c");

            ioUtil io(ioString);
            numofInput = io.numberofInput();

            res.generatingFile();

            map<string, int>functionMap = simpleParser.getProgFunc();

            if(input_prog.is_open()) {

                while(getline(input_prog, line)) {
                    test_prog << line << endofLine;
                }
                input_prog.close();

                test_prog << "int main(){ " << endofLine;

                for(map<string, int>::const_iterator it = functionMap.begin();
                it != functionMap.end(); it++) {
                    
                    if(it->second != numofInput) {
                        err.incorrectInput(it->first);
                    }else{
                        test_prog << generateAsserts(it->first, io.getInput(), io.getOutput()) << semicolon << endofLine;
                    }
                }   

                test_prog << "return 0" << semicolon <<endofLine;
                test_prog << "}" << endofLine;

                test_prog.close();
            }
            
        } 

};



