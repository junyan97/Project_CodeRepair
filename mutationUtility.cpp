#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

class mutUtil {
    public:

        mutUtil(string path) {
            this->path = path;
            operations.push_back("+");
            operations.push_back("-");
            operations.push_back("*");
            operations.push_back("/");
            operations.push_back("%");
            operations.push_back(">");
            operations.push_back(">=");
            operations.push_back("<");
            operations.push_back("<=");
            operations.push_back("||");
            operations.push_back("&&");

            generateMutated();
        }
        
        

    private:
    
        string path;
        vector<string> operations;

        bool hasOperations (string line) {
            
            for(int i = 0; i < operations.size(); i++) {
                if(contains(line, operations[i])) {
                    return true;
                }
            }
            return false;
        }

        string arithmetricOp (string line) {

            if(contains(line, "+") || contains(line, "-")) {
                return contains(line, "+") 
                ? replace_all_copy(line, "+", "-") 
                : replace_all_copy(line, "-", "+");
            }else{
                return contains(line, "*")
                ? replace_all_copy(line, "*", "/")
                    : (contains(line, "/")
                ? replace_all_copy(line, "/", "%")
                    :replace_all_copy(line, "%", "*"));
            }
        }

        string relationalOp (string line) {

            return contains(line, ">=") 
            ? replace_all_copy(line, ">=", ">") 
                : (contains(line, "<=")
            ? replace_all_copy(line, "<=", "<")
                : (contains(line, ">") 
            ? replace_all_copy(line, ">", ">=")
                : replace_all_copy(line, "<", "<=")));
        }
           
        string logicOp (string line) {

            return contains(line, "||") 
            ? replace_all_copy(line, "||", "&&")
            : replace_all_copy(line, "&&", "||");
        }

        string mutatedLine (string line) {

            if(contains(line, "+") || contains(line, "-") || contains(line, "*")
             || contains(line, "/") || contains(line, "%")) {
                 return arithmetricOp(line);
             }
             else if(contains(line, "<") || contains(line, "<=") || contains(line, ">") 
             || contains(line, ">=")) {
                 return relationalOp(line);
             }else{
                 return logicOp(line);
             }
        }
        
        void generateMutated() {
            string line;
            string endofLine = "\n";
            ifstream readFile(path);
            ofstream mut_prog("mutated_prog.c");

            if(readFile) {
                while(getline(readFile, line)) {
                    if(hasOperations(line)) {
                        mut_prog << mutatedLine(line) << endofLine;
                    }else{
                        mut_prog << line << endofLine;
                    }
                }
            }
        }
};