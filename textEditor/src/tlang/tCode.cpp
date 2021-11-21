#include "TeaLang.hpp"

namespace tLang {
	tCode::tCode() {
		dStucture.resize(0);
	}

	tCode::tCode(bool loadFMem, const std::string& code) {
		interpret(code);
	}

	tCode::tCode(const std::string& filename) {
		std::ifstream stream;

		stream.open(filename);

		if (!stream.good()) {
			stream.close();
			throw std::runtime_error("tCode - Couldn't open " + filename);
		}
		else {
			std::string code;
			std::string line;

			while (std::getline(stream, line)) { code += line; code += '\n'; }

			stream.close();

			interpret(code);
		}

	}

	tCode::~tCode() {
		dStucture.clear();
	}

	void tCode::addDataStructure(DataStructure& structure) {
		int getId = groupExists(structure.id);

		if (getId < 0) {
			dStucture.push_back(structure);
		}
		else {
			for (int i = 0; i < (int)structure.data.size(); i++) {
				bool replace = false;
				for (int j = 0; j < (int)dStucture[getId].data.size(); j++) {
					if (structure.data[i].key == dStucture[getId].data[j].key) {
						dStucture[getId].data[j].value = structure.data[i].value;
						replace = true;
					}
				}

				if (!replace)
					dStucture[getId].addVariable(structure.data[i].key, structure.data[i].value);
			}
		}
	}


	DataStructure& tCode::dataGroup(const std::string& id) {
		for (int i = 0; i < (int)dStucture.size(); i++) {
			if (dStucture[i].id == id)
				return dStucture[i];
		}
		return dStucture[0];
	}
	DataStructure& tCode::dataGroup(int id) {
		if (id >= 0 && id < (int)dStucture.size())
			return dStucture[id];

		return dStucture[0];
	}

	DataStructure& tCode::operator[](const std::string& id) {
		return dataGroup(id);
	}

	DataStructure& tCode::operator[](int id) {
		return dataGroup(id);
	}

	void tCode::addFile(const std::string& filename) {
		tLang::tCode l_TCode(filename);

		combineFiles(*this, l_TCode);
	}

	void tCode::addCode(const std::string& code) {
		tLang::tCode l_TCode(1, code);

		combineFiles(*this, l_TCode);
	}
}