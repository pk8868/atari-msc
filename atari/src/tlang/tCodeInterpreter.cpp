#include "TeaLang.hpp"


namespace tLang {
	int tCode::countGroups(const std::string& code) {
		std::stringstream stream(code);

		std::string line;

		int groups = 1;

		while (std::getline(stream, line)) {
			if (line[0] == '{') {
				groups++;
			}
		}

		return groups;
	}


	void tCode::interpret(const std::string& code) {
		dStucture.reserve(countGroups(code));

		std::stringstream stream(code);

		std::string line;

		compilingStatus status{};

		createMainGroup();

		while (std::getline(stream, line)) {

			compile(line, status);

			status.prevLine = line;
		}

		dStucture.shrink_to_fit();

		for (int i = 0; i < (int)dStucture.size(); i++)
			dStucture[i].data.shrink_to_fit();
	}

	void tCode::compile(std::string& line, compilingStatus& status) {
		deleteSpecialChar(line);
		if (line != "") {
			switch (line[0]) {

				// skip if its a comment
			case '#':
				break;

			case '{':
				status.currentGroup = groupExists(status.prevLine);
				if (status.currentGroup == -1)
					status.currentGroup = createGroup(status.prevLine);
				break;

			case '}':
				// switch to main group
				status.currentGroup = 0;
				break;

			default:
				createVariable(line, status);
				break;
			}
		}
	}

	int tCode::createGroup(std::string& id) {
		deleteSpecialCharsAndSpaces(id);
		if (id != "") {
			dStucture.emplace_back(id, 10);
			return int(dStucture.size() - 1);
		}
		// if its a data struct without a name return main data struct id
		return 0;
	}

	int tCode::createMainGroup() {
		dStucture.emplace_back("main", 10);
		return 0;
	}

	void tCode::createVariable(const std::string& line, compilingStatus& status) {
		int eqSpot = (int)line.find('=');

		if (eqSpot != std::string::npos) {
			std::string name = "";
			std::string value = "";

			name = line.substr(0, eqSpot);

			value = line.substr(eqSpot + 1i32, line.size() - (eqSpot));

			deleteSpecialCharsAndSpaces(name);
			deleteSpecialChars(value);

			// if variable exists change the value
			auto variable = dStucture[status.currentGroup][name];

			if (variable) {
				variable->value = value;
			}
			else {
				dStucture[status.currentGroup].addVariable(name, value);
			}
		}
	}

	void tCode::deleteSpecialChar(std::string& id) {
		for (int i = 0; i < (int)id.length(); i++) {
			switch (id[i]) {
			case '\t':
				id.erase(id.begin() + i);
				i--; // go to the previous char
				break;
			}
		}
	}

	void tCode::deleteSpecialChars(std::string& id) {
		for (int i = 0; i < (int)id.length(); i++) {
			switch (id[i]) {
			case '\t':
			case '=':
				id.erase(id.begin() + i);
				i--; // go to the previous char
				break;
			}

			// erase spaces at the start and at the end
			if (i == 0 && id[i] == ' ') {
				id.erase(id.begin());
			}
			else if (i == (int)id.length() - 1 && id[i] == ' ') {
				id.erase(id.begin() + i);
			}
		}
	}

	void tCode::deleteSpecialCharsAndSpaces(std::string& id) {
		for (int i = 0; i < (int)id.length(); i++) {
			switch (id[i]) {
			case '\t':
			case '=':
			case ' ':
				id.erase(id.begin() + i);
				i--; // go to the previous char
				break;
			}
		}
	}

	int tCode::groupExists(const std::string& id) {
		for (int i = 0; i < (int)dStucture.size(); i++) {
			if (dStucture[i].id == id)
				return i;
		}
		return -1;
	}
}