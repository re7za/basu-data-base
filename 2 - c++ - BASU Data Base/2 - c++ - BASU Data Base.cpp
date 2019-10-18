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

string thisClass = "";
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
void runCommand(int, string, string);
void birthDay(string, Date&);
float setAverage(const Class&);
void getStudent();
void printRanks(const Class&);
void sortByGrade(Class&);
void fileCreater(string);


int main()
{
	Start();
	return 0;
}

void Start()
{
	cout << "Wellcome to 'BASU DATA BASE'" << endl;

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
		if (mainPartIndex == -1)
		{
			cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			continue;
		}
		else if (mainPartIndex == -2)
		{
			cout << "!? : " << "your command does not available in this area..!"
				<< " enter 'basu help' to display command list..!" << endl;
			continue;
		}
		else
			runCommand(mainPartIndex, commandVec[commandVec.size() - 1], commandVec[commandVec.size() - 2]);
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
		cout << "in the 'Class-Area'..." << " class ( " << thisClass << " ) ...!" << endl;
	cout << "-> ";
}
void commandSpliter(string _command, vector <string>& commandVec)
{
	while (true)
	{
		//if all characters are checked, exit
		size_t letterCounter = 0;
		for (const char letter : _command)
		{
			if (letter != '`') {
				letterCounter++;
				break;
			}
		}
		if (letterCounter == 0)
			return;

		//extract the words from the command and push them in the vector
		string word;
		for (char& letter : _command)
			if (letter == '`')
				continue;
			else if (letter == ' ') {
				letter = '`';
				break;
			}
			else {
				word += letter;
				letter = '`';
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
	//is command main part entered true?? or false? return index of command from its bank if true

	int wtf = 0;		//was this command found in the other bank?
	toLowerCase(_command);
	int index = 0;
	for (const string& mainCommands : mainAreaCommands)
	{
		if (_command.size() < mainCommands.size())
		{
			index++;
			continue;
		}
		short int mistakeCounter = 0;
		for (size_t i = 0; i < mainCommands.size(); i++)
			if (mainCommands[i] != _command[i])
			{
				mistakeCounter++;
			}
		if (mistakeCounter == 0)
		{
			if (thisClass == "")
				return index;
			else if (thisClass != "")
				wtf++;
		}
		index++;
	}

	index = 0;
	for (const string& mainCommands : classAreaCommands)
	{
		if (_command.size() < mainCommands.size())
		{
			index++;
			continue;
		}
		short int mistakeCounter = 0;
		for (size_t i = 0; i < mainCommands.size(); i++)
			if (mainCommands[i] != _command[i])
			{
				mistakeCounter++;
				break;
			}
		if (mistakeCounter == 0)
		{
			if (thisClass != "")
				return index;
			else if (thisClass == "")
				wtf++;
		}
		index++;
	}
	if (wtf != 0)
		return -2;
	return -1;
}
void toLowerCase(string& _command)
{
	for (char& letter : _command)
		if (letter >= 65 && letter <= 90)
			letter += 32;
}
void runCommand(int index, string argument, string argument_1)
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
				ShowAll();
			else
				ShowClass(argument);
			break;
		}
		//basu save
		case 4: {
			if (argument == "save")
				Save();
			else
				cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			break;
		}
		//basu help
		case 5: {
			if (argument == "help")
				Help();
			else
				cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			break;
		}
		//basu rank
		case 6: {
			if (argument == "rank")
				Rank();
			else
				cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			break;
		}
		//exit
		case 7: {
			return;
		}
		}
	else
		switch (index)
		{
		//basu select none
		case 0: {
			if (argument == "none")
				thisClass = "";
			else
				cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			break;
		}
		//basu add student
		case 1: {
			if (argument == "student")
				getStudent();
			else
				cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			break;
		}
		//basu remove student <ID>
		case 2: {
			RemoveStudent(stoull(argument));
			break;
		}
		//basu search <ID> or <Full Name>
		case 3: {
			if (argument_1 == "search")
				Search(stoull(argument));
			else
				Search(argument_1, argument);
			break;
		}
		//basu show
		case 4: {
			if (argument == "show")
				ShowClass(argument);
			else
				cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			break;
		}
		//basu sort name
		case 5: {
			if (argument == "name")
				SortByName();
			else
				cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			break;
		}
		//basu sort id
		case 6: {
			if (argument == "id")
				SortByID();
			else
				cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			break;
		}
		//basu save
		case 7: {
			if (argument == "save")
				Save();
			else
				cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			break;
		}
		//basu help
		case 8: {
			if (argument == "help")
				Help();
			else
				cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			break;
		}
		//basu rank
		case 9: {
			if (argument == "rank")
				Rank();
			else
				cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			break;
		}
		//basu remove class
		case 10: {
			if (argument == "class")
				RemoveClass();
			else
				cout << "!? : " << "<<WRONG INPUT!!!>>" << "   " << "enter 'basu help' to show command list.." << endl;
			break;
		}
		//basu select class <Class Name>
		case 11: {
			SelectClass(argument);
			break;
		}
		//exit
		case 12: {
			//return;
		}
		}
}
//another functions
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
	//birthday modifying

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
float setAverage(const Class& newClass)
{
	float sum = 0;
	for (const Student& stud : newClass.Data)
	{
		sum += stud.Grade;
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
			cout << "class '" << className << "' was selected..!" << endl;
			return;
		}
	cout << "!? : " << "there is no class called '" << className << "'..!"<< endl;
}
void getStudent()
{
	cout << endl << "**student registration form ( " << thisClass << " )" << endl;

	string name;
	while (true)
	{
		cout << "enter his/her full name : ";
		getline(cin, name);
		size_t err = 0;
		for (char i : name)
			if (!((i >= 65 && i <= 90) || (i >= 97 && i <= 122) || (i == ' ')))
			{
				err++;
				break;
			}
		if (err == 0)
			break;
		else
			cout << "!? : " << "number not allowed..!!!" << endl;
	}

	unsigned long long int id;
	while (true)
	{
		cout << "ID : ";
		cin >> id;
		if (id > 999999999 && id < 10000000000)
			break;
		else
			cout << "!? : " << "id must be exactly '10' digits..!!!" << endl;
	}

	cin.ignore();
	Date birthday;
	string _birth;
	cout << "Birthday (yyyy/mm/dd) : ";
	getline(cin, _birth);
	//modifying
	string date;
	size_t counter = 0;
	for (size_t i = 0; i < _birth.size(); i++)
	{
		date += _birth[i];

		if (_birth[i] == '/' || i == _birth.size() - 1) {
			if (counter == 0)
				birthday.Year = stoi(date);
			else if (counter == 1)
				birthday.Month = stoi(date);
			else
				birthday.Day = stoi(date);
			counter++;
			date = "";
			continue;
		}
	}

	float grade;
	while (true)
	{
		cout << "Grade : ";
		cin >> grade;
		if (grade <= 20 && grade >= 0)
			break;
		else
			cout << "!? : " << "the grade should be from 0 to 20..!!!" << endl;
	}

	AddStudent(name, birthday, id, grade);
}
void AddStudent(string name, Date birthday, unsigned long long int id, float grade)
{
	Student stud;

	vector <string> Fname;
	commandSpliter(name, Fname);

	if (Fname.size() >= 1)
		stud.Firstname = Fname[0];
	if (Fname.size() >= 2)
		stud.Lastname = Fname[1];
	if (Fname.size() >= 3)
		stud.Lastname += " " + Fname[2];
	if (Fname.size() >= 4)
		stud.Lastname += " " + Fname[3];

	stud.Birthday = birthday;
	stud.ID = id;
	stud.Grade = grade;

	for (Class& cls : _class)
		if (cls.ClassName == thisClass)
		{
			cls.Capacity++;
			cls.Data.push_back(stud);
			cls.Average = setAverage(cls);
			break;
		}

	cout << endl << "the student was added to the class successfully..!" << endl;
	cin.ignore();
}
void RemoveStudent(unsigned long long int id)
{
	for (Class &cls : _class)
		if (cls.ClassName == thisClass)
			for (size_t i = 0; i < cls.Data.size(); i++)
				if (cls.Data[i].ID == id)
				{
					cls.Capacity++;
					cls.Data.erase(cls.Data.begin() + i);
					cls.Average = setAverage(cls);
					cout << "Student '" << id << "' was removed successfully..!" << endl;
					return;
				}
	cout << "!? : " << "there is no student by id '" << id << "'..!" << endl;
}
void ShowClass(string className)
{
	//basu show in main area
	if (thisClass != "")
		className = thisClass;

	for (const Class cls : _class)
		if (cls.ClassName == className)
		{
			cout << "class '" << cls.ClassName << "' :" << endl
				<< "capacity : " << cls.Capacity << endl
				<< "average : " << cls.Average << endl
				<< "students :" << endl
				<< "First Name" << "    " << "Last Name" << "     "
				<< "Birthday" << "          " << "Grade" << "          " << "ID" << endl;
			for (const Student data : cls.Data)
			{
				cout << data.Firstname << setw(16) << data.Lastname << setw(11)
					<< data.Birthday.Year << "-" << data.Birthday.Month << "-" << data.Birthday.Day << setw(13)
					<< data.Grade << setw(20) << data.ID << endl;
			}
			return;
		}

	cout << "!? : " << "there is no class named '" << className << "'..!" << endl;
}
void ShowAll()
{
	if (_class.size() == 0)
	{
		cout << "!? : " << "there are no classes yet..!" << endl;
		return;
	}
	for (const Class cls : _class)
	{
		cout << "class '" << cls.ClassName << "' :" << endl
			<< "capacity : " << cls.Capacity << endl
			<< "average : " << cls.Average << endl
			<< "students :" << endl
			<< "First Name" << "    " << "Last Name" << "     "
			<< "Birthday" << "          " << "Grade" << "           " << "ID" << endl;
		for (const Student data : cls.Data)
		{
			cout << data.Firstname << setw(16) << data.Lastname << setw(11)
				<< data.Birthday.Year << "-" << data.Birthday.Month << "-" << data.Birthday.Day << setw(13)
				<< data.Grade << setw(20) << data.ID << endl;
		}
		cout << endl;
	}
}
void SortByName()
{
	//hard core
	for (Class& cls : _class)
		if (cls.ClassName == thisClass)
			for (size_t studCounter1 = 0; studCounter1 < cls.Data.size() - 1; studCounter1++)
				for (size_t studCounter2 = studCounter1; studCounter2 < cls.Data.size(); studCounter2++)
					for (size_t letterCounter = 0; letterCounter < cls.Data[studCounter1].Firstname.size(); letterCounter++)
						if (cls.Data[studCounter1].Firstname[letterCounter] > cls.Data[studCounter2].Firstname[letterCounter])
						{
							//swapping
							Student bubbleStud = cls.Data[studCounter1];
							cls.Data[studCounter1] = cls.Data[studCounter2];
							cls.Data[studCounter2] = bubbleStud;
							break;
						}
						else if (cls.Data[studCounter1].Firstname[letterCounter] < cls.Data[studCounter2].Firstname[letterCounter])
							break;
	cout << "students were sorted by name successfully..!" << endl;
}
void SortByID()
{
	for (Class& cls : _class)
		if (cls.ClassName == thisClass)
			for (size_t studCounter1 = 0; studCounter1 < cls.Data.size() - 1; studCounter1++)
				for (size_t studCounter2 = studCounter1; studCounter2 < cls.Data.size(); studCounter2++)
						if (cls.Data[studCounter1].ID > cls.Data[studCounter2].ID)
						{
							//swapping
							Student bubbleStud = cls.Data[studCounter1];
							cls.Data[studCounter1] = cls.Data[studCounter2];
							cls.Data[studCounter2] = bubbleStud;
						}
	cout << "students were sorted by ID successfully..!" << endl;
}
void Search(unsigned long long int id)
{
	for (Class& cls : _class)
		if (cls.ClassName == thisClass)
			for (size_t i = 0; i < cls.Data.size(); i++)
				if (cls.Data[i].ID == id)
				{
					cout << endl;
					cout << cls.Data[i].Firstname << " " << cls.Data[i].Lastname << " born in '"
						<< cls.Data[i].Birthday.Year << "-" << cls.Data[i].Birthday.Month << "-"
						<< cls.Data[i].Birthday.Day << "' with average '" << cls.Data[i].Grade
						<< "' and ID '" << cls.Data[i].ID << "'" << endl;
					return;
				}
	cout << "!? : " << "there is no student with ID '" << id << "'..!" << endl;
}
void Search(string Fname, string Lname)
{
	for (Class& cls : _class)
		if (cls.ClassName == thisClass)
			for (size_t i = 0; i < cls.Data.size(); i++)
				if (cls.Data[i].Firstname == Fname)
					if (cls.Data[i].Lastname == Lname)
						{
							cout << endl;
							cout << cls.Data[i].Firstname << " " << cls.Data[i].Lastname << " born in '"
								<< cls.Data[i].Birthday.Year << "-" << cls.Data[i].Birthday.Month << "-"
								<< cls.Data[i].Birthday.Day << "' with average '" << cls.Data[i].Grade
								<< "' and ID '" << cls.Data[i].ID << "'" << endl;
							return;
						}
	cout << "!? : " << "there is no student with this name " << endl;
}
void Help()
{
	if (thisClass == "")
	{
		cout << endl;
		cout << "allowed commands in the main area are : " << endl;
		size_t i = 1;
		for (const string command : mainAreaCommands)
		{
			if (i < 10)
				cout << "0" << i++ << " ) " << command << endl;
			else
			cout << i++ << " ) " << command << endl;
		}
	}
	else
	{
		cout << endl;
		cout << "allowed commands in the class area are : " << endl;
		size_t i = 1;
		for (const string command : classAreaCommands)
		{
			if (i < 10)
				cout << "0" << i++ << " ) " << command << endl;
			else
				cout << i++ << " ) " << command << endl;
		}
	}

}
void Rank()
{
	if (thisClass != "")
	{
		Class CLS;
		for (const Class SLS : _class)
			if (SLS.ClassName == thisClass)
			{
				CLS = SLS;
				break;
			}

		sortByGrade(CLS);
		printRanks(CLS);
	}
	else
	{
		Class bubbleCls;
		bubbleCls.ClassName = "all Classe";
		bubbleCls.Capacity = 0;
		//make copy from All students
		for (const Class& cls : _class)
			for (const Student& stud : cls.Data)
			{
				bubbleCls.Capacity++;
				bubbleCls.Data.push_back(stud);
			}

		bubbleCls.Average = setAverage(bubbleCls);
		sortByGrade(bubbleCls);
		printRanks(bubbleCls);
	}
}
void sortByGrade(Class& cls)
{
	for (size_t studCounter1 = 0; studCounter1 < cls.Data.size() - 1; studCounter1++)
		for (size_t studCounter2 = studCounter1; studCounter2 < cls.Data.size(); studCounter2++)
			if (cls.Data[studCounter1].Grade < cls.Data[studCounter2].Grade)
			{
				//swapping
				Student bubbleStud = cls.Data[studCounter1];
				cls.Data[studCounter1] = cls.Data[studCounter2];
				cls.Data[studCounter2] = bubbleStud;
			}
}
void printRanks(const Class& cls)
{
	//just for one class

	size_t counter;
	cout << endl;
	cout << "in class '" << thisClass << "' :" << endl;
	cout << "rank A )" << endl;
	for (counter = 0; counter < cls.Capacity && cls.Data[counter].Grade >= 18; counter++)
		cout << "   " << cls.Data[counter].Firstname << " " << cls .Data[counter].Lastname << " " << cls.Data[counter].Grade << endl;
	cout << endl << "rank B )" << endl;
	for (counter; counter < cls.Capacity && cls.Data[counter].Grade >= 15; counter++)
		cout << "   " << cls.Data[counter].Firstname << " " << cls.Data[counter].Lastname << " " << cls.Data[counter].Grade << endl;
	cout << endl << "rank C )" << endl;
	for (counter; counter < cls.Capacity && cls.Data[counter].Grade >= 12; counter++)
		cout << "   " << cls.Data[counter].Firstname << " " << cls.Data[counter].Lastname << " " << cls.Data[counter].Grade << endl;
	cout << endl << "rank D )" << endl;
	for (counter; counter < cls.Capacity && cls.Data[counter].Grade >= 10; counter++)
		cout << "   " << cls.Data[counter].Firstname << " " << cls.Data[counter].Lastname << " " << cls.Data[counter].Grade << endl;
	cout << endl << "rank E )" << endl;
	for (counter; counter < cls.Capacity && cls.Data[counter].Grade >= 0; counter++)
		cout << "   " << cls.Data[counter].Firstname << " " << cls.Data[counter].Lastname << " " << cls.Data[counter].Grade << endl;
	cout << endl;
}
void Save()
{
	if (thisClass != "")
		fileCreater(thisClass);
	else
		for (const Class& cls : _class)
		{
			fileCreater(cls.ClassName);
			cout << endl;
		}
}
void fileCreater(string clsName)
{
	for (const Class& cls : _class)
		if (cls.ClassName == clsName)
		{
			cout << "choose a name for the new file (changed file from '" << clsName << "' class) : ";
			string newName;
			getline(cin, newName);

			ofstream writer(newName.c_str());
			if (!writer)
			{
				cout << "!? : " << "<<SOMTHING WRONG!!!>>" << "   " << "an error occured with file creating..!" << endl;
				return;
			}

			writer << cls.ClassName << endl;
			writer << cls.Capacity << endl;
			for (const Student& stud : cls.Data)
			{
				writer << stud.Firstname << " " << stud.Lastname << " "
					<< stud.Birthday.Year << "/"
					<< stud.Birthday.Month << "/"
					<< stud.Birthday.Day << " "
					<< stud.Grade << " " << stud.ID << endl;
			}
			cout << "the student was added to the class successfully..!" << endl;
		}
}


