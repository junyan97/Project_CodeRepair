#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

class mutUtil {

    public:

        mutUtil(vector<string> prog) {
            this->prog = prog;
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

    private:

        vector<string>prog;
        vector<string>operations;

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