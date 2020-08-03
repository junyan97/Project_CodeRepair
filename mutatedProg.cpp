#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


class mutatedProg {

    public:
        mutatedProg(string path) {
            this->progPath = path;
            progFunction = fp.copyFiletoVector(progPath);
            getFunName();
            getFunction();
        }

        void setIO(ioUtil io) {
            this->io = io;
        }

        int getFitness() {
            return fitness;
        }


    private:
        int fitness;
        string progPath;
        string functionName;
        vector<string> progMain;
        vector<string> progFunction;


        ioUtil io;
        fileOperation fp;
        parser simpleparser;
        stringManupulation strOperation;

        void getFunName() {

            for(int i = 0; i < progFunction.size(); i++) {

                simpleparser.tokenizedLine(progFunction[i]);

            }

        }

        void getFunction() {

            functionName = simpleparser.getProgFunc().begin()->first;
        }

        void createMain(string input, string output) {

            string semicolon = ";";
            string endofLine = "\n";

            progMain.clear();
            progMain.push_back("int main(){" + endofLine);
            progMain.push_back(strOperation.generateAsserts(functionName, input, output) + semicolon + endofLine);
            progMain.push_back("return 0" + semicolon + endofLine);
            progMain.push_back("}" + endofLine);

        }

        void createTest() {

            
            

        }  

        void progFitness() {

            for(map<string, string>::const_iterator it = io.getIOPairs().begin();
            it != io.getIOPairs().end(); it++) {

            }

        }



};