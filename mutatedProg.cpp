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

        void setIO(ioUtil io) {
            this->io = io;
        }

    private:
        int fitness;
        string progPath;

        ioUtil io;


};