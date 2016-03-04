#ifndef CPPUNIT_TEXTTESTPROGRESSLISTENER_H
#define CPPUNIT_TEXTTESTPROGRESSLISTENER_H

#include <cppunit/TestListener.h>

CPPUNIT_NS_BEGIN

/*! 
 * \brief TestListener that show the status of each TestCase test result.
 * \ingroup TrackingTestExecution
 */
class CPPUNIT_API TextTestProgressListener : public TestListener
{
public:
	/*! Constructs a TextTestProgressListener object.
	 */
	TextTestProgressListener();

	/// Destructor.
	virtual ~TextTestProgressListener();

	void enableVerboseOutput();

	void startTest(Test* test);
	void endTest(Test* test);

	void addFailure(const TestFailure& failure);

	void startTestRun(Test* test, TestResult* eventManager);
	void endTestRun(Test* test, TestResult* eventManager);

protected:
	static const char* black;
	static const char* red;
	static const char* green;

	void writeSuccess();
	void writeFailure();
	void writeError();
	void writeProgress(char progress, const char* color);

private:
	/// Prevents the use of the copy constructor.
	TextTestProgressListener(const TextTestProgressListener& copy);

	/// Prevents the use of the copy operator.
	void operator=(const TextTestProgressListener& copy);

private:
	TestFailure* _failure;
	bool         _verbose;
	bool         _color;
};


CPPUNIT_NS_END

#endif  // CPPUNIT_TEXTTESTPROGRESSLISTENER_H
