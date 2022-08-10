#include <fstream>
#include <iostream>

#include "ArgsParser.h"
#include "ConverterOperation.h"
#include "ConverterCommand.h"
#include "ConverterEncodeInteractiveCommand.h"
#include "ConverterEncodeFileCommand.h"
#include "ConverterDecodeCommand.h"

using std::cout;
using std::cerr;
using std::endl;
using std::cin;
using std::string;
using std::getline;
using std::istream;
using std::ostream;
using std::ofstream;
using std::ifstream;
using std::strstream;

static ConverterCommand* getCommand(ConverterOperation op, bool isInteractive){
	static ConverterEncodeInteractiveCommand encodeInteractive;
	static ConverterEncodeFileCommand encodeFile;
	static ConverterDecodeCommand decode;

	if(op == ConverterOperation::DECODE)
		return &decode;

	if(isInteractive)
		return &encodeInteractive;

	return &encodeFile;
}

static void convert(ConverterCommand& cmd, istream& input, ostream& output){
	cmd(input, output);
}

static void writeDelimiter(bool addDelimiters, ostream& output){
	if(addDelimiters)
		output << endl << "=======================";

	output << endl << endl;
}

int main(int argc, char* argv[]){
	bool hasInputFile = false;
	bool hasArgs = false;
	bool hasOutputFile = false;
	bool isInteractive = false;
	bool noPadding = false;
	bool addDelimiters = true;
	ConverterOperation operation = ConverterOperation::ENCODE;
	ConverterCommand* cmd = getCommand(operation, true);
	ostream* output = &cout;
	ofstream ofile;

	ArgsParser argsParser(argc, argv);
	argsParser.parseArgs();

	const Argument& noDelimiterArg = argsParser.getArgument("no-delimiter");
	if(noDelimiterArg.isValid()){
		addDelimiters = false;
	}

	const Argument& decodeArg = argsParser.getArgument("decode");
	if(decodeArg.isValid()){
		operation = ConverterOperation::DECODE;
	}

	const Argument& noPaddingArg = argsParser.getArgument("no-padding");
	if(noPaddingArg.isValid()){
		setPadding('\0');
		noPadding = true;
	}

	const Argument& paddingArg = argsParser.getArgument("padding");
	if(!noPadding && paddingArg.isValid()){
		char* val = paddingArg.getVal();
		string valString(val);
		if(valString.size() != 1){
			recoverable_error("Padding is only 1 character long. Only the first character of the provided string will be used.\nNotice that this may create confusion if it is a base64 character.");
		}

		setPadding(val[0]);
	}

	const Argument& interactiveArg = argsParser.getArgument("interactive");
	if(interactiveArg.isValid()){
		isInteractive = true;
	}

	const Argument& outputArg = argsParser.getArgument("output");
	if(outputArg.isValid()){
		char* filePath = outputArg.getVal();
		#ifdef DEBUG
		cout << "Opened " << filePath << endl;
		#endif
		ofile.open(filePath);
		output = &ofile;
		hasOutputFile = true;
	}

	const Argument& inputArg = argsParser.getArgument("input");
	if(inputArg.isValid()){
		char* filePath = inputArg.getVal();
		ifstream ifile(filePath);
		cmd = getCommand(operation, false);
		convert(*cmd, ifile, *output);
		writeDelimiter(addDelimiters, *output);
		hasInputFile = true;
		ifile.close();
	}

	// Encode positional arguments
	bool stop = false;
	for(int i = 1; !stop; ++i){
		const Argument& posArg = argsParser.getPositionalArgument(i);
		if(posArg.isValid()){
			hasArgs = true;
			char* val = posArg.getVal();
			strstream valStream;
			valStream << val;
			*output << val << endl;
			cmd = getCommand(operation, true);
			convert(*cmd, valStream, *output);
			writeDelimiter(addDelimiters, *output);
		}
		else
			stop = true;
	}

	if(isInteractive || (!hasInputFile && !hasArgs)){
		cout 
			<< "Insert strings to be encoded and press Enter. For each string, its encoding will be printed." << endl
			<< "Just press Enter with an empty string to quit." << endl
			<< "NOTE: newlines (\\n) are not encoded" << endl << endl;

		while(cin.peek() != '\n'){
			cmd = getCommand(operation, true);
			convert(*cmd, cin, *output);
			writeDelimiter(addDelimiters, *output);
			
			if(cin.rdstate() == std::ios_base::failbit){
				cin.clear();
				cin.get();
			}
		}
	}

	if(hasOutputFile)
		ofile.close();

	return 0;
}