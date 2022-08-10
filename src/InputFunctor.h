#include <iostream>

#ifndef INPUTFUNCTOR
#define INPUTFUNCTOR
using std::istream;

struct InputFunctor{
	virtual istream& operator()(istream& input, char* buffer, std::streamsize size) = 0;
};

#endif //INPUTFUNCTOR