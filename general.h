//This is the General.h File:
//It contains General Purpose Functions

#ifndef GENERAL_H
#define GENERAL_H

#include <string>
#include <fstream>

//Float Functions:
namespace Float {
	const std::string toString(const float);
	const bool aSi(const std::string target); // target iS a Float
}

//Integer Functions:
namespace Integer {
	const std::string toString(const int);
	const bool aSi(const std::string& target); // target iS a(n) Integer
	const int max(int a, int b);
	const int RandomBetween(const int min, const int max);
}

//String Functions:
namespace String {
	const std::string tolower(const std::string& target);
	const unsigned int instancesOf(const char del, const std::string& str);
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