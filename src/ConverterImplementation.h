#include <iostream>
#include <strstream>

#include "BlockConverter.h"
#include "InteractiveInputFunctor.h"
#include "FileInputFunctor.h"

#ifndef CONVERTERIMPLEMENTATION
#define CONVERTERIMPLEMENTATION

#define BUF_SIZE 3
#define INPUT_BUF_SIZE 3073
#define DECODE_INPUT_BUF_SIZE 4097

using std::istream;
using std::ostream;
using std::strstream;
using std::cout;
using std::endl;
using std::cin;
using std::string;

void encodeBuf(unsigned char buf[], unsigned numBytes, unsigned char convBuf[]);

void encode(istream& input, ostream& output, InputFunctor& func);

void encode_file(istream& input, ostream& output);

void encode_interactive(istream& input, ostream& output);

void decodeBuf(unsigned char buf[], unsigned numBytes, unsigned char convBuf[]);

void decode(istream& input, ostream& output);

void setPadding(const char p);

#endif //CONVERTERIMPLEMENTATION