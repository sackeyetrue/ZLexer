#ifndef ERROR_H
#define ERROR_H

#include "token.h"
#include "../utils/utils.h" // read a line from file

using namespace std;
namespace ZS
{
	////////////////////////////////
	// ↓ ZSCRIPT Error Classes ↓  //
	////////////////////////////////

	class Error
	{
	public:
		Error() {};

		Error(std::string name, std::string details)
			: name(name), details(details) {
			  };

		Error(std::string name, Token *token, std::string &filename, int &line, int &start_pos, int &end_pos)
			: name(name), token(token), filename(filename), line(line), start_pos(start_pos), end_pos(end_pos) {
			  };

		Error(std::string name, Token *token, std::string &filename, int &line, int &start_pos, int &end_pos, std::string details)
			: name(name), token(token), line(line), start_pos(start_pos), end_pos(end_pos), details(details), linetext(getLineText(filename, line)) {
			  };

	public:
		Token *token;

		// 	std::string file; // file
		std::string name;
		std::string filename;
		std::string linetext;

		int line; // SyntaxError
		int start_pos;
		int end_pos;
		std::string details; // Invalid Syntax expected "operator"

		// 	std::string expecting;	// Invalid Syntax expected "operator"
		// 	std::string didyoumean; // Invalid Syntax expected "operator"
	};

	class IllegalCharError : public Error
	{
	public:
		IllegalCharError(Token *token, std::string &filename, int &line, int &start_pos, int &end_pos, std::string details = "")
			: Error("IllegalCharError", token, filename, line, start_pos, end_pos, details) {
			  };
	};

	//////////////////////////////////
	// ↓ ZSCRIPT Warning Classes ↓  //
	//////////////////////////////////

	class Warning
	{
	};
};

/////////////////////////////////////
// ↓ ZSCRIPT Errors << Operator ↓  //
/////////////////////////////////////

std::ostream &operator<<(std::ostream &ostream, ZS::Error &error)
{
	ostream << "File [" << error.filename << "] " << error.name << " : '" << error.token->value << "' line:" << error.line << std::endl;
	// ostream << error.filename << std::endl;
	// ostream << error.filename << std::endl;
	// ostream << ZS::strarw(error.linetext, error.start_pos, error.end_pos) << std::endl;

	return ostream;
};

std::ostream &operator<<(std::ostream &ostream, std::vector<ZS::Error> errors)
{
	for (auto error : errors)
	{
		ostream << error;
	}
	return ostream;
};

#endif // ERROR_H
