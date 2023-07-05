#include "chess.h"

chess::chess() {

}

bool chess::play() {

}

void chess::print() {

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