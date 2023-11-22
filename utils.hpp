#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>
#include <fstream>
#include <iostream>
#include "myexceptions.hpp"

namespace Utils {
	std::string calculateCRC32(const std::string& filename);
	void writeToFile(const std::string& filename, const std::string& value);
	bool checkFileIntegrity(const std::string& filename, const std::string& scFilename = std::string());

	// FileIntegrity --help
	bool isFirstCommand(int argc, char* argv[]);

	// FileIntegrity --calc <file_name>
	bool isSecondCommand(int argc, char* argv[]);

	// FileIntegrity --check <file_name>
	bool isThirdCommand(int argc, char* argv[]);

	// FileIntegrity --calc <file_name> --cs-file <checksum-filename>
	bool isFourthCommand(int argc, char* argv[]);

	// FileIntegrity --check <file_name> --cs-file <checksum-filename>
	bool isFifthCommand(int argc, char* argv[]);

	bool isValidCommand(int argc, char* argv[]);
}

#endif