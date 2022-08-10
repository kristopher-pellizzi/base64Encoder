#include "ConverterCommand.h"

#ifndef CONVERTERENCODEINTERACTIVECOMMAND
#define CONVERTERENCODEINTERACTIVECOMMAND

struct ConverterEncodeInteractiveCommand : ConverterCommand{
	void operator()(istream& input, ostream& output);
};

#endif //CONVERTERENCODEINTERACTIVECOMMAND