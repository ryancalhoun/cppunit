#ifndef CPPUNIT_TESTASSERT_H
#define CPPUNIT_TESTASSERT_H

#include <cppunit/Portability.h>
#include <cppunit/Exception.h>
#include <cppunit/Asserter.h>
#include <cppunit/portability/Stream.h>
#include <stdio.h>
#include <float.h> // For struct assertion_traits<double>

// Work around "passing 'T' chooses 'int' over 'unsigned int'" warnings when T
// is an enum type:
#if defined __GNUC__ && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6))
#pragma GCC system_header
#endif


CPPUNIT_NS_BEGIN


/*! \brief Traits used by CPPUNIT_ASSERT* macros.
 *
 * Here is an example of specialising these traits: 
 *
 * \code
 * template<>
 * struct assertion_traits<std::string>   // specialization for the std::string type
 * {
 *   static bool equal(const std::string& x, const std::string& y)
 *   {
 *     return x == y;
 *   }
 *
 *   static bool less(const std::string& x, const std::string& y)
 *   {
 *      return x < y;
 *   }
 *
 *   static bool lessEqual(const std::string& x, const std::string& y)
 *   {
 *      return x <= y;
 *   }
 *
 *   static std::string toString(const std::string& x)
 *   {
 *     std::string text = '"' + x + '"';    // adds quote around the string to see whitespace
 *     OStringStream ost;
 *     ost << text;
 *     return ost.str();
 *   }
 * };
 * \endcode
 */
template <class T>
struct assertion_traits 
{  
    static bool equal(const T& x, const T& y)
    {
        return x == y;
    }

    static bool less(const T& x, const T& y)
    {
        return x < y;
    }

    static bool lessEqual(const T& x, const T& y)
    {
        return x <= y;
    }

    static std::string toString(const T& x)
    {
        OStringStream ost;
// Work around "passing 'T' chooses 'int' over 'unsigned int'" warnings when T
// is an enum type:
#if defined __GNUC__ && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 6) || __GNUC__ > 4)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-promo"
#endif
        ost << x;
#if defined __GNUC__ && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 6) || __GNUC__ > 4)
#pragma GCC diagnostic pop
#endif
        return ost.str();
    }
};


/*! \brief Traits used by CPPUNIT_ASSERT_DOUBLES_EQUAL(). 
 * 
 * This specialisation from @c struct @c assertion_traits<> ensures that 
 * doubles are converted in full, instead of being rounded to the default 
 * 6 digits of precision. Use the system defined ISO C99 macro DBL_DIG 
 * within float.h is available to define the maximum precision, otherwise
 * use the hard-coded maximum precision of 15.
 */
template <>
struct assertion_traits<double>
{  
    static bool equal(double x, double y)
    {
        return x == y;
    }

    static bool less(double x, double y)
    {
        return x < y;
    }

    static bool lessEqual(double x, double y)
    {
        return x <= y;
    }

    static std::string toString(double x)
    {
#ifdef DBL_DIG
       const int precision = DBL_DIG;
#else
       const int precision = 15;
#endif  // #ifdef DBL_DIG
       char buffer[128];
#ifdef __STDC_SECURE_LIB__ // Use secure version with visual studio 2005 to avoid warning.
       sprintf_s(buffer, sizeof(buffer), "%.*g", precision, x); 
#else	
       sprintf(buffer, "%.*g", precision, x); 
#endif
       return buffer;
    }
};


/*! \brief (Implementation) Asserts that two objects of the same type are equals.
 * Use CPPUNIT_ASSERT_EQUAL instead of this function.
 * \sa assertion_traits, Asserter::failNotEqual().
 */
template <class T>
void assertEquals(const T& expected,
                  const T& actual,
                  SourceLine sourceLine,
                  const std::string &message)
{
	if(!assertion_traits<T>::equal(expected,actual)) // lazy toString conversion...
	{
		Asserter::failNotEqual(assertion_traits<T>::toString(expected),
		                       assertion_traits<T>::toString(actual),
		                       sourceLine,
		                       message);
	}
}

void assertEquals(const char* expected, const std::string& actual, SourceLine sourceLine, const std::string& message);
void assertEquals(int expected, unsigned long long actual, SourceLine sourceLine, const std::string& message);


/*! \brief (Implementation) Asserts that two double are equals given a tolerance.
 * Use CPPUNIT_ASSERT_DOUBLES_EQUAL instead of this function.
 * \sa Asserter::failNotEqual().
 * \sa CPPUNIT_ASSERT_DOUBLES_EQUAL for detailed semantic of the assertion.
 */
void CPPUNIT_API assertDoubleEquals(double expected,
                                    double actual,
                                    double delta,
                                    SourceLine sourceLine, 
                                    const std::string &message);


