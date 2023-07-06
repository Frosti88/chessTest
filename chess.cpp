#include "chess.h"

chess::chess() {

}

bool chess::play() {
	this->print();
	return false;
}

void chess::print() {
	piece pieces[32];
	for (int idx = 0; idx < 32; idx++) {
		piece newPiece;
		newPiece.id = this->getID(this->getPiece(this->board[idx]));
		newPiece.pos = this->get_pos(this->board[idx]);
		pieces[idx] = newPiece;
	}

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {

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
	return piece;
}

chess::~chess() {

}