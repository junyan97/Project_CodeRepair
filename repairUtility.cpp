#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class repairUtil {

    public:

        repairUtil(string path, string ioString) {
            this->path = path;
            this->ioString = ioString;
        }

        bool requireRepair() {
            if(doesCompile() && doesExecute()) {
                return false;
            }else{
                return true;
            }
        }


    private:

        string path;
        string ioString;

        bool doesCompile() {
            string compileCommandStr;

            compileCommandStr = "gcc " + path + " -o temp" ;

            cout << "Compiling file" << endl;
            if(system(compileCommandStr.c_str()) == 0) {
                return true;
            }else{
                cerr << "File cannot be compiled" << endl;
                exit(EXIT_FAILURE);
            }
        }

        bool doesExecute() {

            cout << "executinng program" << endl;
            if(system("./temp") == 0) {
                return true;
            }else{
                return false;
            }
        }
       

};