#pragma once

#include "cppunit/TestCaller.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TestSuite.h"

#include <string>

namespace CppUnit
{
	template <typename T>
	class DefineSuite
	{
	protected:
		CppUnit::TestSuite* _suite;
	public:
		typedef T type;
		DefineSuite(const char* name);
		operator CppUnit::Test* () const;
		void addTest(const char* name, void (T::*method)());
	};
}

template <typename T>
CppUnit::DefineSuite<T>::DefineSuite(const char* name)
	: _suite(new CppUnit::TestSuite(name))
{}

template <typename T>
CppUnit::DefineSuite<T>::operator CppUnit::Test* () const
{
	return _suite;
}

template <typename T>
void CppUnit::DefineSuite<T>::addTest(const char* name, void (T::*method)())
{
	_suite->addTest(new CppUnit::TestCaller<T>(name, method));
}

#define CPPUNIT_TOSTR(name) #name
#define CPPUNIT_DEFINE_SUITE(var, name) ::CppUnit::DefineSuite<name> var(CPPUNIT_TOSTR(name))
#define CPPUNIT_ADD_TEST(var, test) \
	do { \
		typedef __typeof__(var) test_class; \
		var.addTest(CPPUNIT_TOSTR(test), &test_class::type::test); \
	} while(0)


