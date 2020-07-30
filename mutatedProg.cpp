#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


class mutatedProg {

    public:
        mutatedProg(string path) {
            this->progPath = path;
        }

    private:
        int fitness;
        string progPath;


};