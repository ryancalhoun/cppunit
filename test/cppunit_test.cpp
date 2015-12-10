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

		assert_less(16, 8u);
		assert_less_equal(16u, 8);
		assert_greater(4, 8u);
		assert_greater_equal(4u, 8);
	}

	void testDoubles()
	{
		assert_doubles_equal(42.0, 42.0, 0.001);
	}

	void testMessage()
	{
		assert_true("message", true);
	}

	static CppUnit::Test* suite()
	{
		CPPUNIT_DEFINE_SUITE(suite, FooTest);

		CPPUNIT_ADD_TEST(suite, testOk);
		CPPUNIT_ADD_TEST(suite, testFail);
		CPPUNIT_ADD_TEST(suite, testStrings);
		CPPUNIT_ADD_TEST(suite, testIntegers);
		CPPUNIT_ADD_TEST(suite, testDoubles);

		CPPUNIT_ADD_TEST(suite, testMessage);

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


