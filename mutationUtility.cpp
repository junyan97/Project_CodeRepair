#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

class mutUtil
{

public:
    mutUtil(vector<string> prog, ioUtil io)
    {
        this->io = io;
        this->prog = prog;
        arithmetricOperations.push_back("+");
        arithmetricOperations.push_back("-");
        arithmetricOperations.push_back("*");
        arithmetricOperations.push_back("/");
        arithmetricOperations.push_back("%");
        relationalOperations.push_back(">");
        relationalOperations.push_back(">=");
        relationalOperations.push_back("<");
        relationalOperations.push_back("<=");
        relationalOperations.push_back("==");
        relationalOperations.push_back("!=");
        logicOperations.push_back("||");
        logicOperations.push_back("&&");

        generateOperations();
        generateMutatedProg();
    }

    void mutate()
    {
    }

    void deleteMutated()
    {
        system("rm temp");
        system("rm testFile.c");
    }

    vector<class mutatedProg> getListofMutatedProg()
    {

        return listofMutatedProg;
    }

private:
    ioUtil io;
    response res;

    vector<string> prog;
    vector<string> operations;
    vector<string> logicOperations;
    vector<string> relationalOperations;
    vector<string> arithmetricOperations;

    vector<class mutatedProg> listofMutatedProg;

    void concatVectors(vector<string> toCopy, vector<string> *copyTo)
    {

        for (int i = 0; i < toCopy.size(); i++)
        {

            copyTo->push_back(toCopy[i]);
        }
    }

    void generateOperations()
    {

        concatVectors(logicOperations, &operations);
        concatVectors(relationalOperations, &operations);
        concatVectors(arithmetricOperations, &operations);
    }

    bool hasOperations(string line)
    {

        for (int i = 0; i < operations.size(); i++)
        {
            if (contains(line, operations[i]))
            {
                if (!contains(line, "#include") && !contains(line, "for") && 
                !contains(line, "while") && !contains(line, "do") 
                && !contains(line, "if") && !contains(line, "else if") && !contains(line, "else"))
                {
                    return true;
                }
            }
        }
        return false;
    }

    void removeElement(vector<string> &vecToRemoveFrom, string itemToBeRemoved)
    {

        vector<string>::iterator it = vecToRemoveFrom.begin();

        while (it != vecToRemoveFrom.end())
        {

            if (*it == itemToBeRemoved)
                it = vecToRemoveFrom.erase(it);
            else
                it++;
        }
    }

    map<string, vector<string>> arithmetricOp(string line)
    {

        string removed;
        map<string, vector<string>> temp;
        vector<string> specialOperation;
        vector<string> operationsRemoved;

        concatVectors(arithmetricOperations, &operationsRemoved);

        if (contains(line, "++"))
        {
            removed = "++";
            specialOperation.push_back("--");
            temp.insert(make_pair(removed, specialOperation));
        }
        else if (contains(line, "--"))
        {
            removed = "--";
            specialOperation.push_back("++");
            temp.insert(make_pair(removed, specialOperation));
        }
        else if (contains(line, "+"))
        {
            removed = "+";
            removeElement(operationsRemoved, "+");
        }
        else if (contains(line, "-"))
        {
            removed = "-";
            removeElement(operationsRemoved, "-");
        }
        else if (contains(line, "*"))
        {
            removed = "*";
            removeElement(operationsRemoved, "*");
        }
        else if (contains(line, "/"))
        {
            removed = "/";
            removeElement(operationsRemoved, "/");
        }
        else
        {
            removed = "%";
            removeElement(operationsRemoved, "%");
        }

        temp.insert(make_pair(removed, operationsRemoved));

        return temp;
    }

