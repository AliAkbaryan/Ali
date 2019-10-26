#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string selected_class;
int index_selected_class = -1;

vector<string> split_with_slash(string text)
{
	vector<string> splitedWithSlash;
	string str = "";
	int i = 0;
	for (char x : text)
	{
		if (x == '/')
		{
			splitedWithSlash.push_back(str);
			str = "";
		}
		else
		{
			str = str + x;
		}
	}
	splitedWithSlash.push_back(str);
	return splitedWithSlash;
}

vector<string> handleFile(string nameFile)
{
	vector<string> text_file;
	text_file.clear();
	string s;
	string file_name = "./" + nameFile + ".basu";
	ifstream inFile(file_name);
	if (inFile.is_open()) {
		while (getline (inFile, s))
		{
			text_file.push_back(s);
		}
		inFile.close();
	}
	else
		std::cout << "Unable to open file";


	return text_file;
}

string to_upper(string data)
{
	// convert string to upper case
	for_each(data.begin(), data.end(), [](char& c) { c = ::toupper(c); });
	return data;
}

string to_lower(string data)
{
	// convert string to upper case
	for_each(data.begin(), data.end(), [](char& c) { c = ::tolower(c); });
	return data;
}

vector<string> removeDupWord(string str)
{
	vector<string> removedDupword;
	string word = "";
	for (char x : str)
	{
		if (x == ' ')
		{
			removedDupword.push_back(word);
			word = "";
		}
		else
		{
			word = word + x;
		}
	}
	removedDupword.push_back(word);
	return removedDupword;
}

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
	vector<Student> Data;
};

vector<Class> Database;


void SelectClass(string classname)
{
	int i = 0;
	int selected;
	int flag = 0;
	for (Class x : Database)
	{
		if (x.ClassName == classname)
		{
			index_selected_class = i;
			flag = 1;
			break;
		}
		else if (classname == "none")
		{
			index_selected_class = -1;
			break;
		}
		i += 1;
	}
}

void AddClass(string file_name)
{
	int i = 2;
	Class add;
	Student student;
	int number_student;
	int check_is_not_exist = 0;
	vector<string> v = handleFile(file_name);
	for (Class x : Database)
	{
		if (x.ClassName == v[0])
		{
			check_is_not_exist = 1;
			break;
		}
	}
	if (!check_is_not_exist)
	{
		add.ClassName = v[0];
		number_student = stoi(v[1]);
		add.Capacity = number_student;
		while (i < number_student + 2)
		{
			Date date;
			student.Firstname = removeDupWord(v[i])[0];
			student.Lastname = removeDupWord(v[i])[1];
			date.Year = stoi(split_with_slash(removeDupWord(v[i])[2])[0]);
			date.Month = stoi(split_with_slash(removeDupWord(v[i])[2])[1]);
			date.Day = stoi(split_with_slash(removeDupWord(v[i])[2])[2]);
			student.Birthday = date;
			student.Grade = stof(removeDupWord(v[i])[3]);
			student.ID = stoi(removeDupWord(v[i])[4]);
			add.Data.push_back(student);
			i += 1;
		}
		Database.push_back(add);
	}
}

void RemoveClass(string classname)
{
	int remove_data_index = 0;
	int i = 0;
	while (i < Database.size())
	{
		if (Database[i].ClassName == classname)
		{
			remove_data_index = i;
			break;
		}
		i += 1;
	}
	Database.erase(Database.begin() + remove_data_index);
}

void AddStudent(string fullname, Date date, unsigned long long int Id, float grade)
{
	int i = 0;
	string first_name = "";
	string last_name = "";
	for (char x : fullname)
	{
		if (i < 5)
			first_name += x;
		else
			last_name += x;
		i += 1;
	}
	Student student;
	student.Firstname = first_name;
	student.Lastname = last_name;
	student.Birthday = date;
	student.Grade = grade;
	student.ID = Id;
	Database[index_selected_class].Capacity += 1;
	Database[index_selected_class].Data.push_back(student);
}

void RemoveStudent(unsigned long long int ID_selected)
{
	int i = 0;
	int removed_student = 0;
	for (Student x : Database[index_selected_class].Data)
	{
		if (x.ID == ID_selected)
			removed_student = i;
		i += 1;
	}
	Database[index_selected_class].Data.erase(Database[index_selected_class].Data.begin() + removed_student);
}

