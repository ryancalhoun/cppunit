#include <cppunit/Test.h>
#include <cppunit/TestFailure.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/portability/Stream.h>


CPPUNIT_NS_BEGIN

TextTestProgressListener::TextTestProgressListener()
	: _failure(NULL)
	, _verbose(false)
	, _color(isaTTY())
{
}

TextTestProgressListener::~TextTestProgressListener()
{
}

void TextTestProgressListener::enableVerboseOutput()
{
	_verbose = true;
}

void TextTestProgressListener::startTest(Test* test)
{
	if(_verbose)
	{
		stdCOut() << test->getScopedName() << " ";
		stdCOut().flush();
	}
}

void TextTestProgressListener::endTest(Test* test)
{
	if(_failure != NULL)
	{
		if(_failure->isError())
			writeError();
		else
			writeFailure();
		delete _failure;
		_failure = NULL;
	}
	else
	{
		writeSuccess();
	}

	if(_verbose)
		stdCOut() << "\n";
	stdCOut().flush();
}

void TextTestProgressListener::addFailure(const TestFailure& failure)
{
	_failure = failure.clone();
}

void TextTestProgressListener::startTestRun(Test* test, TestResult*)
{
	if(_verbose)
	{
		stdCOut() << "Starting suite " << test->getName() << "\n";
		stdCOut().flush();
	}
}

void TextTestProgressListener::endTestRun(Test*, TestResult*)
{
	stdCOut() << "\n";
	stdCOut().flush();
}

const char* TextTestProgressListener::red = "\x1b[31m";
const char* TextTestProgressListener::green = "\x1b[32m";
const char* TextTestProgressListener::black = "\x1b[0m";

void TextTestProgressListener::writeSuccess()
{
	writeProgress('.', green);
}

void TextTestProgressListener::writeFailure()
{
	writeProgress('F', red);
}

void TextTestProgressListener::writeError()
{
	writeProgress('E', red);
}

void TextTestProgressListener::writeProgress(char progress, const char* color)
{
	if(_color)
		stdCOut() << color;
	stdCOut() << progress;
	if(_color)
		stdCOut() << black;
	stdCOut().flush();
}

CPPUNIT_NS_END

