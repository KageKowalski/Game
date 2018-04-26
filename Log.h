#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

// The Log class allows us to output whatever information may be useful to see
// outputted to an external text file called "log.txt". Anything may be logged,
// but this should be primarily used for debugging (analysing variable states)
// and error reporting.
class Log {

public:

	// Prints a string to the log file.
	// Pass in the string to print and specify if a time stamp is desired.
	void print(const std::string& msg, bool timeStamp = true) const;

private:

	// Generates a time stamp of the current date and time, precise to the second.
	// Internal function used in print() before printing the log message.
	std::string generateTimeStamp() const;

	// Clears the log file.
	void clear() const;

private:

	// File path to the log text file.
	std::string _logFilePath;

	// --- SINGLETON IMPLEMENTATION ---
public:

	Log(Log const&) = delete;
	void operator=(Log const&) = delete;

	static Log& get() {
		static Log instance;
		return        instance;
	}

private:

	Log();
	~Log();

};

#endif