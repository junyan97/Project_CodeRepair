#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "fileUtility.cpp"
#include "repairUtility.cpp"


using namespace std;


int main() {

  string filepath;
  string input_output;

  cout << "Please enter exact path of program to be repaired: ";
  cin >> filepath;
  cout << "Please enter input/output example in the form (input, output)";
  cout << endl;

  fileUtil file(filepath);
  repairUtil program(filepath);

  
  if(file.correctFormat() && !program.requireRepair()) {
    cout << "-----------------------------------" << endl;
    cout << endl << "Program do not require repair" << endl;
  }else{
    cout << "-----------------------------------" << endl;
    cout << endl << "Program require repair" << endl;
  }
  system("rm temp");
  cout << endl;
  
  return 0;
}