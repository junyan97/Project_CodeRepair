#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "generalUtility.cpp"
#include "parser.cpp"
#include "ioUtility.cpp"
#include "progUtility.cpp"
#include "repairUtility.cpp"
#include "mutationUtility.cpp"
#include "mutatedProg.cpp"


/*
TODO1: able to determine the number of input require.
TODO2: remove main function after program repaired.
*/

using namespace std;

response res;
errorUtil err;
userPrompt prompt;
ioUtil io;


int main() {

  int numofIO;
  string response;
  string filepath;
  /*string input_output;*/
  string generatedTests = "test_prog.c";

  prompt.reqFilePath();
  cin >> filepath;

  progUtil file(filepath);

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
  /*cin >> input_output;*/
  /*file.setioString(input_output);*/
  cout << endl;

  repairUtil program(generatedTests);

  if(file.correctFormat() && !program.requireRepair()) {
    res.dashedLine();
    res.message("Program do not require repair");
  }else{
    res.dashedLine();
    res.message("Program require repair");

    mutUtil repairProg(generatedTests);
    repairProg.repair(); 
  }
  system("rm temp");
  system("rm test_prog.c");
  cout << endl;

  return 0;
}