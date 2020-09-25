#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "generalUtility.cpp"
#include "parser.cpp"
#include "ioUtility.cpp"
#include "repairUtility.cpp"
#include "mutatedProg.cpp"
#include "mutationUtility.cpp"

using namespace std;

response res;
errorUtil err;
userPrompt prompt;
ioUtil io;
fileOperation fp;

void filePreview(vector<string> fileInVec) {
    
    prompt.filePathConfimation();
    res.dashedLine();
    fp.previewFile(fileInVec);
    res.newLine();
}

void requestIO() {

    string response;

    prompt.reqIOoption();
    cin >> response;

    if(response == "yes") {

      int numofIO;

      prompt.reqNumberofIO();
      cin >> numofIO;
      io.setNumberofIO(numofIO);
      prompt.reqProgIO();
      io.getUserIO();

    }
    else if(response == "no") {

      string ioFile;

      prompt.reqIOfile();
      cin >> ioFile;
      io.setIOfile(ioFile);

    }else{

      res.message("Incorrect usuage: Please enter yes or no");
      err.opCancelled();

    }

}


int main(int argc, char **argv) {
    
    vector<string> prog;
    vector<class mutatedProg> listofMutatedProg;

    if(argc != 2) {

        res.message("Incorrect usuage: Please enter the file to be repaired");
        err.opCancelled();   
    }

    prog = fp.copyFiletoVector(argv[1]);

    repairUtil file(prog);

    filePreview(prog);
    
    requestIO();
    file.setIO(io);
    cout << endl;

    if(file.initialProgRepair()) {
      res.dashedLine();
      res.message("Program do not require repair");
    }else{
      res.dashedLine();
      res.message("Program require repair");

      mutUtil mutate(prog, io);
      
      listofMutatedProg = mutate.getListofMutatedProg();

      mutChecker checker(listofMutatedProg, io);

      if(checker.repairFound()) {

          res.dashedLine();
          res.message("repaired found");
        
          vector<class mutatedProg> temp;

          temp = checker.getRepairedProg();

          for(int i = 0; i < temp.size(); i++) {

            string filePath = "repairedProgram/prog_";

            fp.copyVectortoFile(filePath + to_string(i) + ".c", temp[i].getMutatedProg());

          }
      }else{
          
          res.dashedLine();
          res.message("no repair found");
      }

        system("rm testFile.c");
        /*system("rm temp");*/ 
    }

    

    cout << endl;

    return 0;
  }