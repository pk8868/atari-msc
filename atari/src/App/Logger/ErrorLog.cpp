#include "pch.h"
#include "ErrorLog.hpp"

ErrorLog::ErrorLog() {

}

ErrorLog::~ErrorLog() {

}

ErrorLog& ErrorLog::Get() {
	static ErrorLog logger;
	return logger;
}

void ErrorLog::LogImpl(const Error& error) {
	util::addToLogFile(cm_errorSeverities[error.severity] + " - " + error.message);

	if (error.severity == Error::Critical)
		throw std::runtime_error(error.message);

	m_error.push_back(error);
}

void ErrorLog::DrawImpl() {
	if (!m_guiStatus.open)
		return;

	ImGui::Begin("Logger", &m_guiStatus.open, ImGuiWindowFlags_NoCollapse);

	for (int i = 0; i < m_error.size(); i++) {
		ImGui::Text(m_error[i].getFullMessage().c_str());
	}

	ImGui::End();
}
