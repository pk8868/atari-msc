#pragma once

const std::string cm_errorSeverities[3] = { "Log", "Warning", "Error" };

struct Error {
	enum ErrorSeverity : uint8_t {
		Log,
		Warning,
		Critical
	} severity;

	std::string message;

	std::string getFullMessage(bool messageBox = false) const {
		std::stringstream temp_message;

		temp_message << "[" << cm_errorSeverities[severity] << "] : " << message;

		return temp_message.str();
	}
};

class ErrorLog {
public:
	ErrorLog();
	~ErrorLog();

	ErrorLog(const ErrorLog&) = delete;
	void operator=(const ErrorLog&) = delete;

	// statyczne funkcje
	static ErrorLog& Get();
	static void Log(const Error& error) { Get().LogImpl(error); }

	static void Draw() { Get().DrawImpl(); }
	static void Toggle() { Get().m_guiStatus.open = !Get().m_guiStatus.open; }
private:
	void LogImpl(const Error& error); // implementacja funkcji Log
	void DrawImpl(); // implementacja funkcji Draw

private:
	// lista errorow
	std::vector<Error> m_error;

	// lista wartosci (sta³a lista)

	struct GuiStatus {
		bool open = false;
	} m_guiStatus;
};