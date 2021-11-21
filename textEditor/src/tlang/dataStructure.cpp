#include "TeaLang.hpp"



namespace tLang {
	DataStructure::DataStructure() {
		id = "";
	}
	DataStructure::DataStructure(const std::string& id, int maxSize) {
		this->id = id;

		this->data.reserve(maxSize);
		this->data.clear();
	}


	Variable* DataStructure::variable(const std::string& id) {
		for (int i = 0; i < (int)data.size(); i++) {
			if (data[i].key == id)
				return &data[i];
		}
		return nullptr;
	}

	Variable* DataStructure::variable(int id) {
		if (id >= 0 && id < (int)data.size()) {
			return &data[id];
		}
		return nullptr;
	}


	void DataStructure::addVariable(const std::string& name, const std::string& value) {
		// create Variable at the end
		data.emplace_back(name, value);
	}

	Variable* DataStructure::operator[](const std::string& id) {
		return variable(id);
	}

	Variable* DataStructure::operator[](int id) {
		return variable(id);
	}

	void DataStructure::operator<<(const Variable& variable) {
		data.push_back(variable);
	}

	void DataStructure::operator<<(const Variable&& variable) {
		data.push_back(variable);
	}
}