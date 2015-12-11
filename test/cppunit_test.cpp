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
		int xi = 42;
		assert_equal(42, xi);
		assert_equal(42ll, xi);
		assert_equal(42ull, xi);

		long long xll = 42;
		assert_equal(42, xll);
		assert_equal(42ll, xll);
		assert_equal(42ull, xll);

		unsigned xu = 42;
		assert_equal(42, xu);
		assert_equal(42ll, xu);
		assert_equal(42ull, xu);

		unsigned long long xull = 42;
		assert_equal(42, xull);
		assert_equal(42ll, xull);
		assert_equal(42ull, xull);

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
		assert_true(true, "message");
		assert_false(false, "message");

		assert_equal(2, 2, "message");

		assert_less(4, 2, "message");
		assert_less_equal(4, 2, "message");

		assert_greater(4, 8, "message");
		assert_greater_equal(4, 8, "message");

		assert_doubles_equal(4.2, 4.2, 0.1, "message");
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


