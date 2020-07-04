#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class FileUtil {

    public:

        FileUtil(string path) {
            this->path = path;
        }

        bool correctFormat() {
            if(openFile) {
                return true;
            }else {
                return false;
            }
        }

    private:

        string path;

        bool openFile() {
            string myText;
            fstream readFile(path);

            //check to see if file opens.
            if(!readFile) {
                cerr << "Error, opening file. " << endl;
                exit(EXIT_FAILURE);
            }
            if(!endsWith(path, ".c")) {
                cerr << "Incorrect file type " << endl;
                exit(EXIT_FAILURE);
            }

            readFile.close();

            return true;
        }

        bool endsWith(string mainStr, string toMatch) {
            if(mainStr.size() >= toMatch.size() &&
                    mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0)
                    return true;
                else
                    return false;
        } 


};