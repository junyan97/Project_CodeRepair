#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

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