void Search(unsigned long long int ID_search)
{
	if (index_selected_class != -1)
	{
		for (Student x : Database[index_selected_class].Data)
		{
			if (x.ID == ID_search)
			{

				std::cout << setw(12) << left << "Firstname" << setw(12) << left << "Lastname" << setw(12) << left << "ID" << setw(12) << left << "Birthday" << "Grade" << endl;
				std::cout << setw(12) << left << x.Firstname << setw(12) << left << x.Lastname << setw(12) << left << x.ID << setw(12) << left << to_string(x.Birthday.Year) + "/" + to_string(x.Birthday.Month) + "/" + to_string(x.Birthday.Day) << x.Grade << endl;
				break;
			}
		}
	}
	else
	{
		for (Class x : Database)
		{
			for (Student y : x.Data)
			{
				if (y.ID == ID_search)
				{
					std::cout << setw(12) << left << "Firstname" << setw(12) << left << "Lastname" << setw(12) << left << "ID" << setw(12) << left << "Birthday" << "Grade" << endl;
					std::cout << setw(12) << left << y.Firstname << setw(12) << left << y.Lastname << setw(12) << left << y.ID << setw(12) << left << to_string(y.Birthday.Year) + "/" + to_string(y.Birthday.Month) + "/" + to_string(y.Birthday.Day) << y.Grade << endl;
				}
			}
		}
	}
}

void Search(string firstname, string lastname)
{
	if (index_selected_class != -1)
	{
		for (Student x : Database[index_selected_class].Data)
		{
			if (x.Firstname == firstname && x.Lastname == lastname)
			{
				std::cout << setw(12) << left << "Firstname" << setw(12) << left << "Lastname" << setw(12) << left << "ID" << setw(12) << left << "Birthday" << "Grade" << endl;
				std::cout << setw(12) << left << x.Firstname << setw(12) << left << x.Lastname << setw(12) << left << x.ID << setw(12) << left << to_string(x.Birthday.Year) + "/" + to_string(x.Birthday.Month) + "/" + to_string(x.Birthday.Day) << x.Grade << endl;
				break;
			}
		}
	}
	else
	{
		for (Class x : Database)
		{
			for (Student y : x.Data)
			{
				if (y.Firstname == firstname && y.Lastname == lastname)
				{
					std::cout << setw(12) << left << "Firstname" << setw(12) << left << "Lastname" << setw(12) << left << "ID" << setw(12) << left << "Birthday" << "Grade" << endl;
					std::cout << setw(12) << left << y.Firstname << setw(12) << left << y.Lastname << setw(12) << left << y.ID << setw(12) << left << to_string(y.Birthday.Year) + "/" + to_string(y.Birthday.Month) + "/" + to_string(y.Birthday.Day) << y.Grade << endl;
				}
			}
		}
	}
}

void ShowClass()
{
	std::cout << setw(12) << left << "Firstname" << setw(12) << left << "Lastname" << setw(12) << left << "ID" << setw(12) << left << "Birthday" << "Grade" << endl;
	for (Student x : Database[index_selected_class].Data)
	{
		std::cout << setw(12) << left << x.Firstname << setw(12) << left << x.Lastname << setw(12) << left << x.ID << setw(12) << left << to_string(x.Birthday.Year) + "/" + to_string(x.Birthday.Month) + "/" + to_string(x.Birthday.Day) << x.Grade << endl;
	}
}

void ShowAll()
{
	for (Class x : Database)
	{
		std::cout << setw(12) << left << "Classname:" << x.ClassName << endl;
		std::cout << setw(12) << left << "Firstname" << setw(12) << left << "Lastname" << setw(12) << left << "ID" << setw(12) << left << "Birthday" << "Grade" << endl;
		for (Student y : x.Data)
		{
			std::cout << setw(12) << left << y.Firstname << setw(12) << left << y.Lastname << setw(12) << left << y.ID << setw(12) << left << to_string(y.Birthday.Year) + "/" + to_string(y.Birthday.Month) + "/" + to_string(y.Birthday.Day) << y.Grade << endl;
		}
	}
}

void SortByName()
{
	if (index_selected_class != -1)
	{
		for (int i = 0; i < Database[index_selected_class].Data.size() - 1; i++)
		{
			for (int j = 0; j < Database[index_selected_class].Data.size() - i - 1; j++)
			{
				Student flag;
				string f1 = Database[index_selected_class].Data[j].Firstname;
				string f2 = Database[index_selected_class].Data[j + 1].Firstname;
				for (int k = 0; k < 5; k++)
				{
					if (f1[k] > f2[k])
					{
						flag = Database[index_selected_class].Data[j];
						Database[index_selected_class].Data[j] = Database[index_selected_class].Data[j + 1];
						Database[index_selected_class].Data[j + 1] = flag;
						break;
					}
					else if (f1[k] < f2[k])
						break;
				}
			}
		}
	}
	else
	{
		for (int l = 0; l  < Database.size(); l ++)
		{
			for (int i = 0; i < Database[l].Data.size() - 1; i++)
			{
				for (int j = 0; j < Database[l].Data.size() - i - 1; j++)
				{
					Student flag;
					string f1 = Database[l].Data[j].Firstname;
					string f2 = Database[l].Data[j + 1].Firstname;
					for (int k = 0; k < 5; k++)
					{
						if (f1[k] > f2[k])
						{
							flag = Database[l].Data[j];
							Database[l].Data[j] = Database[l].Data[j + 1];
							Database[l].Data[j + 1] = flag;
							break;
						}
						else if (f1[k] < f2[k])
							break;
					}
				}
			}
		}
	}
}

