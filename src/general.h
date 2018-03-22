//This is the General.h File:
//It contains General Purpose Functions

#ifndef GENERAL_H
#define GENERAL_H

#include <string>
#include <fstream>

//Float Functions:
namespace Float {
	std::string toString(const float);
	bool aSi(const std::string target); // target iS a Float
}

//Integer Functions:
namespace Integer {
	std::string toString(const int);
	bool aSi(const std::string& target); // target iS a(n) Integer
	int max(int a, int b);
	int RandomBetween(const int min, const int max);
}

//String Functions:
namespace String {
	std::string tolower(const std::string& target);
	unsigned int instancesOf(const char del, const std::string& str);
}

//File & Fstream Functions:
namespace File {
	void putbackStr(std::string& target, std::ifstream& file);
	void swapNames(const char* const filenameA, const char* const filenameB);
}

//Other Functions:
namespace Other {
	void clrscrn();
}

#endif
