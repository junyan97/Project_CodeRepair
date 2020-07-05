#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

class parser {

    public:

        void tokenizedLine(string line) {

            string token = "";
            string cleanedLine = line;

            boost::trim_right(cleanedLine);
            boost::trim_left(cleanedLine);

            for(char *tok = strtok(const_cast<char*>(cleanedLine.c_str()), ";"); tok != NULL; tok = strtok(NULL, ";")) {

                tokens.push_back(tok);
                cout << "tokens: " << tok << endl;
                
            }

        }
        
        vector<string> getFunNames() {

            findFunNames();

            return funName;
        }

    private:

        vector<string> tokens;
        vector<string> funName;

        bool functionLine(string line) {
            
            if(line.rfind("int", 0) == 0 && contains(line, "(") && contains(line, ")") && contains(line, "{")) {
                return true;
            }

            return false;
        }

        void findFunNames() {

            for(int i = 0; i < tokens.size(); i++) {

                string curr = tokens[i];

                if(functionLine(curr)) {

                    funName.push_back(curr.substr(curr.find("int") + 4, curr.find("(") - 4));
                }
            }
        }
};
