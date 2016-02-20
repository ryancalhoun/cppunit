#include <cppunit/Test.h>
#include <cppunit/TestFailure.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/portability/Stream.h>


CPPUNIT_NS_BEGIN

TextTestProgressListener::TextTestProgressListener()
	: _failure(NULL)
{
}

TextTestProgressListener::~TextTestProgressListener()
{
}

void TextTestProgressListener::startTest(Test* test)
{
	stdCOut() << test->getName() << " ";
	stdCOut().flush();
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
	stdCOut() << "\n";
	stdCOut().flush();
}

void TextTestProgressListener::addFailure(const TestFailure& failure)
{
	_failure = failure.clone();
}

void TextTestProgressListener::endTestRun(Test*, TestResult*)
{
	stdCOut() << "\n";
	stdCOut().flush();
}


CPPUNIT_NS_END

