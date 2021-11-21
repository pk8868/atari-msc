#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

namespace tLang {

	// tlang Variable
	struct Variable {
		Variable(const std::string& key, const std::string& value)
			: key(key), value(value)
		{

		}

		// sfml types
		sf::Color rgba();
		sf::Vector2f v2f();

		// ints
		int			i32();
		long		i64();

		// floats
		float		fp32();
		double		fp64();

		std::string key = "";
		std::string value = "";
	};

	// string lists
	static int countItems(const std::string& string) {
		int count = 0;
		bool insideItem = false;
		bool waitingforComma = false;
		for (int i = 0; i < (int)string.length(); i++) {
			if (string[i] == '[') {
				if (!insideItem && !waitingforComma)
					insideItem = true;
			}

			else if (string[i] == ']') {
				if (insideItem) {
					waitingforComma = true;
					insideItem = false;
					count++;
				}
			}
			if (string[i] == ',') {
				if (waitingforComma)
					waitingforComma = false;
			}

		}
		return count;
	}

	// add to string list
	static void addToStringList(std::vector<std::string>& list, const std::string& string) {
		int newItems = countItems(string);

		list.reserve(list.capacity() + newItems);

		int lastLeftBracket = 0;
		int countFromLastBracket = 0;
		bool insideBrackets = 0;
		bool waitingForComma = false;

		for (int i = 0; i < (int)string.size(); i++) {
			if (string[i] == '[') {
				if (!waitingForComma) {
					if (!insideBrackets) {
						lastLeftBracket = i;
						countFromLastBracket = 0;
						insideBrackets = true;
					}
					else
						countFromLastBracket++;
				}
			}
			else if (string[i] == ']') {
				if (insideBrackets) {
					insideBrackets = false;
					waitingForComma = true;

					list.push_back(string.substr(size_t(lastLeftBracket) + 1, countFromLastBracket));
					countFromLastBracket = 0;
				}
			}
			if (string[i] == ',') {
				if (waitingForComma)
					waitingForComma = false;
			}
			else
				countFromLastBracket += insideBrackets;
		}
	}

	// add to int list
	static void addToIntList(std::vector<int>& list, const std::string& string) {
		int newItems = countItems(string);

		list.reserve(list.capacity() + newItems);

		int lastLeftBracket = 0;
		int countFromLastBracket = 0;
		bool insideBrackets = 0;
		bool waitingForComma = false;

		for (int i = 0; i < (int)string.size(); i++) {
			if (string[i] == '[') {
				if (!waitingForComma) {
					if (!insideBrackets) {
						lastLeftBracket = i;
						countFromLastBracket = 0;
						insideBrackets = true;
					}
					else
						countFromLastBracket++;
				}
			}
			else if (string[i] == ']') {
				if (insideBrackets) {
					insideBrackets = false;
					waitingForComma = true;

					list.push_back(atoi(string.substr(size_t(lastLeftBracket) + 1, countFromLastBracket).c_str()));
					countFromLastBracket = 0;
				}
			}
			if (string[i] == ',') {
				if (waitingForComma)
					waitingForComma = false;
			}
			else
				countFromLastBracket += insideBrackets;
		}
	}

	// add to float list
	static void addToFloatList(std::vector<float>& list, const std::string& string) {
		int newItems = countItems(string);

		list.reserve(list.capacity() + newItems);

		int lastLeftBracket = 0;
		int countFromLastBracket = 0;
		bool insideBrackets = 0;
		bool waitingForComma = false;

		for (int i = 0; i < (int)string.size(); i++) {
			if (string[i] == '[') {
				if (!waitingForComma) {
					if (!insideBrackets) {
						lastLeftBracket = i;
						countFromLastBracket = 0;
						insideBrackets = true;
					}
					else
						countFromLastBracket++;
				}
			}
			else if (string[i] == ']') {
				if (insideBrackets) {
					insideBrackets = false;
					waitingForComma = true;

					list.push_back((float)atof(string.substr(size_t(lastLeftBracket) + 1, countFromLastBracket).c_str()));
					countFromLastBracket = 0;
				}
			}
			if (string[i] == ',') {
				if (waitingForComma)
					waitingForComma = false;
			}
			else
				countFromLastBracket += insideBrackets;
		}
	}


	// List of variables
	class DataStructure {
	public:
		DataStructure();
		DataStructure(const std::string& id, int maxSize);

		Variable* variable(const std::string& id);
		Variable* variable(int id);

		void operator<<(const Variable& variable);
		void operator<<(const Variable&& variable);

