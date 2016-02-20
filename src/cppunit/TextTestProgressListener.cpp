#include <cppunit/Test.h>
#include <cppunit/TestFailure.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/portability/Stream.h>


CPPUNIT_NS_BEGIN

TextTestProgressListener::TextTestProgressListener()
	: _failure(NULL)
	, _verbose(false)
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
		stdCOut() << (_failure->isError() ? "E" : "F");
		delete _failure;
		_failure = NULL;
	}
	else
	{
		stdCOut() << ".";
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


CPPUNIT_NS_END

