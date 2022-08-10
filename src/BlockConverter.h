#include <map>
#include <cstdlib>
#include <iostream>
#include <strstream>

#include "ANSI_CODES.h"
#include "ErrorHandler.h"

#ifndef BLOCKCONVERTER
#define BLOCKCONVERTER

using std::map;
using std::cerr;
using std::endl;
using std::strstream;

#define ENC_PAIR(k, v) _encoderMap.insert(std::pair<unsigned char, char>(k, v))
#define DEC_PAIR(k, v) _decoderMap.insert(std::pair<char, unsigned char>(k, v))

class BlockConverter{
	private:
		map<unsigned char, char> _encoderMap;
		map<char, unsigned char> _decoderMap;

		void init();
		BlockConverter();

	public:
		BlockConverter(const BlockConverter& other) = delete;
		void operator=(const BlockConverter& other) = delete;

		static BlockConverter& getInstance();

		char getEncodeMapping(unsigned char k);
		unsigned char getDecodeMapping(char k);


};

#endif //BLOCKCONVERTER