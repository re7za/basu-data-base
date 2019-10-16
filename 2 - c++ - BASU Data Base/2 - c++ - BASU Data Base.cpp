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

string thisClass;
vector <Class> _class;

//the commands bank must be accessible everywhere
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
const short int classAreaCommandsNumber = 13;
const string classAreaCommands[classAreaCommandsNumber] = {
	"basu select none",
	"basu add student",
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


void Start();
void SelectClass(string);
void AddClass(string);
void RemoveClass(string);
void RemoveClass();
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
void Rank();


void templatePrinter();
void commandSpliter(string, vector <string>&);
void commandModifire(string&, vector <string>&);
int getIndexOfArea(string);
void toLowerCase(string&);
void runCommand(int, string);
void birthDay(string, Date&);
float setAverage(Class&);


int main()
{
	Start();
	return 0;
}

void Start()
{
	cout << "Wellcome to 'BASU DATA BASE'" << endl;
	int selector;
	//Continue until the user exits
	while (true)
	{
		//just to avoid crowding this function
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
			cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			continue;
		}
		else
			runCommand(mainPartIndex, commandVec[commandVec.size() - 1]);
	}
}

//command detection
void templatePrinter()
{
	cout << endl;
	cout << "**enter your command...";
	if (thisClass == "")
		cout << "in the 'Main-Area'...!" << endl;
	else if (thisClass != "")
		cout << "in the Class-Area..." << setw(3) << " class ( " << thisClass << " ) :" << endl;
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
	
	if (thisClass == "")
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
	else if (thisClass != "")
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
void runCommand(int index, string argument)
{
	if (thisClass == "")
		switch (index)
		{
		//basu add class <File Name>
		case 0: {
			AddClass(argument);
			break;
		}
		//basu remove class <Class Name>
		case 1: {
			RemoveClass(argument);
			break;
		}
		//basu select class <Class Name>
		case 2: {
			SelectClass(argument);
			break;
		}
		//basu show <Class Name> or nothing
		case 3: {
			if (argument == "show")
				//ShowAll();
			//else
				//ShowClass(argument);
			break;
		}
		//basu save
		case 4: {
			//Save();
		}
		//basu help
		case 5: {
			//Help();
		}
		//basu rank
		case 6: {
			//Rank();
		}
		//exit
		case 7: {
			return;
		}
		}
	else if (thisClass != "")
		switch (index)
		{
		//basu select none
		case 0: {
			thisClass = "";
			break;
		}
		//basu add student
		case 1: {

		}
		//basu remove student <ID>
		case 2: {

		}
		//basu search <ID> or <Full Name>
		case 3: {

		}
		//basu show
		case 4: {

		}
		//basu sort name
		case 5: {
			//SortByName();
		}
		//basu sort id
		case 6: {
			//SortByID();
		}
		//basu save
		case 7: {
			//Save();
		}
		//basu help
		case 8: {
			//Help();
		}
		//basu rank
		case 9: {
			//Rank();
		}
		//basu remove class
		case 10: {
			RemoveClass();
		}
		//basu select class <Class Name>
		case 11: {
			//SelectClass(argument);
		}
		//exit
		case 12: {
			return;
		}
		}
	else
	{
		cout << "!? : " << "somthing wrong with selector" << endl;
		return;
	}
}

void AddClass(string fileName)
{
	
	ifstream reader(fileName.c_str(), ios::beg);
	if (!reader) {
		cout << "!? : " << "<<SOMTHING WRONG!!!>>" << "   " << "there is no file named '" << fileName << "'..!" << endl;
		return;
	}

	Class newClass;
	Student newStud;
	reader >> newClass.ClassName;

	//Prevent re-adding a file
	for (Class temp : _class)
		if (temp.ClassName == newClass.ClassName) {
			cout << "!? : '" << fileName << "' is already exists..!" << endl;
			reader.close();
			return;
		}

	reader >> newClass.Capacity;
	for (size_t i = 0; i < newClass.Capacity; i++)
	{
		reader >> newStud.Firstname;
		reader >> newStud.Lastname;
		string simpleDate;
		reader >> simpleDate;
		birthDay(simpleDate, newStud.Birthday);
		reader >> newStud.Grade;
		reader >> newStud.ID;

		newClass.Data.push_back(newStud);
	}
	newClass.Average = setAverage(newClass);
	_class.push_back(newClass);

	cout << "'" << fileName << "'" << " added successfully..!" << endl;

	reader.close();
}
void birthDay(string simpleDate , Date& birthDay)
{
	//birthDay modifying

	string date;
	size_t counter = 0;
	for (size_t i = 0; i < simpleDate.size(); i++)
	{
		date += simpleDate[i];

		if (simpleDate[i] == '/' || i == simpleDate.size() - 1) {
			if (counter == 0)
				birthDay.Year = stoi(date);
			else if (counter == 1)
				birthDay.Month = stoi(date);
			else
				birthDay.Day = stoi(date);
			counter++;
			date = "";
			continue;
		}

	}
}
float setAverage(Class& newClass)
{
	float sum = 0;
	for (Student data : newClass.Data)
	{
		sum += data.Grade;
	}
	return sum / newClass.Capacity;
}
void RemoveClass(string className)
{
	for (int i = 0; i < _class.size(); i++)
		if (_class[i].ClassName == className)
		{
			_class.erase(_class.begin() + i);
			cout << "class '" << className << "' was removed successfully..!" << endl;
			return;
		}
	cout << "!? : " << "there is no class named '" << className << "'..!" << endl;
}
void RemoveClass()
{
	for (int i = 0; i < _class.size(); i++)
		if (_class[i].ClassName == thisClass)
		{
			_class.erase(_class.begin() + i);
			cout << "class '" << thisClass << "' was removed successfully..!" << endl;
			thisClass = "";
			return;
		}
}
void SelectClass(string className)
{
	for (Class selected : _class)
		if (selected.ClassName == className)
		{
			thisClass = className;
			cout << "class '" << className << "' was selected successfully..!" << endl;
			return;
		}
	cout << "!? : " << "there is no class called '" << className << "'..!"<< endl;
}


/*

	for (Class cls : _class)
	{
		cout << cls.ClassName << endl << cls.Capacity << endl << cls.Average << endl;
		for (Student data : cls.Data)
		{
			cout << data.Firstname << " " << data.Lastname << " "
				<< data.Birthday.Year << "-" << data.Birthday.Month << "-" << data.Birthday.Day << " "
				<< data.Grade << " " << data.ID << endl;
		}
	}

*/