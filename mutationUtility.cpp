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
        }
        
        bool hasOperations (string line) {
            
            for(int i = 0; i < operations.size(); i++) {
                if(contains(line, operations[i])) {
                    return true;
                }
            }
            return false;
        }

    private:
    
        string path;
        vector<string> operations;

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

        
        

    
};