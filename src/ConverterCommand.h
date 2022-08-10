#include <iostream>

#include "ConverterImplementation.h"

#ifndef CONVERTERCOMMAND
#define CONVERTERCOMMAND

using std::cout;
using std::endl;

struct ConverterCommand{
	virtual void operator()(istream& input, ostream& output) = 0;
};

#endif //CONVERTERCOMMAND