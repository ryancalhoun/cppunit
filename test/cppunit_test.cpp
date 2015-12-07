#include "cppunit/CppUnit.h"
#include "cppunit/TestResultCollector.h"
#include "cppunit/ui/text/TestRunner.h"

class FooTest : public CppUnit::TestFixture
{
public:
	void testOk()
	{
		CPPUNIT_ASSERT(true);
	}
	void testFail()
	{
		CPPUNIT_ASSERT(false);
	}

	static CppUnit::Test* suite()
	{
		CPPUNIT_DEFINE_SUITE(suite, FooTest);

		CPPUNIT_ADD_TEST(suite, testOk);
		CPPUNIT_ADD_TEST(suite, testFail);

		return suite;
	}

};

int main(int argc, const char* argv[])
{
	CppUnit::TextUi::TestRunner runner;

	runner.addTest(FooTest::suite());
	runner.run();

	return runner.result().testFailures();
}


