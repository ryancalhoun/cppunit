#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "cppunit/Portability.h"

CPPUNIT_NS_BEGIN

class Options
{
public:
	Options(std::ostream& out, std::ostream& error);

	void parse(int argc, const char* argv[]);

	const std::vector<std::string>& testNames() const;
	bool doWait() const;
	bool doPrintResult() const;
	bool doPrintProgress() const;
	bool doPrintVerbose() const;

protected:
	void exitVersionMessage();
	void exitHelpMessage(int code = 0);
	void exitErrorMessage(const std::string& option);

protected:
	std::ostream&            _out;
	std::ostream&            _error;

	std::string              _program;

	std::vector<std::string> _testNames;
	bool                     _doWait;
	bool                     _doPrintResult;
	bool                     _doPrintProgress;
	bool                     _doPrintVerbose;
};

CPPUNIT_NS_END
