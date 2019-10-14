//syd reza qaemi
//9712358033
//TA Project
//The Second Project
//BASU Data Base


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

//vector <Class> Database;

//the commands bank must be accessible everywhere
enum area {mainArea, classArea};
int selector = mainArea;
const short int mainAreaCommandsNumber = 8;
const string mainAreaCommands[mainAreaCommandsNumber] = {
	"basu add class",
	"basu remove class",
	"basu select class",
	"basu show",
	"basu save",
	"basu help",
	"basu rank",
	"exit"
};
const short int classAreaCommandsNumber = 12;
const string classAreaCommands[classAreaCommandsNumber] = {
	"basu select none",
	"basu remove student",
	"basu search",
	"basu show",
	"basu sort name",
	"basu sort id",
	"basu save",
	"basu help",
	"basu rank",
	"basu remove class",
	"basu select class",
	"exit"
};

struct Date
{
	unsigned short int Year;
	unsigned short int Month;
	unsigned short int Day;
};
struct Student
{
	string Firstname;
	string Lastname;
	unsigned long long int ID;
	Date Birthday;
	float Grade;
};
struct Class
{
	string ClassName;
	float Average;
	unsigned short int Capacity;
	vector <Student> Data;
};

void Start();
void SelectClass(string);
void AddClass(string);
void RemoveClass(string);
void AddStudent(string, Date, unsigned long long int, float);
void RemoveStudent(unsigned long long int);
void Search(unsigned long long int);
void Search(string, string);
void ShowClass(string);
void ShowAll();
void SortByName();
void SortByID();
void Save();
void Help();


void templatePrinter();
void commandSpliter(string, vector <string>&);
void commandModifire(string&, vector <string>&);
int getIndexOfArea(string);
void toLowerCase(string&);
void runCommand(int, string ,const vector <string>&);



int main()
{
	Start();
	return 0;
}

void Start()
{
	//Continue until the user exits
	while (true)
	{
		//just to avoid crowding the function
		templatePrinter();

		string command;
		getline(cin, command);

		//split the command into several parts in the vector
		vector <string> commandVec;
		commandSpliter(command, commandVec);

		//remove the extra spaces
		commandModifire(command, commandVec);

		int mainPartIndex = getIndexOfArea(command);
		if (mainPartIndex == -1) {
			cout << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			continue;
		}
		else
			runCommand(mainPartIndex, command, commandVec);
	}
}

void templatePrinter()
{
	cout << endl;
	cout << "**enter your command...";
	if (selector == mainArea)
		cout << "in the Main Area...!" << endl;
	else if (selector == classArea)
		cout << "in the Class Area..." << setw(3) << "on class (<Class Name>) !" << endl;
	cout << "-> ";
}
void commandSpliter(string _command, vector <string>& commandVec)
{
	while (true)
	{
		//if all characters are checked, exit
		size_t letterCounter = 0;
		for (char letter : _command)
		{
			if (letter != '0') {
				letterCounter++;
				break;
			}
		}
		if (letterCounter == 0)
			return;

		//extract the words from the command and push them in the vector
		string word;
		for (char& letter : _command)
			if (letter == '0')
				continue;
			else if (letter == ' ') {
				letter = '0';
				break;
			}
			else {
				word += letter;
				letter = '0';
			}
		if (word.size() > 0)
			commandVec.push_back(word);
	}
}
void commandModifire(string& _command,vector <string>& commandVec)
{
	_command = "";
	for (size_t i = 0; i < commandVec.size(); i++)
	{
		_command += commandVec[i];
		if (i != commandVec.size() - 1)
			_command += " ";
	}
}
int getIndexOfArea(string _command)
{
	//is command main part entered true?? or false?
	
	if (selector == mainArea)
	{
		toLowerCase(_command);
		int index = 0;
		for (const string& mainCommands : mainAreaCommands)
		{
			if (_command.size() < mainCommands.size())
				continue;
			size_t mistakeCounter = 0;
			for (size_t j = 0; j < mainCommands.size(); j++)
				if (mainCommands[j] != _command[j])
					mistakeCounter++;
			if (mistakeCounter == 0)
				return index;
			index++;
		}
	}
	else if (selector == classArea)
	{
		toLowerCase(_command);
		int index = 0;
		for (const string& mainCommands : classAreaCommands)
		{
			if (_command.size() < mainCommands.size())
				continue;
			size_t mistakeCounter = 0;
			for (size_t i = 0; i < mainCommands.size(); i++)
				if (mainCommands[i] != _command[i])
					mistakeCounter++;
			if (mistakeCounter == 0)
				return index;
			index++;
		}
	}
	return -1;
}
void toLowerCase(string& _command)
{
	for (char& letter : _command)
		if (letter >= 65 && letter <= 90)
			letter += 32;
}
void runCommand(int index, string command, const vector <string>& commandVec)
{
	
}


