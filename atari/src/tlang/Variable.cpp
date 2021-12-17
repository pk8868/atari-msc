#include "TeaLang.hpp"


namespace tLang {
	sf::Color Variable::rgba() {
		if (this->value.length() == 6) {
			return sf::Color((uint32_t)strtol(this->value.substr(0, 6).c_str(), NULL, 16));
		}
		else if (this->value.length() == 8) {
			return sf::Color((uint32_t)strtol(this->value.substr(0, 8).c_str(), NULL, 16));
		}
		return sf::Color();
	}

	sf::Vector2f Variable::v2f() {
		std::string v1 = "";

		std::string v2 = "";
		if (this->value.length() > 0) {
			size_t eqPos = this->value.find(',');
			// finding ',' in string
			if (eqPos != std::string::npos) {

				v1 = this->value.substr(0, eqPos);
				v2 = this->value.substr(eqPos + 1, this->value.size() - (eqPos + 1));
			}
		}

		return sf::Vector2f((float)atof(v1.c_str()), (float)atof(v2.c_str()));
	}

	int	Variable::i32() {
		return atoi(this->value.c_str());
	}

	long Variable::i64() {
		return atol(this->value.c_str());
	}

	float Variable::fp32() {
		return (float)atof(this->value.c_str());
	}

	double Variable::fp64() {
		return atof(this->value.c_str());
	}
}