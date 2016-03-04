#include "Options.h"
#include <cstdlib>

CPPUNIT_NS::Options::Options(std::ostream& out, std::ostream& error)
	: _out(out)
	, _error(error)
	, _program("cppunit testsuite")
	, _doWait(false)
	, _doPrintResult(true)
	, _doPrintProgress(true)
	, _doPrintVerbose(false)
{}

void CPPUNIT_NS::Options::parse(int argc, const char* argv[])
{
	if(argc > 0)
	{
		_program = argv[0];
		std::string::size_type s = _program.find_last_of("/\\");
		if(s != std::string::npos)
			_program = _program.substr(s + 1);
	}
	for(int i = 1; i < argc; ++i)
	{
		std::string option = argv[i];
		if(option == "-V" || option == "--verbose")
		{
			_doPrintVerbose = true;
		}
		else if(option == "-w" || option == "--wait")
		{
			_doWait = true;
		}
		else if(option == "-r" || option == "--no-print-result")
		{
			_doPrintResult = false;
		}
		else if(option == "-p" || option == "--no-print-progress")
		{
			_doPrintProgress = false;
		}
		else if(option == "-v" || option == "--version")
		{
			exitVersionMessage();
		}
		else if(option == "-h" || option == "--help")
		{
			exitHelpMessage();
		}
		else if(option.compare(0, 1, "-") == 0)
		{
			exitErrorMessage(option);
		}
		else
		{
			_testNames.push_back(option);
		}
	}
}

const std::vector<std::string>& CPPUNIT_NS::Options::testNames() const
{
	return _testNames;
}

bool CPPUNIT_NS::Options::doWait() const
{
	return _doWait;
}

bool CPPUNIT_NS::Options::doPrintResult() const
{
	return _doPrintResult;
}

bool CPPUNIT_NS::Options::doPrintProgress() const
{
	return _doPrintProgress;
}

bool CPPUNIT_NS::Options::doPrintVerbose() const
{
	return _doPrintVerbose;
}

void CPPUNIT_NS::Options::exitVersionMessage()
{
	_out << _program << ": CppUnit " << CPPUNIT_VERSION << " (" << __DATE__ << ")" << std::endl;
	::exit(0);
}

void CPPUNIT_NS::Options::exitHelpMessage(int code)
{
	_out << _program << " [options] TEST..." << std::endl;
	_out << "CppUnit test driver" << std::endl;
	_out << std::endl;

	_out << "  -h --help               Show this help message" << std::endl;
	_out << "  -v --version            Show version banner" << std::endl;
	_out << "  -V --verbose            Enable verbose progress output" << std::endl;
	_out << "  -w --wait               Wait to exit until user presses RETURN" << std::endl;
	_out << "  -r --no-print-result    Disable printing test result" << std::endl;
	_out << "  -p --no-print-progress  Disable printing test progress" << std::endl;

	_out << std::endl;

	::exit(code);
}

void CPPUNIT_NS::Options::exitErrorMessage(const std::string& option)
{
	_error << _program << ": invalid option " << option << std::endl;
	exitHelpMessage(1);
}

