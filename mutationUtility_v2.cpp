#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

class mutUtil {

    public:

        mutUtil(vector<string> prog, ioUtil io) {
            this->prog = prog;
            this->io = io;
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

        void mutate() {

        }

        vector<class mutatedProg>getListofMutatedProg() {

            return listofMutatedProg;

        }

    private:

        ioUtil io;

        vector<string>prog;
        vector<string>operations;

        vector<class mutatedProg> listofMutatedProg;

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

        string mutation (string line) {
 
            if (contains(line, "+") || contains(line, "-") || contains(line, "*")
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

        void copyPreviousLine(int lineNumber, vector<string> *toCopyTo) {

            /*Protect against linenumber = 0*/

            for(int i = 0; i < lineNumber - 1; i++) {

                toCopyTo->push_back(prog[i]);
            }

        }

        void copyRemainingLine(int lineNumber, vector<string> *toCopyTo) {

            for(int i = lineNumber + 1; i < prog.size(); i++) {

                toCopyTo->push_back(prog[i]);
            }

        }

        void generateMutatedProg() {

            for(int i = 0; i < prog.size(); i++) {

                if(hasOperations(prog[i])) {

                    vector<string>temp;
                    
                    copyPreviousLine(i, &temp);
                    temp.push_back(mutation(prog[i]));
                    copyRemainingLine(i, &temp);

                    mutatedProg temp1(temp);
                    temp1.setIO(io);

                    listofMutatedProg.push_back(temp1);

                }
            }
        }
}; 