/*! \brief (Implementation) Asserts that an object is less than another one of the same type
 * Use CPPUNIT_ASSERT_LESS, CPPUNIT_ASSERT_GREATER instead of this function.
 * \sa assertion_traits, Asserter::failNotLess().
 */
template <class T>
void assertLess(const T& expected,
                const T& actual,
                SourceLine sourceLine,
                const std::string& message)
{
	if(!assertion_traits<T>::less(actual,expected))
	{
		Asserter::failNotLess(assertion_traits<T>::toString(expected),
		                      assertion_traits<T>::toString(actual),
		                      sourceLine,
		                      message);
	}
}

void assertLess(int expected, unsigned long long actual, SourceLine sourceLine, const std::string& message);


/*! \brief (Implementation) Asserts that an object is less than another one of the same type
 * Use CPPUNIT_ASSERT_LESS, CPPUNIT_ASSERT_GREATER instead of this function.
 * \sa assertion_traits, Asserter::failNotLess().
 */
template <class T>
void assertGreater(const T& expected,
                   const T& actual,
                   SourceLine sourceLine,
                   const std::string& message)
{
	if(!assertion_traits<T>::less(expected,actual))
	{
		Asserter::failNotGreater(assertion_traits<T>::toString(expected),
		                         assertion_traits<T>::toString(actual),
		                         sourceLine,
		                         message);
	}
}

void assertGreater(int expected, unsigned long long actual, SourceLine sourceLine, const std::string& message);

/*! \brief (Implementation) Asserts that two objects of the same type are equals.
 * Use CPPUNIT_ASSERT_LESSEQUAL, CPPUNIT_ASSERT_GREATEREQUAL instead of this function.
 * \sa assertion_traits, Asserter::failNotLessEqual().
 */
template <class T>
void assertLessEqual(const T& expected,
                     const T& actual,
                     SourceLine sourceLine,
                     const std::string& message)
{
	if(!assertion_traits<T>::lessEqual(actual,expected))
	{
		Asserter::failNotLessEqual(assertion_traits<T>::toString(expected),
		                           assertion_traits<T>::toString(actual),
		                           sourceLine,
		                           message);
	}
}

void assertLessEqual(int expected, unsigned long long actual, SourceLine sourceLine, const std::string& message);

/*! \brief (Implementation) Asserts that two objects of the same type are equals.
 * Use CPPUNIT_ASSERT_LESSEQUAL, CPPUNIT_ASSERT_GREATEREQUAL instead of this function.
 * \sa assertion_traits, Asserter::failNotLessEqual().
 */
template <class T>
void assertGreaterEqual(const T& expected,
                        const T& actual,
                        SourceLine sourceLine,
                        const std::string& message)
{
	if(!assertion_traits<T>::lessEqual(expected,actual))
	{
		Asserter::failNotGreaterEqual(assertion_traits<T>::toString(expected),
		                              assertion_traits<T>::toString(actual),
		                              sourceLine,
		                              message);
	}
}

void assertGreaterEqual(int expected, unsigned long long actual, SourceLine sourceLine, const std::string& message);