    map<string, vector<string>> relationalOp(string line)
    {

        string removed;
        map<string, vector<string>> temp;
        vector<string> operationsRemoved;

        concatVectors(relationalOperations, &operationsRemoved);

        if (contains(line, ">"))
        {
            removed = ">";
            removeElement(operationsRemoved, ">");
        }
        else if (contains(line, ">="))
        {
            removed = ">=";
            removeElement(operationsRemoved, ">=");
        }
        else if (contains(line, "<"))
        {
            removed = "<";
            removeElement(operationsRemoved, "<");
        }
        else if (contains(line, "<="))
        {
            removed = "<=";
            removeElement(operationsRemoved, "<=");
        }
        else if (contains(line, "=="))
        {
            removed = "==";
            removeElement(operationsRemoved,"==");
        } 
        else
        {
            removed = "!=";
            removeElement(operationsRemoved, "!=");
        }
        
        temp.insert(make_pair(removed, operationsRemoved));

        return temp;
    }

    map<string, vector<string>> logicOp(string line)
    {

        string removed;
        map<string, vector<string>> temp;
        vector<string> operationsRemoved;

        concatVectors(logicOperations, &operationsRemoved);

        if (contains(line, "||"))
        {
            removed = "||";
            removeElement(operationsRemoved, "||");
        }
        else
        {
            removed = "&&";
            removeElement(operationsRemoved, "&&");
        }

        temp.insert(make_pair(removed, operationsRemoved));

        return temp;
    }

    map<string, vector<string>> findOperation(string line)
    {

        map<string, vector<string>> temp;

        if (contains(line, "+") || contains(line, "-") || contains(line, "*") || contains(line, "/") || contains(line, "%"))
        {

            cout << endl
                 << "Arithmetric Operation Found!";
            res.generatingMutations();
            temp = arithmetricOp(line);
        }
        else if (contains(line, "<") || contains(line, "<=") || contains(line, ">") || contains(line, ">=") || contains(line, "==") || contains(line, "!="))
        {

            cout << endl
                 << "Relational Operation Found!";
            res.generatingMutations();
            temp = relationalOp(line);
        }
        else
        {

            cout << endl
                 << "Logic Operation Found!";
            res.generatingMutations();
            temp = logicOp(line);
        }

        return temp;
    }

    void copyPreviousLine(int lineNumber, vector<string> *toCopyTo)
    {

        for (int i = 0; i < lineNumber; i++)
        {

            toCopyTo->push_back(prog[i]);
        }
    }

    void copyRemainingLine(int lineNumber, vector<string> *toCopyTo)
    {

        for (int i = lineNumber + 1; i < prog.size(); i++)
        {

            toCopyTo->push_back(prog[i]);
        }
    }

    string replaceLine(string line, string toReplaced, string toBeReplaced)
    {

        return replace_all_copy(line, toReplaced, toBeReplaced);
    }

    void generateMutatedProg()
    {

        for (int i = 0; i < prog.size(); i++)
        {

            if (hasOperations(prog[i]))
            {

                string operationRemoved;
                vector<string> operationsRemaining;
                map<string, vector<string>> mapOfOperations;

                mapOfOperations = findOperation(prog[i]);
                operationRemoved = mapOfOperations.begin()->first;
                operationsRemaining = mapOfOperations.begin()->second;

                for (int j = 0; j < operationsRemaining.size(); j++)
                {

                    vector<string> temp;

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

class mutChecker
{

public:
    mutChecker(vector<class mutatedProg> list, ioUtil io)
    {
        this->io = io;
        this->listofMutatedProg = list;

        findRepairedProg();
    }

    bool repairFound()
    {

        if (repairedProg.size() != 0)
        {

            return true;
        }

        return false;
    }

    vector<class mutatedProg> getRepairedProg()
    {

        return repairedProg;
    }

private:
    ioUtil io;
    vector<class mutatedProg> repairedProg;
    vector<class mutatedProg> listofMutatedProg;

    void findRepairedProg()
    {

        int numOfIO;

        numOfIO = io.getNumofIOPairs();

        for (int i = 0; i < listofMutatedProg.size(); i++)
        {

            if (listofMutatedProg[i].getFitness() == numOfIO)
            {

                repairedProg.push_back(listofMutatedProg[i]);
            }
        }
    }
};