void SortByID()
{
	if (index_selected_class != -1)
	{
		for (int i = 0; i < Database[index_selected_class].Data.size() - 1; i++)
		{
			for (int j = 0; j < Database[index_selected_class].Data.size() - i - 1; j++)
			{
				Student flag;
				unsigned long long int f1 = Database[index_selected_class].Data[j].ID;
				unsigned long long int f2 = Database[index_selected_class].Data[j + 1].ID;
				if (f1 > f2)
				{
					flag = Database[index_selected_class].Data[j];
					Database[index_selected_class].Data[j] = Database[index_selected_class].Data[j + 1];
					Database[index_selected_class].Data[j + 1] = flag;
				}
			}
		}
	}
	else
	{
		for (int l = 0; l < Database.size(); l++)
		{
			for (int i = 0; i < Database[l].Data.size() - 1; i++)
			{
				for (int j = 0; j < Database[l].Data.size() - i - 1; j++)
				{
					Student flag;
					unsigned long long int f1 = Database[l].Data[j].ID;
					unsigned long long int f2 = Database[l].Data[j + 1].ID;
					if (f1 > f2)
					{
						flag = Database[l].Data[j];
						Database[l].Data[j] = Database[l].Data[j + 1];
						Database[l].Data[j + 1] = flag;
					}
				}
			}
		}
	}
}

void Save()
{
	int i = 1;
	for (Class x : Database)
	{
		string file_name = "./L" + to_string(i) + ".basu";
		ofstream myfile;
		myfile.open(file_name);
		myfile << x.ClassName << endl;
		myfile << to_string(x.Capacity) << endl;
		for (Student y : x.Data)
		{
			myfile << y.Firstname << " " << y.Lastname << " " << to_string(y.Birthday.Year) << "/" << to_string(y.Birthday.Month) << "/" << to_string(y.Birthday.Day) << " " << to_string(y.Grade) << " " << to_string(y.ID) << endl;
		}
		i += 1;
		myfile.close();
	}
}

void Rank()
{
	int count_A = 0;
	int count_B = 0;
	int count_C = 0;
	int count_D = 0;
	int count_E = 0;
	for (Student x : Database[index_selected_class].Data)
	{
		if (x.Grade > 18)
			count_A += 1;
		else if (x.Grade > 15)
			count_B += 1;
		else if (x.Grade > 12)
			count_C += 1;
		else if (x.Grade > 10)
			count_D += 1;
		else if (x.Grade < 10)
			count_E += 1;
	}
	std::cout << "count student with grade 'A' : " << count_A << endl;
	std::cout << "count student with grade 'B' : " << count_B << endl;
	std::cout << "count student with grade 'C' : " << count_C << endl;
	std::cout << "count student with grade 'D' : " << count_D << endl;
	std::cout << "count student with grade 'E' : " << count_E << endl;
}

void ShowFilename()
{
	int i = 1;
	while (true)
	{
		ifstream newFile("./L" + to_string(i) + ".basu");
		if (newFile.is_open())
			std::cout << "L" + to_string(i) << endl;
		else
			break;
		i += 1;
	}
}

