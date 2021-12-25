#include "pch.h"
#include "Interpreter.hpp"


void Interpreter::pParse(const std::string& code, SetPList& r_setList){
	SetPrecursor currentSet{};

	ParsingStatus status{false};

	int oldPosition;
	int currentPosition = 0;
	while (currentPosition < (code.length() - 1)) {

		oldPosition = currentPosition;

		// repeat
		if (status.insideSpecialCommand) {
			// ustawienie pozycji otwierajacego nawiasu kwadratowego
			size_t leftBracketPos = getLeftBracketPos(code, oldPosition);

			if (leftBracketPos < 0)
				break;

			// ustawienie pozycji zamykajacego nawiasu kwadratowego
			currentPosition = getRightBracketPos(code, leftBracketPos);

			if (currentPosition < 0)
				break;

			// znalezienie liczby powtórzeñ
			currentSet.repeat = pGetRepeatNumber(code.substr(oldPosition,
													leftBracketPos - oldPosition) + " ");

			// wyciêcie kodu miêdzy nawiasami kwadratowymi
			currentSet.code = code.substr(leftBracketPos + 1, currentPosition - (leftBracketPos + 1));

			status.insideSpecialCommand = false;
			currentPosition++; // przejscie za znak ]
		}

		// zwyk³y kod
		else {
			// jesli nie ma repeat to do konca jest zwykly instruction set
			if (code.find("REPEAT", oldPosition) == std::string::npos)
				currentPosition = (int)code.length() - 1;
			else {
				currentPosition = (int)code.find("REPEAT", oldPosition);

				status.specialCommand = ParsingStatus::Repeat;
			}

			if (code.find("ASK", oldPosition) < currentPosition) {
				currentPosition = (int)code.find("ASK", oldPosition);
				status.specialCommand = ParsingStatus::Ask;
			}

			// wyciêcie kodu do REPEAT
			currentSet.code = code.substr(oldPosition, size_t(currentPosition - oldPosition));


			status.insideSpecialCommand = true;
		}

		pDeleteSpaces(currentSet.code);

		if (!ifEmptyString(currentSet.code))
			r_setList.push_back(currentSet);

		// ustawienie wszystkiego na defaultowe
		currentSet = SetPrecursor{};
	}

}

// prawdopodobnie do zoptymalizowania
int Interpreter::pGetRepeatNumber(const std::string& code) {
	if (code.length() > 7)
		return atoi(code.substr(7, code.length() - 7).c_str());

	return 1;
}

int Interpreter::getLeftBracketPos(const std::string& string, uint32_t startPos) {
	if (string.find('[', startPos) == std::string::npos) {
		m_list.emplace_back(ErrorCode::MissingLeftBracket, "nie znaleziono znaku [");
		return -1;
	}
		
	return string.find('[', startPos);
}

int Interpreter::getRightBracketPos(const std::string& string, uint32_t leftBracket) {
	// znalezienie zamkniecia repeat'a
	if (string.find(']', leftBracket) == std::string::npos) {
		m_list.emplace_back(ErrorCode::MissingRightBracket, "nie znaleziono znaku ]");
		return -1;
	}

	uint32_t currentPos = leftBracket + 1;
	while (currentPos < string.size()) {
		// jesli jest lewy nawias wewnatrz kodu przejdz do nastepnego nawiasu
		if (string.find('[', currentPos) != std::string::npos) {
			currentPos = string.find(']', currentPos) + 1;
		}
		else {
			// brakuje nawiasu zamykajacego
			if (string.find(']', currentPos) == std::string::npos)
				break;
			return string.find(']', currentPos);
		}
	}

	m_list.emplace_back(ErrorCode::MissingRightBracket, "nie znaleziono znaku ]");

	return -1;	
}