#include "chess.h"

chess::chess() {

}

bool chess::play() {
	while (true) {
		std::string com;
		int x = 0;
		int y = 0;
		int nx = 0;
		int ny = 0;
		std::cout << "Enter nothing to keep modifying or done to end modifying" << std::endl;
		std::getline(std::cin, com);
		if (com == "done") {
			break;
		}
		com = "";
		std::cout << "Enter coords for moving" << std::endl;
		while (x < 1 or x > 8) {
			std::cout << "X: ";
			std::cin >> x;
		}
		while (y < 1 or y > 8) {
			std::cout << "Y: ";
			std::cin >> y;
		}
		while (nx < 1 or nx > 8) {
			std::cout << "nX: ";
			std::cin >> nx;
		}
		while (ny < 1 or ny > 8) {
			std::cout << "nY: ";
			std::cin >> ny;
		}
		this->move(x, y, nx, ny);
		this->print();
	}
	return false;
}

void chess::print() {

	char vl = 205;
	char hl = 186;
	char cr = 206;
	char urc = 187;
	char tcr = 203;
	char lcr = 204;
	char rcr = 185;
	char dcr = 202;
	char ulc = 201;
	char dlc = 200;
	char drc = 188;

	piece pieces[32];
	for (int idx = 0; idx < 32; idx++) {
		piece newPiece;
		newPiece.id = this->getID(this->getPiece(this->board[idx]));
		newPiece.pos = this->get_pos(this->board[idx]);
		pieces[idx] = newPiece;
	}
	
	std::cout << ulc;
	for (int i = 0; i < 7; i++) {
		std::cout << vl << vl<< vl << tcr;
	}
	std::cout << vl << vl <<vl << urc;
	for (int y = 1; y < 9; y++) {
		std::cout << std::endl;
		std::cout << hl;
		for (int x = 1; x < 9; x++) {
			uint8_t pos = (x << 4) | y;
			std::string current = "   ";
			for (int idx = 0; idx < 32; idx++) {
				if (pieces[idx].pos == pos) {
					current = pieces[idx].id;
				}
			}
			std::cout << current << hl;
		}
		if (y != 8) {
			std::cout << std::endl;
			std::cout << lcr;
			for (int i = 0; i < 7; i++) {
				std::cout << vl << vl << vl << cr;
			}
			std::cout << vl << vl << vl << rcr;
		}
		else {
			std::cout << std::endl;
			std::cout << dlc;
			for (int i = 0; i < 7; i++) {
				std::cout << vl << vl << vl << dcr;
			}
			std::cout << vl << vl << vl << drc;
		}
	}
}

std::string chess::getID(uint16_t piece) {
	switch (piece) {
	case 0b0001:
		return "WPN";
		break;
	case 0b0010:
		return "WBI";
		break;
	case 0b0011:
		return "WKN";
		break;
	case 0b0100:
		return "WRK";
		break;
	case 0b0101:
		return "WQN";
	case 0b0110:
		return "WKG";
		break;
	case 0b1001:
		return "BPN";
		break;
	case 0b1010:
		return "BBI";
		break;
	case 0b1011:
		return "BKN";
		break;
	case 0b1100:
		return "BRK";
		break;
	case 0b1101:
		return "BQN";
	case 0b1110:
		return "BKG";
		break;
	}
}

uint8_t chess::getPiece(uint16_t piece) {
	return piece >> 12;
}


uint8_t chess::get_pos(uint16_t piece) {
	uint8_t pos = piece >> 4;
	return pos;
}

bool chess::isCaptured(uint16_t piece) {
	uint16_t captured = (piece << 12);
	bool iscap = captured >> 15;
	return iscap;
}

void chess::setPos(int idx, uint8_t pos)
{
	uint16_t piece = this->board[idx];
	uint16_t mask = 0xF00F;
	piece &= mask;
	uint16_t replacement = (pos << 4) & ~mask;
	uint16_t newPiece = piece | replacement;
	this->board[idx] = newPiece;
}

void chess::setCap(int idx)
{
	this->board[idx] = this->board[idx] | 0000000000001111;
}

void chess::move(int x, int y, int newX, int newY)
{
	uint8_t newPos = (newX << 4) | newY;
	uint8_t oldPos = (x << 4) | y;
	for (int idx = 0; idx < 32; idx++) {
		if (this->get_pos(this->board[idx]) == newPos) {
			this->setCap(idx);
		}
		if (this->get_pos(this->board[idx]) == oldPos) {
			this->setPos(idx, newPos);
		}
	}
}

chess::~chess() {

}