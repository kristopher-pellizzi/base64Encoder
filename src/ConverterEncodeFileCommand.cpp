#include "ConverterEncodeFileCommand.h"

void ConverterEncodeFileCommand::operator()(istream& input, ostream& output){
	#ifdef DEBUG
	cout << "Encode_file Command" << endl;
	#endif
	encode_file(input, output);
}