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
            arithmetricOperations.push_back("+");
            arithmetricOperations.push_back("-");
            arithmetricOperations.push_back("*");
            arithmetricOperations.push_back("/");
            arithmetricOperations.push_back("%");
            relationalOperations.push_back(">");
            relationalOperations.push_back(">=");
            relationalOperations.push_back("<");
            relationalOperations.push_back("<=");
            logicOperations.push_back("||");
            logicOperations.push_back("&&");

            generateOperations();
            generateMutatedProg();
        }

        void mutate() {

        }

        void deleteMutated() {
            system("rm temp");
            system("rm testFile.c");
        }

        vector<class mutatedProg>getListofMutatedProg() {

            return listofMutatedProg;

        }

    private:

        ioUtil io;

        vector<string>prog;
        vector<string>operations;
        vector<string>logicOperations;
        vector<string>relationalOperations;
        vector<string>arithmetricOperations;
        
        vector<class mutatedProg> listofMutatedProg;

        void concatVectors(vector<string> toCopy, vector<string>* copyTo) {

            for(int i = 0; i < toCopy.size(); i++) {

                copyTo->push_back(toCopy[i]);

            }
        }

        void generateOperations() {

            concatVectors(logicOperations, &operations);
            concatVectors(relationalOperations, &operations);
            concatVectors(arithmetricOperations, &operations);

        }

        bool hasOperations (string line) {
            
            for(int i = 0; i < operations.size(); i++) {
                if(contains(line, operations[i])) {
                    if(!contains(line, "#include")) {
                        return true;
                    }            
                }
            }
            return false;
        }

        void removeElement (vector<string>& vecToRemoveFrom, string itemToBeRemoved) {

            vector<string>::iterator it = vecToRemoveFrom.begin();

            while (it != vecToRemoveFrom.end()) {

                    if(*it == itemToBeRemoved)
                        it = vecToRemoveFrom.erase(it);
                    else
                        it++;
            }
        }

        map<string, vector<string> > arithmetricOp (string line) {

            string removed;
            map<string, vector<string> >temp;
            vector<string> operationsRemoved;

            concatVectors(arithmetricOperations, &operationsRemoved);

            if(contains(line, "+")) {
                removed = "+";
                removeElement(operationsRemoved, "+");
            }
            else if(contains(line, "-")) {
                removed = "-";
                removeElement(operationsRemoved, "-");
            }
            else if(contains(line, "*")) {
                removed = "*";
                removeElement(operationsRemoved, "*");
            }
            else if(contains(line, "/")) {
                removed = "/";
                removeElement(operationsRemoved, "/");
            }else {
                removed = "%";
                removeElement(operationsRemoved, "%");
            }

            temp.insert(make_pair(removed, operationsRemoved));
            
            return temp;
        }

        map<string, vector<string> > relationalOp (string line) {

            string removed;
            map<string, vector<string> >temp;
            vector<string> operationsRemoved;

            concatVectors(relationalOperations, &operationsRemoved);

            if(contains(line, ">")) {
                removed = ">";
                removeElement(operationsRemoved, ">");
            }
            else if(contains(line, ">=")) {
                removed = ">=";
                removeElement(operationsRemoved, ">=");
            }
            else if(contains(line, "<")) {
                removed = "<";
                removeElement(operationsRemoved, "<");
            }else{
                removed = "<=";
                removeElement(operationsRemoved, "<=");
            }

            temp.insert(make_pair(removed, operationsRemoved));
            
            return temp;

        }

        map<string, vector<string> > logicOp (string line) {

            string removed;
            map<string, vector<string> >temp;
            vector<string> operationsRemoved;

            concatVectors(logicOperations, &operationsRemoved);

            if(contains(line, "||")) {
                removed = "||";
                removeElement(operationsRemoved, "||");
            }else{
                removed = "&&";
                removeElement(operationsRemoved, "&&");
            }

            temp.insert(make_pair(removed, operationsRemoved));
            
            return temp;
    
        }


        map<string, vector<string> > findOperation(string line) {

            map<string, vector<string> >temp;

            if (contains(line, "+") || contains(line, "-") || contains(line, "*")
             || contains(line, "/") || contains(line, "%")) {

                temp = arithmetricOp(line);

             }
             else if(contains(line, "<") || contains(line, "<=") || contains(line, ">") 
             || contains(line, ">=")) {

                 temp = relationalOp(line);

             }else{

                 temp = logicOp(line);
             }

             return temp;

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

        string replaceLine(string line, string toReplaced, string toBeReplaced) {

            return replace_all_copy(line, toReplaced, toBeReplaced);
        }

        void generateMutatedProg() {

            for(int i = 0; i < prog.size(); i++) {

                if(hasOperations(prog[i])) {
                    
                    string operationRemoved;
                    vector<string>operationsRemaining;
                    map<string, vector<string> > mapOfOperations;

                    mapOfOperations = findOperation(prog[i]);
                    operationRemoved = mapOfOperations.begin()->first;
                    operationsRemaining = mapOfOperations.begin()->second;

                    for(int j = 0; j < operationsRemaining.size(); j++) {

                        string currentLine;
                        vector<string>temp;

                        copyPreviousLine(i, &temp);
                        temp.push_back(replaceLine(prog[i], operationRemoved, operationsRemaining[j]));
                        copyRemainingLine(i, &temp);

                        mutatedProg mutated(temp);
                        mutated.setIO(io);

                        listofMutatedProg.push_back(mutated);


                    }

                }
            }

        }
}; 