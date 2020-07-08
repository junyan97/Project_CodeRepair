#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class repairUtil {

    public:

        repairUtil(string path) {
            this->path = path;
        }

        bool requireRepair() {
            if(doesCompile() && doesExecute()) {
                return false;
            }else{
                return true;
            }
        }

        void setFilename(string path) {
            this->path = path;
        }


    private:

        string path;

        errorUtil err;
        response res;
      
        bool doesCompile() {
            string compileCommandStr;

            compileCommandStr = "gcc " + path + " -o temp" ;

            res.message("Compiling file");
            
            if(system(compileCommandStr.c_str()) == 0) {
                return true;
            }else{
                err.fileCannotbeCompiled();
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