		void addVariable(const std::string& name, const std::string& value);

		Variable* operator[](const std::string& id);

		Variable* operator[](int id);

		std::vector<Variable> data;

		std::string id;
	};

	// variable file
	class tCode {
	public:
		tCode();
		tCode(bool loadFMem, const std::string& code);
		tCode(const std::string& filename);
		~tCode();

		void addDataStructure(DataStructure& structure);

		void addFile(const std::string& filename);

		void addCode(const std::string& code);

		// returns main if doesnt exist
		DataStructure& dataGroup(const std::string& id);
		DataStructure& dataGroup(int id);


		DataStructure& operator[](const std::string& id);
		DataStructure& operator[](int id);


		std::vector<DataStructure>* dataStructure() { return &dStucture; }
	private:
		std::vector<DataStructure> dStucture;

	private:
		// compiling part
		struct compilingStatus {
			int currentGroup = 0;
			std::string prevLine = "";
		};


		int countGroups(const std::string& code);

		// returns group Index
		int createGroup(std::string& id);

		int createMainGroup();

		void interpret(const std::string& code);

		void compile(std::string& line, compilingStatus& status);

		void createVariable(const std::string& line, compilingStatus& status);

		void deleteSpecialChars(std::string& id);
		void deleteSpecialCharsAndSpaces(std::string& id);

		void deleteSpecialChar(std::string& id);

		int groupExists(const std::string& id);
	};

	// Combine structure
	static void combineStructure(DataStructure& str1, DataStructure& str2) {
		for (int i = 0; i < (int)str2.data.size(); i++) {
			bool duplicate = false;
			for (int j = 0; j < (int)str1.data.size(); j++) {
				if (str1.data[j].key == str2.data[i].key) {
					str1.data[j].value = str2.data[i].value;
					duplicate = true;
				}
			}
			if (!duplicate)
				str1.data.push_back(str2.data[i]);

		}
	}

	// count unique structures
	static int countUniqueStruct(tCode& file1, tCode& file2) {
		int u_str = 0;

		for (int i = 0; i < (int)file2.dataStructure()->size(); i++) {
			bool unique = true;
			for (int j = 0; j < (int)file1.dataStructure()->size(); j++) {
				if (file2.dataStructure()->at(i).id == file1.dataStructure()->at(j).id) {
					unique = false;
					break;
				}
			}
			u_str += unique;
		}

		return u_str;
	}


	// Combining two files
	static void combineFiles(tCode& file1, tCode& file2) {
		// reserve additional memory for unique structures
		file1.dataStructure()->reserve(file1.dataStructure()->size() + countUniqueStruct(file1, file2));

		for (int i = 0; i < (int)file2.dataStructure()->size(); i++) {
			bool combineStruct = false;
			for (int j = 0; j < (int)file1.dataStructure()->size(); j++) {
				// if duplicate
				if (file2.dataStructure()->at(i).id == file1.dataStructure()->at(j).id) {
					combineStructure(file1.dataStructure()->at(j), file2.dataStructure()->at(i));
					combineStruct = true;
				}
			}

			// if no duplicates
			if (!combineStruct)
				file1.dataStructure()->push_back(file2.dataStructure()->at(i));
		}

		file1.dataStructure()->shrink_to_fit();

	}

	static std::string getTlangStr(const DataStructure& dStruct) {
		std::string string = "";

		if (dStruct.id != "main") {
			string += dStruct.id;
			string += "\n{\n";
		}

		for (int i = 0; i < (int)dStruct.data.size(); i++) {
			string += dStruct.id != "main" ? "\t" : "" +
				dStruct.data[i].key + " = " + dStruct.data[i].value;

			// last line doesnt add endline
			if (i + 1 != (int)dStruct.data.size())
				string += "\n";
		}
		if (dStruct.id != "main") 
			string += "\n}\n";
		return string;
	}

	static std::string getTCodeStr(tCode& tcode) {
		std::string string = "";

		for (int i = 0; i < (int)tcode.dataStructure()->size(); i++) {
			string += getTlangStr(tcode[i]) + "\n";
		}

		return string;
	}

	static void saveToFile(tCode& file, const std::string& filename) {
		std::ofstream stream;
		stream.open(filename, std::ios::trunc);

		if (stream.good()) {
			for (int i = 0; i < (int)file.dataStructure()->size(); i++) {
				stream << getTlangStr(file.dataStructure()->at(i));
			}
		}
		else
			throw std::runtime_error("tCode saveToFile - Couldn't save " + filename);
		stream.close();
	}
}

