#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>

using namespace std;

class fileUtil {

    public:

        fileUtil(string path) {
            this->path = path;
            generateTest();
        }

        bool correctFormat() {
            if(openFile()) {
                return true;
            }else {
                return false;
            }
        }

    private:

        string path;

        bool openFile() {
            string myText;
            fstream readFile(path);

            //check to see if file opens.
            if(!readFile) {
                cerr << "Error, opening file. " << endl;
                exit(EXIT_FAILURE);
            }
            if(!endsWith(path, ".c")) {
                cerr << "Incorrect files type " << endl;
                exit(EXIT_FAILURE);
            }

            readFile.close();

            return true;
        }

        bool endsWith(string mainStr, string toMatch) {
            if(mainStr.size() >= toMatch.size() &&
                    mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
                    return true;
                else
                    return false;
        }

        void generateTest() {
            
            string line;
            string endofLine = "\n";
            ifstream input_prog (path);
            ofstream test_prog ("test_prog.c");


            if(input_prog.is_open()) {

                while(getline(input_prog, line)) {
                    test_prog << line << endofLine;
                }
                input_prog.close();

                test_prog << "int main(){ " << endofLine;
                

                test_prog.close();
            }

            
        } 


};