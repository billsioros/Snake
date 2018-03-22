//This is the main.cpp File:

#include "Game.h"
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	srand(time(NULL));
	Game G;
	G.run();
	
	return 0;
}
