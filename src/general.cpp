//This is the General.cpp File:
//General Purpose Functions Implementations

#include "general.h"
#include <sstream>
#include <vector>
#include <cctype>
#include <iostream>
#include <cstdlib>

using namespace std;

//Float Functions:
string Float::toString(const float target)
{
	stringstream stream;
	stream.setf(ios::fixed, ios::floatfield);
	stream.precision(2);
	stream << target;
	return stream.str();
}

bool Float::aSi(const string target)
{
	istringstream strstrm(target); //initialize the stream's buffer with the given string
	float num;

	//Stringstream fails -> The target was not of type float
	strstrm >> skipws >> num;
	return strstrm.eof() && !strstrm.fail();
}

//Integer Functions:
string Integer::toString(const int target)
{
	stringstream stream;
	stream << target;
	return stream.str();
}

bool Integer::aSi(const string& target)
{
	istringstream strstrm(target); //initialize the stream's buffer with the given string
	int num;

	//Stringstream fails -> The target was not of type int
	strstrm >> skipws >> num;
	return strstrm.eof() && !strstrm.fail();
}

int Integer::max(int a, int b) {
	if (a > b) return a;
	else return b;
}

int Integer::RandomBetween(const int min, const int max) { return (min + (rand() % (max - min + 1))); }

//String Functions:
string String::tolower(const string& target)
{
	string lowerCaseStr;
	for (unsigned int i = 0; i < target.length(); i++) {
		if (target[i] >= 'A' && target[i] <= 'Z')
			lowerCaseStr += std::tolower(target[i]);
		else
			lowerCaseStr += target[i];
	}

	return lowerCaseStr;
}

//Counts the instances of the given delemeter in the given string
unsigned int String::instancesOf(const char del, const string& str)
{
	unsigned int counter = 0;
	const unsigned int length = str.length();

	for (unsigned int i = 0; i <= length; ++i) {
		if (str[i] == del) counter++;
	}

	return counter;
}

//File & Fstream Functions:
void File::putbackStr(string& target, ifstream& file)
{
	const unsigned int length = target.size();
	file.putback('\n');
	for (int i = length - 1; i >= 0; i--) file.putback(target[i]);
}

void File::swapNames(const char* const filenameA, const char* const filenameB)
{
	rename(filenameA, "temp.dat");		//A     ->    Temp
	rename(filenameB, filenameA);		//B     ->    A
	rename("temp.dat", filenameB);		//Temp  ->    B
}

//Other Functions:
void Other::clrscrn()
{
#ifdef __linux__
	system("clear");
#else
	system("cls");
#endif
}