#include "func.h"

void inverseSymbols(string fileInput, string fileOutput){
  ifstream readFile(fileInput);
  ofstream writeFile(fileOutput);
 
  string currentString;
  
  while(readFile >> currentString){
    for(int i=0; i < currentString.size() / 2; i++){
       char save = currentString[i];
       currentString[i] = currentString[currentString.size() - i - 1];
       currentString[currentString.size() - i - 1] = save;
    }
    writeFile << currentString << endl;
  }
  
  readFile.close();
  writeFile.close();
}

