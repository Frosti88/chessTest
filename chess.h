#pragma once
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <sstream>

struct piece {
	std::string id = "";
	uint8_t pos = 0;
};
class chess
{
public:
	chess();

	bool play();

	void print();

	uint8_t get_pos(uint16_t piece);
	uint8_t getPiece(uint16_t piece);
	bool isCaptured(uint16_t piece);

	std::string getID(uint16_t piece);

	~chess();
private:
	//one piece per entry
	//0000  0000  0000  0000
	//piece x     y     captured
	//0001 = white pawn
	//0010 = white bishop
	//0011 = white knight
	//0100 = white rook
	//0101 = white queen
	//0110 = white king
	//1001 = black pawn
	//1010 = black bishop
	//1011 = black knight
	//1100 = black rook
	//1101 = black queen
	//1110 = black king
	uint16_t board[32] = { //white pawns
						   0b0001000100100000,
						   0b0001001000100000,
						   0b0001001100100000,
						   0b0001010000100000,
						   0b0001010100100000,
						   0b0001011000100000,
						   0b0001011100100000,
						   0b0001100000100000,
						   //white bishop
						   0b0010001100010000,
						   0b0010011000010000,
						   //white knight
						   0b0011001000010000,
						   0b0011011100010000,
						   //white rook
						   0b0100000100010000,
						   0b0100100000010000,
						   //white queen
						   0b0101010000010000,
						   //white king
						   0b0110010100010000,
						   //black pawns
						   0b1001000101110000,
						   0b1001001001110000,
						   0b1001001101110000,
						   0b1001010001110000,
						   0b1001010101110000,
						   0b1001011001110000,
						   0b1001011101110000,
						   0b1001100001110000,
						   //black bishop
						   0b1010001110000000,
						   0b1010011010000000,
						   //black knight
						   0b1011001010000000,
						   0b1011011110000000,
						   //black rook
						   0b1100000110000000,
						   0b1100100010000000,
						   //black queen
						   0b1101010010000000,
						   //black king
						   0b1110010110000000
	};
};