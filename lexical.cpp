#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<string.h>
using namespace std;

//readings of files
ifstream myFile;
ofstream outFile;
//char arrays to store identifiers
char keywords[20][10] = {"int", "float", "bool", "true", "false", "if", "else", "then", "endif",
"while", "whileend", "do", "doend","for", "forend", "input", "output", "and", "or", "not"};
char separators[] = "'(){}[],:;";
char operators[] = {'*', '+', '-', '=', '/', '>', '<', '%'};
//check if theres separator
bool separation =false;
//check if theres operator
bool operation =false;
//index used in containsNum
int curIndex = 0;
//states to print
bool sep=false;
bool op=false;
bool ident=false;
bool num=false;
//get chars
char ch;
//store chars here to identify their type
char buffer[20];
//buffer index
int x = 0;
//check if comment
bool comments=false;
//!block comment! detection
char detection[2] = {'\0'};
//used in detecting count
int y = 0;
//contains keyword check
bool containsKey(char buffer[]){
	for (int i = 0; i < 20; ++i)
		if (strcmp(keywords[i], buffer) == 0)
return true;
return false;
 }
//contains separator check
bool containsSep(char ch){
for (int i = 0; i < 10; ++i){
	if (ch == separators[i])
		return true;
	 }
		return false;
	}
//contains operator check
bool containsOp(char ch){
for (int i = 0; i < 10; ++i){
	if (ch == operators[i])
		return true;
	 }
	  return false;
	}
//conatins an integer check
bool containsNum(char buffer[]){
for (int i = 0; i <= (curIndex-1); i++){
	if (!isdigit(buffer[i]))
		return false;
		continue;
	 }
		return true;
}
//outputting
void print(){
	if (ident){
		cout << "Identifier 			= 			" << buffer << endl;
		outFile << "Identifier 			= 			" << buffer << endl;
		ident = false;
	}
	if (num){
		cout << "Integer 			= 			" << buffer << endl;
		outFile << "Integer 				= 			" << buffer << endl;
		num = false;
	}
	//printing of separators
	if (sep){
		cout << "Separator 			= 			" << ch << endl;
		outFile << "Separator 			= 			" << ch << endl;
		sep = false;
		separation = false;
	}
	//printing of operators
	if (op){
		cout << "Operator 			= 			" << ch << endl;
		outFile << "Operator 			= 			" << ch << endl;
		op = false;
		operation = false;
	}
}
//lexical analyzer
void lexical(){
	//check for comment first if not then identify chars
	if (ch == '!'){
		detection[y] = ch;
		y++;
	if (detection[1] == ch){
		comments = false;
		y = 0;
		detection[0] ='\0';
		detection[1] ='\0';
	}
	else
		comments = true;
		}
	if (!comments){
	//not a comment then
	if (containsSep(ch)){
		separation = true;
		sep = true;
	}
	if (containsOp(ch)){
		operation = true;
		op = true;
	}
	//check if char is alphanumeric	. $
	if (isalnum(ch) || ch=='.' || ch=='$'){
		buffer[x++] = ch;
		curIndex++;
	}
	else if ((ch=='\n' ||ch ==' ' ||separation||operation||myFile.eof())&&(x != 0)){
		buffer[x] ='\0';
		x = 0;
	if (containsKey(buffer)){
		cout << "Keyword 			= 			" << buffer << endl;
		outFile << "Keywords 			= 			" << buffer << endl;
	}
	else if (containsNum(buffer))
		num = true;
	else {
	//check if doesnt start with number
	if (!isdigit(buffer[0]))
		ident = true;
		}
	//resetting
	curIndex = 0;
		}
		print();
	}
}
int main(){
	string filenameIn;
	string filenameOut;

	cout << "Enter file to read:";
	cin >> filenameIn;
	cout << "Enter file to ouput:";
	cin >> filenameOut;

	myFile.open(filenameIn);
	outFile.open(filenameOut);
	//error if could not open so exit
	if (!myFile.is_open()){
		cout << "Error\n";
		exit(0);}

	cout << "Tokens:							Lexemes:" << endl;
	outFile << "Tokens:							Lexemes:" << endl;
//implementation of lexical analyzer
	while (!myFile.eof()){
		ch=myFile.get();
		lexical();
	}
	//closing of Files
	myFile.close();
	outFile.close();
	return 0;
}
