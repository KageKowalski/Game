#include "Log.h"

Log::Log() {
	_logFilePath = "log.txt";
	clear();
}

Log::~Log() {}

void Log::print(const std::string& msg, bool timeStamp) const {
	std::ofstream file(_logFilePath, std::ios_base::app);
	if (!file.is_open()) return;
	if(timeStamp) file << generateTimeStamp().c_str() << msg.c_str() << "\n";
	else file << msg.c_str() << "\n";
	file.close();
}

std::string Log::generateTimeStamp() const {
	std::chrono::system_clock::time_point currTime = std::chrono::system_clock::now();
	std::time_t currTimePrintable = std::chrono::system_clock::to_time_t(currTime);
	std::stringstream retStr;
	retStr << std::put_time(std::localtime(&currTimePrintable), "%F %T ");
	return retStr.str();
}

void Log::clear() const {
	std::ofstream file(_logFilePath, std::ios_base::trunc);
	if (!file.is_open()) return;
	file.close();
}