#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "generalUtility.cpp"
#include "parser.cpp"
#include "ioUtility.cpp"
#include "repairUtility.cpp"
#include "mutatedProg.cpp"

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

  prompt.reqFilePath();
  cin >> filepath;

  repairUtil file(fp.copyFiletoVector(filepath));

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

    /*mutUtil repairProg(generatedTests);
    repairProg.repair();*/
  }

  cout << endl;

  return 0;
}