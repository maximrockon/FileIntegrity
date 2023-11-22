#ifndef MY_EXCEPTIONS_HPP
#define MY_EXCEPTIONS_HPP
#include <exception>

class FileOpenException : public std::exception {
private:
	const char* reason_;
public:
	FileOpenException() :
		reason_("Failed to open your file. Make sure you are passing the correct path.") {}

	const char* what() const {
		return reason_;
	}
};

class CheckFailedException : public std::exception {
private:
	const char* reason_;
public:
	CheckFailedException() :
		reason_("File integrity check failed. Your file has been modified.") {}

	const char* what() const {
		return reason_;
	}
};

class WrongCommandException : public std::exception {
private:
	const char* reason_;
public:
	WrongCommandException() :
		reason_("You entered an incorrect set of options. For useful information use the --help option") {}

	const char* what() const {
		return reason_;
	}
};

#endif