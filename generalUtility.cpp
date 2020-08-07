#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>

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

        void fileCannotbeCompiled() {

            cerr << "File cannot be compiled" << endl;
            system("rm temp");
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

        void reqNumberofIO() {

            cout << "Please enter the number of Input/Output Pairs to be provided: ";
            
        }

        void reqProgIO() {

            cout << "Please enter input/output example in the form ((input),output): " << endl;

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

        void message(string msg) {

            cout << msg << endl;
        }

};

class stringManupulation{

    public:

        bool endsWith(string mainStr, string toMatch) {
            if(mainStr.size() >= toMatch.size() &&
                    mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0) {
                        return true;
                    }else{
                        return false;
                    }              
        }

        void trimString(string &str) {

            boost::trim_left(str);
            boost::trim_right(str);

        }

        int find_n_Occurance(string input, char character, int n) {

            int cnt = 0;

            for(int i = 0; i < input.length(); i++) {
                if(input[i] == character) {
                    cnt++;
                }
                if(cnt == n) {
                    return i;
                }
            }
            return 0;
        }

        string subString(string str, int pos1, int pos2) {

            int len_To_Copy = abs(pos2 - pos1) + 1;

            return str.substr(pos1, len_To_Copy);
        }

        string generateAsserts(string funName, string input, string expected) {
            return "assert(" + funName + input + "==" + expected + ")";
        }

};

class fileOperation{

    public:

        errorUtil err;
        stringManupulation strManu;

        void openFile(ifstream &fp) {
            
            if(!fp) {
                err.errorOpening();
            }
        }

        void checkExtension(string path, string extension) {
            
            if(!strManu.endsWith(path, extension)) {
                err.errorOpening();
            }
        }

        void previewFile(vector<string> prog) {

            for(int i = 0; i < prog.size(); i++) {
                cout << prog[i] << endl;
            }
        }

        vector<string> copyFiletoVector(string path) {

            string line;
            ifstream readFile(path);
            vector<string>temp;

            openFile(readFile);
            checkExtension(path, ".c");

            while(getline(readFile, line)) {
                temp.push_back(line);
            }

            return temp;

        }

        bool copyVectortoFile(string path, vector<string> vecToCopy) {

            string endofLine = "\n";
            ofstream prog(path);

            if(prog) {
                for(int i = 0; i < vecToCopy.size(); i++) {
                    prog << vecToCopy[i] << endofLine;
                }

                prog.close();
                
                return true;
            }

            return false;
        }

        vector<string> copyVector(vector<string>origin) {

            vector<string>temp;

            for(int i = 0; i < origin.size(); i++) {

                temp.push_back(origin[i]);
            }

            return temp;
        }

};
