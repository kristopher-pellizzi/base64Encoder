#include "ConverterCommand.h"

#ifndef CONVERTERDECODECOMMAND
#define CONVERTERDECODECOMMAND

struct ConverterDecodeCommand : ConverterCommand{
	void operator()(istream& input, ostream& output);
};

#endif //CONVERTERDECODECOMMAND