#include "cppunit/CppUnit.h"
#include "cppunit/TestResultCollector.h"
#include "cppunit/ui/text/TestRunner.h"

class FooTest : public CppUnit::TestFixture
{
public:
	void testOk()
	{
		assert_true(true);
		assert_false(false);
		assert_equal(4, 4);
	}
	void testFail()
	{
		assert_true(false);
	}
	void testStrings()
	{
		std::string s("foo");
		assert_equal("foo", s);
	}
	void testIntegers()
	{
		unsigned xu = 42;
		assert_equal(42, xu);
		assert_equal(42ll, xu);
		assert_equal(42ull, xu);

		size_t xs = 42;
		assert_equal(42, xs);
		assert_equal(42ll, xs);
		assert_equal(42ull, xs);
	}

	static CppUnit::Test* suite()
	{
		CPPUNIT_DEFINE_SUITE(suite, FooTest);

		CPPUNIT_ADD_TEST(suite, testOk);
		CPPUNIT_ADD_TEST(suite, testFail);
		CPPUNIT_ADD_TEST(suite, testStrings);
		CPPUNIT_ADD_TEST(suite, testIntegers);

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


