/*Jacqueline Cardenas
First Iteration reading and ouputting into new file
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*char separators[] = "'(){}[],.:;";
char operators[] = "*+-=/><%";
char keywords[] = "int","float", "bool", "true", "false", "if", "else", "then", "endif", "while", "whileend", "do", "doend", "for", "forend", "input", "output", "and", "or","not";
*/

ifstream myFile; //reading of file
ofstream outFile;


void lexical(){
//writing of lexical analyzer
}

int main() {
	string filenameIn;
  string filenameOut;

  cout << "Enter filename to read:";
	cin >> filenameIn;

	cout << "Enter file name to output:";
	cin >> filenameOut;


	myFile.open(filenameIn);
	outFile.open(filenameOut);

	if (!myFile.is_open()){
		cout << "Error\n";
		exit(0);
	}

  string content=" ";
  int i;

  for (i=0; myFile.eof()!=true; i++) //getting content of myFile
  content += myFile.get();

  i--;//erase last char
  content.erase(content.end()-1);

  cout << "Tokens       Lexemes\n" << content << endl;
	outFile << "Tokens 		Lexemes\n" ;
	outFile<<content;

  while (!myFile.eof()){
	lexical();
  }

  myFile.close(); //closing of files
  outFile.close();

  return 0;
}
