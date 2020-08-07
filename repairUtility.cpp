#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>

/*#include "generalUtility.cpp"
#include "parser.cpp"
#include "ioUtility.cpp"*/

using namespace std;

class repairUtil {

    response res;
    errorUtil err;
    parser simpleParser;
    fileOperation fOperation;
    stringManupulation strOperation;

    public:

        repairUtil(vector<string> prog) {
            
            this->prog = prog;

        }

        void setIO(ioUtil io) {

            this->io = io;

        }

        void previewFile() {
            
            fOperation.previewFile(prog);
        }

        void initialliseInitialProg() {
            
            getProgFunction(prog);
            initialProg = fOperation.copyVector(prog);
            testInitialProg();
            fOperation.copyVectortoFile("testFile.c", initialProg);

        }

        bool initialProgRepair() {

            initialliseInitialProg();

            if(doesCompile() && doesExecute()) {
                
                system("rm temp");
                system("rm testFile.c");
                return true;
            }else{
                return false;
            }
        }

        bool requireRepair() {

            getProgFunction(prog);
            fOperation.copyVectortoFile("testFile.c", prog);

            if(doesCompile() && doesExecute()) {

                system("rm temp");
                system("rm testFile.c");
                return true;
            }else{
                return false;
            }
        }

    private:

        ioUtil io;
        vector<string> prog;  
        vector<string> initialProg;

        void getProgFunction(vector<string> prog) {

            for(int i = 0; i < prog.size(); i++) {

                simpleParser.tokenizedLine(prog[i]);

            }
        }

        void testInitialProg() {

            int numofArguments;
            int numofIOPairs;
            string semicolon = ";";
            string endofLine = "\n";
        
            map<string, string> ioPairs;

            numofIOPairs = io.getNumofIOPairs();
            numofArguments = io.getNumofArguments();
            ioPairs = io.getIOPairs();

            res.message("generating inital test file");

            map<string, int> functionMap = simpleParser.getProgFunc();

            initialProg.push_back("int main(){" + endofLine);

                for(map<string, int>::const_iterator it = functionMap.begin();
                it != functionMap.end(); it++) {
                    
                    if(it->second != numofArguments) {
                        err.incorrectInput(it->first);
                    }else{

                        for(map<string, string>::const_iterator it1 = ioPairs.begin();
                        it1 != ioPairs.end(); it1++) {
                            initialProg.push_back(strOperation.generateAsserts(it->first, it1->first, it1->second) + semicolon + endofLine);
                        }
                        
                    }
                }   

            initialProg.push_back("return 0" + semicolon + endofLine);
            initialProg.push_back("}" + endofLine);

        }

        bool doesCompile() {

            string filename;
            string compileCommandStr;

            filename = "testFile.c";

            compileCommandStr = "gcc " + filename + " -o temp" ;

            res.message("Compiling file");
            
            if(system(compileCommandStr.c_str()) == 0) {
                return true;
            }else{
                return false;
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