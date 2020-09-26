#include <map>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

class parser
{

public:
    void tokenizedLine(string line)
    {

        string token = "";
        string cleanedLine = line;

        boost::trim_right(cleanedLine);
        boost::trim_left(cleanedLine);

        for (char *tok = strtok(const_cast<char *>(cleanedLine.c_str()), ";"); tok != NULL; tok = strtok(NULL, ";"))
        {

            tokens.push_back(tok);
        }
    }

    map<string, int> getProgFunc()
    {

        findFunNames();

        return prog_functions;
    }

private:
    vector<string> tokens;
    vector<string> funName;
    map<string, int> prog_functions;

    bool functionLine(string line)
    {

        if (line.rfind("int", 0) == 0 && contains(line, "(") && contains(line, ")") && contains(line, "{"))
        {
            return true;
        }

        return false;
    }

    int argCounter(string line)
    {
        return count(line.begin(), line.end(), ',') + 1;
    }

    void findFunNames()
    {

        for (int i = 0; i < tokens.size(); i++)
        {

            string curr = tokens[i];

            if (functionLine(curr))
            {

                string functionName = curr.substr(curr.find("int") + 4, curr.find("(") - 4);

                prog_functions.insert(make_pair(functionName, argCounter(curr)));
            }
        }
    }
};
