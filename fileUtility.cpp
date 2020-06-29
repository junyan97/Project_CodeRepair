#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <boost/algorithm/string.hpp>

#include "ioUtility.cpp"

using namespace std;

class parser {

    public:

        void tokenizedLine(string line) {

            string token = "";
            string cleanedLine = line;

            boost::trim_right(cleanedLine);
            boost::trim_left(cleanedLine);

            for(char *tok = strtok(const_cast<char*>(cleanedLine.c_str()), " ;"); tok != NULL; tok = strtok(NULL, " ;")) {

                tokens.push_back(tok);
            }

        }
        
        vector<string> getFunNames() {

            findFunNames();

            return funName;
        }

    private:

        vector<string> tokens;
        vector<string> funName;

        void findFunNames() {

            for(int i = 0; i < tokens.size(); i++) {

                if(tokens[i] == "int" && i < tokens.size()) {
                    if(tokens[i + 1].find("(")) {
                        funName.push_back(tokens[i + 1].substr(0, tokens[i + 1].find("(")));
                    }
                }
            }

        }
};

class fileUtil {

    public:

        fileUtil(string path, string ioString) {
            this->path = path;
            this->ioString = ioString;
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
        string ioString;

        bool openFile() {
            string line;
            ifstream readFile(path);
            parser simpleParser;

            //check to see if file opens.
            if(!readFile) {
                cerr << "Error, opening file. " << endl;
                exit(EXIT_FAILURE);
            }
            if(!endsWith(path, ".c")) {
                cerr << "Incorrect files type " << endl;
                exit(EXIT_FAILURE);
            }

            while(getline(readFile, line)) {
                simpleParser.tokenizedLine(line);
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

        string generateAsserts(string funName, int input, int expected) {
            return "assert(" + funName + "(" + to_string(input) + ")" + "==" + to_string(expected) + ")";
        }

        void generateTest() {
            
            string line;
            string semicolon = ";";
            string endofLine = "\n";
            ifstream input_prog (path);
            ofstream test_prog ("test_prog.c");

            ioUtil io(ioString);
            parser simpleParser;

            vector<string> listofFunc = simpleParser.getFunNames();

            if(input_prog.is_open()) {

                while(getline(input_prog, line)) {
                    test_prog << line << endofLine;
                }
                input_prog.close();

                test_prog << "int main(){ " << endofLine;
                
                for(int i = 0; i < listofFunc.size(); i++) {
                    test_prog << generateAsserts(listofFunc[i], io.getInput(), io.getOutput()) << semicolon << endofLine;
                }

                test_prog << "return 0" << semicolon <<endofLine;
                test_prog << "}" << endofLine;

                test_prog.close();
            }
            
        } 

};