void Help()
{
	std::cout << "This item is help for you to use My program." << endl;
	std::cout << "1. You can select class from exist classes with 'basu select class <Class name>'" << endl;
	std::cout << "	We have two option for select:" << endl;
	std::cout << "	a. none  ---> with this item you are free to use Database without select class." << endl;
	std::cout << "	b. class name  ---> with this item you select class to use for another order." << endl;
	std::cout << "2. You can Add class to exist classes with 'basu Add class <file_name>'" << endl;
	std::cout << "	You can show all file name with use 'basu show Filename'" << endl;
	std::cout << "3. You can Remove class from exist classes with 'basu remove class <Class name>'" << endl;
	std::cout << "4. You can add student to selected classe with 'basu add student <fullname birthday Id grade>'" << endl;
	std::cout << "	** if you dont selected class you can't add student**" << endl;
	std::cout << "5. You can remove student from selected classe with 'basu remove student <id>'" << endl;
	std::cout << "6. We have two options for search" << endl;
	std::cout << "	a. search in selected class with 'basu search <Id or fullname>'" << endl;
	std::cout << "	b. search in all class with 'basu search <Id or fullname>'" << endl;
	std::cout << "7. You can show all class from exist classes with 'basu show'" << endl;
	std::cout << "8. You can show a class from exist classes with 'basu show <Class name>'" << endl;
	std::cout << "9. You can sort selected class by name 'basu sort name'" << endl;
	std::cout << "10. You can sort selected class by id 'basu sort id'" << endl;
	std::cout << "11. You can save changed in file names L1, L2, L3, L4, ... with 'basu save'" << endl;
	std::cout << "12. You can exit from program with 'basu exit'" << endl;
	std::cout << "13. You can see student's rank in selected class 'basu rank'" << endl;
	std::cout << "14. You can go to help page 'basu help'" << endl;
}

void Start()
{
	string input;
	int flag_sel_class = 0;
	while (true)
	{
		getline(cin, input);
		vector<string> removed = removeDupWord(input);
		if (removed.size() == 1 && to_upper(removed[0]) == "EXIT")
		{
			break;
		}
		else if (removed.size() == 4 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "ADD" && to_upper(removed[2]) == "CLASS")
		{
			AddClass(removed[3]);
		}
		else if (removed.size() == 4 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "REMOVE" && to_upper(removed[2]) == "CLASS")
		{
			RemoveClass(removed[3]);
		}
		else if (removed.size() == 4 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "REMOVE" && to_upper(removed[2]) == "STUDENT")
		{
			RemoveStudent(stoll(removed[3]));
		}
		else if (removed.size() == 7 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "ADD" && to_upper(removed[2]) == "STUDENT")
		{
			if (flag_sel_class)
			{
				if (removed[3].size() == 12 && removed[4].size() < 11 && removed[5].size() == 10 && removed[6].size() < 6)
				{
					Date d1;
					d1.Year = stoi(split_with_slash(removed[4])[0]);
					d1.Month = stoi(split_with_slash(removed[4])[1]);
					d1.Day = stoi(split_with_slash(removed[4])[2]);
					AddStudent(removed[3], d1, stoll(removed[5]), stof(removed[6]));
				}
				else
				{
					cout << "Your input is invalid! try again" << endl;
				}
			}
			else
				std::cout << "please select a class !" << endl << endl;
		}
		else if (removed.size() == 4 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "SELECT" && to_upper(removed[2]) == "CLASS")
		{
			flag_sel_class = 1;
			SelectClass(removed[3]);
		}
		else if (removed.size() == 3 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "SELECT" && to_upper(removed[2]) == "NONE")
		{
			flag_sel_class = 0;
			SelectClass("none");
		}
		else if (removed.size() == 3 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "SEARCH")
		{
			if (removed[2].size() == 10)
				Search(stoll(removed[2]));
			else
			{
				int i = 0;
				string first_name = "";
				string last_name = "";
				for (char x : removed[2])
				{
					if (i < 5)
						first_name += x;
					else
						last_name += x;
					i += 1;
				}
				Search(first_name, last_name);
			}
		}
		else if (removed.size() == 2 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "SHOW")
		{
				ShowAll();
		}
		else if(removed.size() == 3 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "SHOW")
		{
			SelectClass(removed[2]);
			ShowClass();
			index_selected_class = -1;
		}
		else if (removed.size() == 3 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "SHOW" && removed[2] == "Filename")
		{
			ShowFilename();
		}
		else if (removed.size() == 3 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "SORT" && to_upper(removed[2]) == "NAME")
		{
			SortByName();
		}
		else if (removed.size() == 3 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "SORT" && to_upper(removed[2]) == "ID")
		{
			SortByID();
		}
		else if (removed.size() == 2 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "SAVE")
		{
			Save();
		}
		else if (removed.size() == 2 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "HELP")
		{
			Help();
		}
		else if (removed.size() == 2 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "RANK")
		{
			if (flag_sel_class)
			{
				Rank();
			}
			else
				std::cout << "please select a class !" << endl << endl;
		}
		else if (removed.size() == 3 && to_upper(removed[0]) == "BASU" && to_upper(removed[1]) == "SHOW" && removed[2] == "Filename")
		{
			ShowFilename();
		}
		else
			std::cout << "Input Invalid ... " << endl;
	}
}

int main()
{
	Start();
	return 0;
}
