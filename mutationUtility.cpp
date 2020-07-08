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

        void repair() {

            int mut_cnt = 0;
            string mutated_filename = "mutated_prog_";

            repairUtil prog("");
            
            do {
                if(mut_cnt == 0) {
                    generateMutated(path, mutated_filename + to_string(mut_cnt));
                }else{
                    generateMutated(mutated_filename + to_string(mut_cnt - 1) + ".c", mutated_filename + to_string(mut_cnt));
                } 
                prog.setFilename(mutated_filename + to_string(mut_cnt) + ".c");
                mut_cnt++;

            } while (prog.requireRepair() && mut_cnt < 3);

            if(mut_cnt < 2) {
                res.newLine();
                res.dashedLine();
                res.message("Program repaired");
            }else{
                res.newLine();
                res.dashedLine();
                res.message("No suitable repair found");
            }
            
            for(int i = 0; i < mut_cnt - 1; i++) {
                string to_Be_Deleted = "rm " + mutated_filename + to_string(i) + ".c";
                system(to_Be_Deleted.c_str());
            }
            
        }        
        

    private:
    
        string path;
        vector<string> operations;

        response res;

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

             if(contains(line, "include")) {
                return line;
             }    
            else if(contains(line, "+") || contains(line, "-") || contains(line, "*")
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
        
        void generateMutated(string file_to_mutate, string mutated_filename) {
            string line;
            string endofLine = "\n";
            ifstream readFile(file_to_mutate);
            ofstream mut_prog(mutated_filename + ".c");

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