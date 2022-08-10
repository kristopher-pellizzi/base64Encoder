#include "BlockConverter.h"

BlockConverter& BlockConverter::getInstance(){
	static BlockConverter instance;

	return instance;
}


BlockConverter::BlockConverter(){
	init();
}


char BlockConverter::getEncodeMapping(unsigned char k){
	auto ret = _encoderMap.find(k);

	if(ret == _encoderMap.end()){
		exit_error("Mapping not found. Critical error. Encoding will be aborted.");
	}

	return ret->second;
}


unsigned char BlockConverter::getDecodeMapping(char k){
	auto ret = _decoderMap.find(k);

	strstream err;

	err 
		<< "Mapping not found for character '" << k << "'. Critical error. Decoding will be aborted." << endl
		<< "Be sure to use argument -p to specify which is the padding character, if it differs from '='." << endl
		<< "Also, there must be no spaces in the strings/files to be decoded." << endl;
	if(ret == _decoderMap.end()){
		exit_error(err.str());
	}

	return ret->second;
}


void BlockConverter::init(){
	
	// Populate _encoderMap

	ENC_PAIR( 0, 'A');
	ENC_PAIR( 1, 'B');
	ENC_PAIR( 2, 'C');
	ENC_PAIR( 3, 'D');
	ENC_PAIR( 4, 'E');
	ENC_PAIR( 5, 'F');
	ENC_PAIR( 6, 'G');
	ENC_PAIR( 7, 'H');
	ENC_PAIR( 8, 'I');
	ENC_PAIR( 9, 'J');
	ENC_PAIR(10, 'K');
	ENC_PAIR(11, 'L');
	ENC_PAIR(12, 'M');
	ENC_PAIR(13, 'N');
	ENC_PAIR(14, 'O');
	ENC_PAIR(15, 'P');
	ENC_PAIR(16, 'Q');
	ENC_PAIR(17, 'R');
	ENC_PAIR(18, 'S');
	ENC_PAIR(19, 'T');
	ENC_PAIR(20, 'U');
	ENC_PAIR(21, 'V');
	ENC_PAIR(22, 'W');
	ENC_PAIR(23, 'X');
	ENC_PAIR(24, 'Y');
	ENC_PAIR(25, 'Z');
	ENC_PAIR(26, 'a');
	ENC_PAIR(27, 'b');
	ENC_PAIR(28, 'c');
	ENC_PAIR(29, 'd');
	ENC_PAIR(30, 'e');
	ENC_PAIR(31, 'f');
	ENC_PAIR(32, 'g');
	ENC_PAIR(33, 'h');
	ENC_PAIR(34, 'i');
	ENC_PAIR(35, 'j');
	ENC_PAIR(36, 'k');
	ENC_PAIR(37, 'l');
	ENC_PAIR(38, 'm');
	ENC_PAIR(39, 'n');
	ENC_PAIR(40, 'o');
	ENC_PAIR(41, 'p');
	ENC_PAIR(42, 'q');
	ENC_PAIR(43, 'r');
	ENC_PAIR(44, 's');
	ENC_PAIR(45, 't');
	ENC_PAIR(46, 'u');
	ENC_PAIR(47, 'v');
	ENC_PAIR(48, 'w');
	ENC_PAIR(49, 'x');
	ENC_PAIR(50, 'y');
	ENC_PAIR(51, 'z');
	ENC_PAIR(52, '0');
	ENC_PAIR(53, '1');
	ENC_PAIR(54, '2');
	ENC_PAIR(55, '3');
	ENC_PAIR(56, '4');
	ENC_PAIR(57, '5');
	ENC_PAIR(58, '6');
	ENC_PAIR(59, '7');
	ENC_PAIR(60, '8');
	ENC_PAIR(61, '9');
	ENC_PAIR(62, '+');
	ENC_PAIR(63, '/');


	// Populate _decoderMap

	DEC_PAIR('A',  0);
	DEC_PAIR('B',  1);
	DEC_PAIR('C',  2);
	DEC_PAIR('D',  3);
	DEC_PAIR('E',  4);
	DEC_PAIR('F',  5);
	DEC_PAIR('G',  6);
	DEC_PAIR('H',  7);
	DEC_PAIR('I',  8);
	DEC_PAIR('J',  9);
	DEC_PAIR('K', 10);
	DEC_PAIR('L', 11);
	DEC_PAIR('M', 12);
	DEC_PAIR('N', 13);
	DEC_PAIR('O', 14);
	DEC_PAIR('P', 15);
	DEC_PAIR('Q', 16);
	DEC_PAIR('R', 17);
	DEC_PAIR('S', 18);
	DEC_PAIR('T', 19);
	DEC_PAIR('U', 20);
	DEC_PAIR('V', 21);
	DEC_PAIR('W', 22);
	DEC_PAIR('X', 23);
	DEC_PAIR('Y', 24);
	DEC_PAIR('Z', 25);
	DEC_PAIR('a', 26);
	DEC_PAIR('b', 27);
	DEC_PAIR('c', 28);
	DEC_PAIR('d', 29);
	DEC_PAIR('e', 30);
	DEC_PAIR('f', 31);
	DEC_PAIR('g', 32);
	DEC_PAIR('h', 33);
	DEC_PAIR('i', 34);
	DEC_PAIR('j', 35);
	DEC_PAIR('k', 36);
	DEC_PAIR('l', 37);
	DEC_PAIR('m', 38);
	DEC_PAIR('n', 39);
	DEC_PAIR('o', 40);
	DEC_PAIR('p', 41);
	DEC_PAIR('q', 42);
	DEC_PAIR('r', 43);
	DEC_PAIR('s', 44);
	DEC_PAIR('t', 45);
	DEC_PAIR('u', 46);
	DEC_PAIR('v', 47);
	DEC_PAIR('w', 48);
	DEC_PAIR('x', 49);
	DEC_PAIR('y', 50);
	DEC_PAIR('z', 51);
	DEC_PAIR('0', 52);
	DEC_PAIR('1', 53);
	DEC_PAIR('2', 54);
	DEC_PAIR('3', 55);
	DEC_PAIR('4', 56);
	DEC_PAIR('5', 57);
	DEC_PAIR('6', 58);
	DEC_PAIR('7', 59);
	DEC_PAIR('8', 60);
	DEC_PAIR('9', 61);
	DEC_PAIR('+', 62);
	DEC_PAIR('/', 63);
}