#include "ConverterImplementation.h"

static char PADDING_CHAR = '=';

void encodeBuf(unsigned char buf[], unsigned numBytes, unsigned char convBuf[]){
	int j = 0;
	unsigned char curr = 0;
	unsigned shiftAmount = 2;
	unsigned min = numBytes < BUF_SIZE ? numBytes : BUF_SIZE;
	BlockConverter& convTable = BlockConverter::getInstance();

	for(int i = 0; i < min; ++i){
		curr |= buf[i] >> shiftAmount;
		convBuf[j++] = convTable.getEncodeMapping(curr);
		curr = buf[i] << (8 - shiftAmount);
		curr >>= 2;
		shiftAmount += 2;
	}

	convBuf[j++] = convTable.getEncodeMapping(curr);

	/*
	// If the number of passed bytes is not a multiple of 3, then, less then 4 characters will be generated
	// for the encoded string.
	// Optionally, it is possible to fill the remaining bytes in the encoding with a padding character 
	// ('=' by default).
	*/
	for(int i = j; i < BUF_SIZE + 1; ++i)
		convBuf[j++] = PADDING_CHAR;
}

void encode(istream& input, ostream& output, InputFunctor& func){
	unsigned char buf[BUF_SIZE];
	unsigned char convBuf[BUF_SIZE + 2];
	char inputBuffer[INPUT_BUF_SIZE];

	convBuf[BUF_SIZE + 1] = '\0';
	while(func(input, inputBuffer, INPUT_BUF_SIZE) || input.gcount() > 0){
		
		if(!input.good() && !input.eof())
			exit_error("Error while reading from input stream. Aborting...");
		

		std::streamsize charsInBuf = input.gcount();

		for(std::streamsize j = 0; j < charsInBuf;){
			unsigned numBytes;

			for(int i = 0; i < BUF_SIZE && j < charsInBuf; ++i){
				buf[i] = inputBuffer[j++];
				numBytes = i + 1;
			}

			for(int i = numBytes; i < BUF_SIZE; ++i){
				buf[i] = 0;
			}

			encodeBuf(buf, numBytes, convBuf);
			output << convBuf;
		}
	}
}


void encode_file(istream& input, ostream& output){
	static FileInputFunctor func;
	encode(input, output, func);
}


void encode_interactive(istream& input, ostream& output){
	static InteractiveInputFunctor func;
	encode(input, output, func);
}


void decodeBuf(unsigned char buf[], unsigned* numBytes, unsigned char convBuf[]){
	int j = 0;
	unsigned char curr = 0;
	BlockConverter& convTable = BlockConverter::getInstance();
	unsigned maskShift = 2;
	unsigned toRemove = 0;

	if(buf[0] == PADDING_CHAR)
		exit_error("Something went wrong.\nBase64 encoded strings are composed by sequences of groups of 4 characters.\nNone of them can begin with a padding character.");
	curr |= ((unsigned char) convTable.getDecodeMapping(buf[0]) << 2);
	for(int i = 1; i < *numBytes; ++i){
		unsigned char mask = ~((unsigned char) 0xff >> maskShift) >> 2;
		unsigned char decodedChar;

		if(buf[i] == PADDING_CHAR){
			++toRemove;
			decodedChar = 0;
		}
		else{
			decodedChar = convTable.getDecodeMapping(buf[i]);
		}

		curr |= (decodedChar & mask) >> (6 - maskShift);
		convBuf[j++] = curr;
		convBuf[j] = '\0';

		maskShift += 2;
		curr = decodedChar << maskShift;
	}

	*numBytes -= toRemove;
}


static std::streamsize getDecodedBufSize(unsigned numBytes){
	switch(numBytes){
		case 2:
			return 1;
		case 3:
			return 2;
		case 4:
			return 3;
	}

	return -1;
}


void decode(istream& input, ostream& output){
	unsigned char buf[BUF_SIZE + 1];
	unsigned char convBuf[BUF_SIZE + 1];
	char inputBuffer[DECODE_INPUT_BUF_SIZE];

	convBuf[BUF_SIZE] = '\0';
	while(input.get(inputBuffer, DECODE_INPUT_BUF_SIZE)){

		if(!input.good() && !input.eof())
			exit_error("Error while reading from input stream. Aborting...");

		std::streamsize charsInBuf = input.gcount();

		for(std::streamsize j = 0; j < charsInBuf;){
			unsigned numBytes;

			for(int i = 0; i < BUF_SIZE + 1 && j < charsInBuf; ++i){
				buf[i] = inputBuffer[j++];
				numBytes = i + 1;
			}

			decodeBuf(buf, &numBytes, convBuf);
			std::streamsize convBufBytes = getDecodedBufSize(numBytes);
			if(convBufBytes == -1){
				exit_error("Cannot retrieve correct number of decoded bytes for the decoding buffer");
			}
			output.write((char*) convBuf, convBufBytes);
		}
	}
}


void setPadding(const char p){
	PADDING_CHAR = p;
}