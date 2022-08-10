#include "ConverterCommand.h"

#ifndef CONVERTERENCODEFILECOMMAND
#define CONVERTERENCODEFILECOMMAND

struct ConverterEncodeFileCommand : ConverterCommand{
	void operator()(istream& input, ostream& output);
};

#endif //CONVERTERENCODEFILECOMMAND