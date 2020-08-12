#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


class mutatedProg {

    public:
        mutatedProg(vector<string> prog) {
            this->progFunction = prog;
        }
        void setIO(ioUtil io) {
            this->io = io;
            execute();
        }

        vector<string> getMutatedProg() {
            return progFunction;
        }

        int getFitness() {
            return fitness;
        }


    private:
        int fitness;
        string functionName;
        vector<string> progMain;
        vector<string> progFunction;
        vector<string> testProg;


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

            /*cout << "Created Main" << endl;

            for(int i = 0; i < progMain.size(); i++) {
                cout << progMain[i] << endl;
            }*/

        }

        void createTestProg() {

            testProg.clear();

            //Copying function vector
            for(int i = 0; i < progFunction.size(); i++) {
                testProg.push_back(progFunction[i]);
            }

            //copying mainFuction vector
            for(int i = 0; i < progMain.size(); i++) {
                testProg.push_back(progMain[i]);
            }

            /*cout << "Created testProg " << endl;

            for(int i = 0; i < testProg.size(); i++) {
                cout << testProg[i] << endl;
            }*/

        }

        bool executeProg() {

            repairUtil rp(testProg);

            if(!rp.requireRepair()) {
                return true;
            }

            return false;
            
        }  

        void progFitness() {

            fitness = 0;
            map<string, string>ioPairs = io.getIOPairs();

            for(map<string, string>::const_iterator it = ioPairs.begin();
            it != ioPairs.end(); it++) {

                createMain(it->first, it->second);
                createTestProg();

                if(executeProg()) {
                    fitness++;
                }
            }
        }

         void execute() {
            getFunName();
            getFunction();
            progFitness();
        }



};