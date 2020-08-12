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


int main() {

  int numofIO;
  string response;
  string filepath;
  vector<string> prog;
  vector<class mutatedProg> listofMutatedProg;

  prompt.reqFilePath();
  cin >> filepath;
  prog = fp.copyFiletoVector(filepath);

  repairUtil file(prog);

  prompt.filePathConfimation();
  res.dashedLine();
  file.previewFile();
  res.newLine();
  prompt.userConfirmation();
  cin >> response;

  if(response == "no") {
    err.opCancelled();
  }
  else if (response != "yes") {
    err.resNotRecog();
  }

  prompt.reqNumberofIO();
  cin >> numofIO;
  io.setNumberofIO(numofIO);
  prompt.reqProgIO();
  io.getUserIO();
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
    
  }

  cout << endl;

  return 0;
}