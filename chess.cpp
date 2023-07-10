#include "chess.h"

chess::chess() {

}

bool chess::play() {
	this->parsePGN("1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 {This opening is called the Ruy Lopez}"
		"4. Ba4 Nf6 5. O - O Be7 6. Re1 b5 7. Bb3 d6 8. c3 O - O 9. h3 Nb8 10. d4 Nbd7"
		"11. c4 c6 12. cxb5 axb5 13. Nc3 Bb7 14. Bg5 b4 15. Nb1 h6 16. Bh4 c5 17. dxe5"
		"Nxe4 18. Bxe7 Qxe7 19. exd6 Qf6 20. Nbd2 Nxd6 21. Nc4 Nxc4 22. Bxc4 Nb6"
		"23. Ne5 Rae8 24. Bxf7 + Rxf7 25. Nxf7 Rxe1 + 26. Qxe1 Kxf7 27. Qe3 Qg5 28. Qxg5"
		"hxg5 29. b3 Ke6 30. a3 Kd6 31. axb4 cxb4 32. Ra5 Nd5 33. f3 Bc8 34. Kf2 Bf5"
		"35. Ra7 g6 36. Ra6 + Kc5 37. Ke1 Nf4 38. g3 Nxh3 39. Kd2 Kb5 40. Rd6 Kc5 41. Ra6"
		"Nf2 42. g4 Bd3 43. Re6 1 / 2 - 1 / 2");
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
	return piece;
}

void chess::parsePGN(std::string PGN) {
std::stringstream SPGN(PGN);
	/*std::string segment;
	std::vector<std::string> seglist;
	std::vector<std::string> moveList;

	PGN.erase(std::remove(PGN.begin(), PGN.end(), '\n'), PGN.end());

	while (std::getline(SPGN, segment, ' '))
	{
		seglist.push_back(segment);
	}

	std::string mv = "";
	bool record = false;
	for (std::string moveLine : seglist) {
		if (moveLine.find('.') != std::string::npos) {
			moveList.push_back(mv);
			mv = "";
			record = false;
		}
		mv += moveLine;
	}
	for (std::string move : moveList) {
		std::cout << move << std::endl;
	}*/
	// Split the PGN into individual moves
	std::vector<std::string> moves;
	size_t startPos = 0;
	size_t endPos = PGN.find(' ');

	while (endPos != std::string::npos) {
		std::string move = PGN.substr(startPos, endPos - startPos);
		moves.push_back(move);

		startPos = endPos + 1;
		endPos = PGN.find(' ', startPos);
	}

	// Output each move on a new line
	for (size_t i = 0; i < moves.size(); i++) {
		std::string move = moves[i];

		// Remove any comments within curly braces
		size_t commentPos = move.find('{');
		if (commentPos != std::string::npos) {
			move = move.substr(0, commentPos);
		}

		// Remove any annotations (e.g., +, #)
		size_t annotationPos = move.find_first_of("+#");
		if (annotationPos != std::string::npos) {
			move = move.substr(0, annotationPos);
		}

		// Remove any extraneous spaces
		move.erase(std::remove(move.begin(), move.end(), ' '), move.end());

		if (!move.empty()) {
			std::cout << move << std::endl;
		}
	}
}

chess::~chess() {

}