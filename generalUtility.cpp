#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class errorUtil{

    public:

        void errorOpening() {

            cerr << "Error, opening file. " << endl;
            exit(EXIT_FAILURE);

        }

        void incorrectFile() {

            cerr << "Incorrect files type " << endl;
            exit(EXIT_FAILURE);

        }

        void incorrectInput(string funName) {

            cerr << "Incorrect number of input for function " << funName << endl;
            exit(EXIT_FAILURE);

        }

        void opCancelled() {

            cerr << "operation cancelled" << endl;
            exit(EXIT_FAILURE);

        }

        void resNotRecog() {

            cerr << "response not recognized" << endl;
            exit(EXIT_FAILURE);

        }

};

class userPrompt{

    public:

        void reqFilePath() {

            cout << "Please enter exact path of program to be repaired: ";

        }

        void filePathConfimation() {

            cout << "Is the following the file to be inspected" << endl;

        }

        void userConfirmation() {

            cout << "Type yes to proceed and no to cancel the operation: ";

        }

        void reqProgIO() {

            cout << "Please enter input/output example in the form ((input),output): ";

        }


};

class response{

    public:

        void dashedLine() {

            cout << "-----------------------------------" << endl;
            cout << endl;
            
        }
        void newLine() {

            cout << endl;

        }

        void noRepairRequired() {

            cout << "Program do not require repair" << endl;

        }

        void repairRequired() {

            cout << "Program require repair" << endl;

        }

        void generatingFile(){

            cout << "generating test file " << endl;
        }

};
