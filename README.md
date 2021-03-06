[![Travis Status](https://travis-ci.org/ryancalhoun/cppunit.svg?branch=master)](https://travis-ci.org/ryancalhoun/cppunit)
[![AppVeyor Status](https://ci.appveyor.com/api/projects/status/e790yysfh4vgb2a1/branch/master?svg=true)](https://ci.appveyor.com/project/ryancalhoun/cppunit)

# CppUnit: The C++ Unit Test Library

A fork of http://www.freedesktop.org/wiki/Software/cppunit.

CppUnit is the C++ port of the famous JUnit framework for unit
testing.

## Create your test runner
```c++
#include "cppunit/TestResultCollector.h"
#include "cppunit/ui/text/TestRunner.h"

#include "MyTestClass.h"

int main(int argc, const char* argv[])
{
  CppUnit::TextUi::TestRunner runner;
  
  runner.addTest(MyTestClass::suite());
  runner.run(argc, argv);
  
  return runner.result().testFailures();
}
```

CppUnit will parse the given command-line options and allow some control over the manner of running. The test runner can also display the CppUnit version, or a help message like this:
```
cppunit_test [options] TEST...
CppUnit test driver

  -h --help               Show this help message
  -v --version            Show version banner
  -V --verbose            Enable verbose progress output
  -w --wait               Wait to exit until user presses RETURN
  -r --no-print-result    Disable printing test result
  -p --no-print-progress  Disable printing test progress
  -x --xml-output         Enable xml output for test result
```

## Define each test suite
```c++
#include "cppunit/CppUnit.h"

class MyTestClass : public CppUnit::TestFixture
{
public:
  void testSomething();
  
  static CppUnit::Test* suite()
  {
    CPPUNIT_DEFINE_SUITE(suite, MyTestClass);
    CPPUNIT_ADD_TEST(suite, testSomething);
    
    return suite;
  }
};
```
## Make assertions
```c++
void MyTestClass::testSomething()
{
  int x = 42;
  assert_true(x > 0 && x < 100);
  assert_false(x < 0);
  assert_equal(42, x);
}
```

## Available asserts
```c++
void assert_true(condition);
void assert_false(condition);
void assert_equal(expected, actual);
void assert_less(expected, actual);
void assert_less_equal(expected, actual);
void assert_greater(expected, actual);
void assert_greater_equal(expected, actual);
void assert_doubles_equal(expected, actual, tolerance);
void assert_throw(expected_type, expression);
void assert_no_throw(expression);
```
Each of the above asserts may take an additional (last) parameter, an assert failure message.

For instance:
```c++
  assert_true(foo, "better check the database again");
  assert_greater_equal(0, timestamp, "need to update the license file");
```
