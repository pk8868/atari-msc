#include "pch.h"
#include "Interpreter.hpp"


void Interpreter::pParse(const std::string& code, SetPList& r_setList){
	std::string current;

	SetPrecursor currentSet{};

	ParsingStatus status{false};

	int oldPosition;
	int currentPosition = 0;
	while (currentPosition < (code.length() - 1)) {

		oldPosition = currentPosition;

		// repeat
		if (status.insideSpecialCommand) {
			size_t leftBracketPos = 0;

			// znalezienie startu repeat'a
			if (code.find('[', oldPosition) == std::string::npos) {
				m_list.emplace_back(ErrorCode::MissingLeftBracket, "nie znaleziono znaku [");
				break;
			}
			else
				leftBracketPos = code.find('[', oldPosition);

			// znalezienie zamkniecia repeat'a
			if (code.find(']', leftBracketPos) == std::string::npos) {
				m_list.emplace_back(ErrorCode::MissingRightBracket, "nie znaleziono znaku ]");
				break;
			}
			else
				currentPosition = (int)code.find(']', oldPosition);


			// znalezienie liczby powtórzeñ
			currentSet.repeat = pGetRepeatNumber(code.substr(oldPosition,
													leftBracketPos - oldPosition) + " ");

			// wyciêcie kodu miêdzy nawiasami kwadratowymi
			currentSet.code = code.substr(leftBracketPos + 1, (currentPosition) - (leftBracketPos + 1));

			
			status.insideSpecialCommand = false;
			status.specialCommand = ParsingStatus::Repeat;
			currentPosition++; // przejscie za znak ]
		}

		// zwyk³y kod
		else {
			// jesli nie ma repeat to do konca jest zwykly instruction set
			// TODO: liczenie nawiasow kwadratowych w srodku
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