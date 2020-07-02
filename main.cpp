#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "fileUtility.cpp"
#include "repairUtility.cpp"
#include "mutationUtility.cpp"


using namespace std;


int main() {

  string response;
  string filepath;
  string input_output;
  string generatedTests = "test_prog.c";

  cout << "Please enter exact path of program to be repaired: ";
  cin >> filepath;

  fileUtil file(filepath);

  cout << "Is the following the file to be inspected" << endl;
  cout << "---------------------------------------------" << endl;
  file.previewFile();
  cout << endl <<"Type yes to proceed and no to cancel the operation: ";
  cin >> response;

  if(response == "no") {
    cout << "operation cancelled" << endl;
    exit(EXIT_SUCCESS);
  }
  else if (response != "yes") {
    cout << "response not recognized" << endl;
    exit(EXIT_SUCCESS);
  }

  cout << "Please enter input/output example in the form (input, output): ";
  cin >> input_output;
  file.setioString(input_output);
  cout << endl;
  
  repairUtil program(generatedTests);
  
  if(file.correctFormat() && !program.requireRepair()) {
    cout << "-----------------------------------" << endl;
    cout << endl << "Program do not require repair" << endl;
  }else{
    cout << "-----------------------------------" << endl;
    cout << endl << "Program require repair" << endl;

    mutUtil repairProg(generatedTests);
    repairProg.repair();

    
  }
  system("rm temp");
  system("rm test_prog.c");
  cout << endl;
  
  return 0;
}