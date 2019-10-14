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

const short int mainAreaCommandsNumber = 7;
string mainAreaCommands[mainAreaCommandsNumber] = {
	"basu add class",
	"basu remove class",
	"basu select class",
	"basu show",
	"basu save",
	"basu help",
	"basu rank"
};
const short int classAreaCommandsNumber = 11;
string classAreaCommands[classAreaCommandsNumber] = {
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
	"basu select class"
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

void commandConverter(string , vector <string>&);
void toLowerCase(string&);

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
		string command;
		getline(cin, command);
		
		//convert the command into several parts in vector
		vector <string> commandVec;
		commandConverter(command, commandVec);

		//the main part of command should not be casesensitive
		//convert the command to lowercase... except the last word
		for (int i = 0; i < commandVec.size() - 1; i++)
			toLowerCase(commandVec[i]);

		string commandMainPart;
		for (int i = 0; i < commandVec.size() - 1; i++) {
			commandMainPart += commandVec[i];
			if (i != commandVec.size() - 2)
				commandMainPart += " ";
		}

		cout << commandMainPart << "///" << commandMainPart.size() << endl;


	}
}

void commandConverter(string _command, vector <string>& commandVec)
{
	while (true)
	{
		//if all characters are checked, exit
		int letterCounter = 0;
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
void toLowerCase(string& _command)
{
	for (char& letter : _command)
		if (letter >= 65 && letter <= 90)
			letter += 32;
}