#define CPPUNIT_ASSERT(condition)                                                 \
  (CPPUNIT_NS::Asserter::failIf(!(condition),                                   \
                                 CPPUNIT_NS::Message("assertion failed",         \
                                                      "Expression: " #condition), \
                                 CPPUNIT_SOURCELINE()))
#define CPPUNIT_ASSERT_MESSAGE(message,condition)                          \
  (CPPUNIT_NS::Asserter::failIf(!(condition),                            \
                                  CPPUNIT_NS::Message("assertion failed", \
                                                       "Expression: "      \
                                                       #condition,         \
                                                       message),          \
                                  CPPUNIT_SOURCELINE()))
#define CPPUNIT_FAIL(message)                                         \
  (CPPUNIT_NS::Asserter::fail(CPPUNIT_NS::Message("forced failure",  \
                                                     message),         \
                                CPPUNIT_SOURCELINE()))

#define CPPUNIT_ASSERT_EQUAL(expected,actual)          \
  (CPPUNIT_NS::assertEquals((expected),              \
                              (actual),                \
                              CPPUNIT_SOURCELINE(),    \
                              ""))

#define CPPUNIT_ASSERT_EQUAL_MESSAGE(message,expected,actual)      \
  (CPPUNIT_NS::assertEquals((expected),              \
                              (actual),                \
                              CPPUNIT_SOURCELINE(),    \
                              (message)))

#define CPPUNIT_ASSERT_LESS(expected, actual)          \
    (CPPUNIT_NS::assertLess((expected),              \
                              (actual),                \
                              CPPUNIT_SOURCELINE(),    \
                              ""))
#define CPPUNIT_ASSERT_LESS_MESSAGE(message,expected, actual)          \
    (CPPUNIT_NS::assertLess((expected),              \
                              (actual),                \
                              CPPUNIT_SOURCELINE(),    \
                              (message)))

#define CPPUNIT_ASSERT_GREATER(expected, actual)       \
    (CPPUNIT_NS::assertGreater((expected),           \
                                 (actual),             \
                                 CPPUNIT_SOURCELINE(), \
                                 ""))
#define CPPUNIT_ASSERT_GREATER_MESSAGE(message,expected, actual)       \
    (CPPUNIT_NS::assertGreater((expected),           \
                                 (actual),             \
                                 CPPUNIT_SOURCELINE(), \
                                 (message)))

#define CPPUNIT_ASSERT_LESSEQUAL(expected, actual)               \
    (CPPUNIT_NS::assertLessEqual((expected),              \
                                   (actual),                \
                                   CPPUNIT_SOURCELINE(),    \
                                   ""))
#define CPPUNIT_ASSERT_LESSEQUAL_MESSAGE(message,expected, actual)               \
    (CPPUNIT_NS::assertLessEqual((expected),              \
                                   (actual),                \
                                   CPPUNIT_SOURCELINE(),    \
                                   (message)))

#define CPPUNIT_ASSERT_GREATEREQUAL(expected, actual)            \
    (CPPUNIT_NS::assertGreaterEqual((expected),                \
                                      (actual),              \
                                      CPPUNIT_SOURCELINE(),    \
                                      ""))
#define CPPUNIT_ASSERT_GREATEREQUAL_MESSAGE(message,expected, actual)            \
    (CPPUNIT_NS::assertGreaterEqual((expected),                \
                                      (actual),              \
                                      CPPUNIT_SOURCELINE(),    \
                                      (message)))

#define CPPUNIT_ASSERT_DOUBLES_EQUAL(expected,actual,delta)        \
  (CPPUNIT_NS::assertDoubleEquals((expected),            \
                                    (actual),              \
                                    (delta),               \
                                    CPPUNIT_SOURCELINE(),  \
                                    ""))

#define CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(message,expected,actual,delta)  \
  (CPPUNIT_NS::assertDoubleEquals((expected),            \
                                    (actual),              \
                                    (delta),               \
                                    CPPUNIT_SOURCELINE(),  \
                                    (message)))

# define CPPUNIT_ASSERT_THROW(expression, ExceptionType)              \
   CPPUNIT_ASSERT_THROW_MESSAGE(CPPUNIT_NS::AdditionalMessage(),       \
                                 expression,                            \
                                 ExceptionType)


#if CPPUNIT_USE_TYPEINFO_NAME
#define CPPUNIT_EXTRACT_EXCEPTION_TYPE_(exception, no_rtti_message) \
   CPPUNIT_NS::TypeInfoHelper::getClassName(typeid(exception))
#else
#define CPPUNIT_EXTRACT_EXCEPTION_TYPE_(exception, no_rtti_message) \
   std::string(no_rtti_message)
#endif

#define CPPUNIT_GET_PARAMETER_STRING(parameter) #parameter

# define CPPUNIT_ASSERT_THROW_MESSAGE(message, expression, ExceptionType)   \
   do {                                                                       \
      bool cpputCorrectExceptionThrown_ = false;                              \
      CPPUNIT_NS::Message cpputMsg_("expected exception not thrown");       \
      cpputMsg_.addDetail(message);                                         \
      cpputMsg_.addDetail("Expected: "                                       \
                           CPPUNIT_GET_PARAMETER_STRING(ExceptionType));   \
                                                                              \
      try {                                                                   \
         expression;                                                          \
      } catch (const ExceptionType &) {                                     \
         cpputCorrectExceptionThrown_ = true;                                 \
      } catch (const std::exception &e) {                                    \
         cpputMsg_.addDetail("Actual  : " +                                  \
                              CPPUNIT_EXTRACT_EXCEPTION_TYPE_(e,             \
                                          "std::exception or derived"));     \
         cpputMsg_.addDetail(std::string("What()  : ") + e.what());         \
      } catch (...) {                                                       \
         cpputMsg_.addDetail("Actual  : unknown.");                          \
      }                                                                       \
                                                                              \
      if(cpputCorrectExceptionThrown_)                                     \
         break;                                                               \
                                                                              \
      CPPUNIT_NS::Asserter::fail(cpputMsg_,                                  \
                                  CPPUNIT_SOURCELINE());                     \
   } while (false)


# define CPPUNIT_ASSERT_NO_THROW(expression)                             \
   CPPUNIT_ASSERT_NO_THROW_MESSAGE(CPPUNIT_NS::AdditionalMessage(),       \
                                    expression)


# define CPPUNIT_ASSERT_NO_THROW_MESSAGE(message, expression)               \
   do {                                                                       \
      CPPUNIT_NS::Message cpputMsg_("unexpected exception caught");         \
      cpputMsg_.addDetail(message);                                         \
                                                                              \
      try {                                                                   \
         expression;                                                          \
      } catch (const std::exception &e) {                                   \
         cpputMsg_.addDetail("Caught: " +                                    \
                              CPPUNIT_EXTRACT_EXCEPTION_TYPE_(e,             \
                                          "std::exception or derived"));    \
         cpputMsg_.addDetail(std::string("What(): ") + e.what());           \
         CPPUNIT_NS::Asserter::fail(cpputMsg_,                               \
                                     CPPUNIT_SOURCELINE());                  \
      } catch (...) {                                                       \
         cpputMsg_.addDetail("Caught: unknown.");                           \
         CPPUNIT_NS::Asserter::fail(cpputMsg_,                               \
                                     CPPUNIT_SOURCELINE());                  \
      }                                                                       \
   } while (false)


# define CPPUNIT_ASSERT_ASSERTION_FAIL(assertion)                 \
   CPPUNIT_ASSERT_THROW(assertion, CPPUNIT_NS::Exception)

# define CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(message, assertion)    \
   CPPUNIT_ASSERT_THROW_MESSAGE(message, assertion, CPPUNIT_NS::Exception)

# define CPPUNIT_ASSERT_ASSERTION_PASS(assertion)                 \
   CPPUNIT_ASSERT_NO_THROW(assertion)

# define CPPUNIT_ASSERT_ASSERTION_PASS_MESSAGE(message, assertion)    \
   CPPUNIT_ASSERT_NO_THROW_MESSAGE(message, assertion)

#define CPPUNIT_VA_SELECT(_2, _1, NAME, ...) NAME

/*
 * Variadic macros for message/no-message signatures
 */
#define CPPUNIT_REEVAL(exp) exp
#define CPPUNIT_VA_ARG2(_0, _1, _2, ...) _2
#define CPPUNIT_SELECT(_0, _1, ...) CPPUNIT_REEVAL(CPPUNIT_VA_ARG2(__VA_ARGS__, _0, _1))

#define CPPUNIT_VA_EXPAND(...) ,

#define CPPUNIT_TEXT_PASTE(_x1, _x2) _x1 ## _x2
#define CPPUNIT_TEXT_JOIN(_x1, _x2) CPPUNIT_TEXT_PASTE(_x1, _x2)

#define CPPUNIT_CALL_MESSAGE(fun, msg, ...) CPPUNIT_REEVAL(CPPUNIT_TEXT_PASTE(fun, _MESSAGE) (msg, __VA_ARGS__))
#define CPPUNIT_CALL_NOMESSAGE(fun, msg, ...) CPPUNIT_REEVAL(fun (__VA_ARGS__))

#define CPPUNIT_ASSERT_BODY(...) CPPUNIT_TEXT_JOIN(CPPUNIT_CALL, CPPUNIT_SELECT(_NOMESSAGE, _MESSAGE, CPPUNIT_VA_EXPAND __VA_ARGS__()))

/*
 * Primary user-facing assert definitions
 */
#define assert_true(cond, ...) CPPUNIT_ASSERT_BODY(__VA_ARGS__) (CPPUNIT_ASSERT, __VA_ARGS__, (cond))
#define assert_false(cond, ...) CPPUNIT_ASSERT_BODY(__VA_ARGS__) (CPPUNIT_ASSERT, __VA_ARGS__, ! (cond))

#define assert_equal(expected, actual, ...) CPPUNIT_ASSERT_BODY(__VA_ARGS__) (CPPUNIT_ASSERT_EQUAL, __VA_ARGS__, expected, actual)
#define assert_less(expected, actual, ...) CPPUNIT_ASSERT_BODY(__VA_ARGS__) (CPPUNIT_ASSERT_LESS, __VA_ARGS__, expected, actual)
#define assert_less_equal(expected, actual, ...) CPPUNIT_ASSERT_BODY(__VA_ARGS__) (CPPUNIT_ASSERT_LESSEQUAL, __VA_ARGS__, expected, actual)
#define assert_greater(expected, actual, ...) CPPUNIT_ASSERT_BODY(__VA_ARGS__) (CPPUNIT_ASSERT_GREATER, __VA_ARGS__, expected, actual)
#define assert_greater_equal(expected, actual, ...) CPPUNIT_ASSERT_BODY(__VA_ARGS__) (CPPUNIT_ASSERT_GREATEREQUAL, __VA_ARGS__, expected, actual)

#define assert_doubles_equal(expected, actual, tolerance, ...) CPPUNIT_ASSERT_BODY(__VA_ARGS__) (CPPUNIT_ASSERT_DOUBLES_EQUAL, __VA_ARGS__, expected, actual, tolerance)


CPPUNIT_NS_END

#endif  // CPPUNIT_TESTASSERT_H
