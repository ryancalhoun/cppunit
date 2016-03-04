cmake_minimum_required(VERSION 2.6)

set(SOURCES
	AdditionalMessage.cpp
	Asserter.cpp
	BeOsDynamicLibraryManager.cpp
	BriefTestProgressListener.cpp
	CompilerOutputter.cpp
	DefaultProtector.cpp
	DefaultProtector.h
	DynamicLibraryManager.cpp
	DynamicLibraryManagerException.cpp
	Exception.cpp
	Message.cpp
	Options.cpp
	Options.h
	PlugInManager.cpp
	PlugInParameters.cpp
	Protector.cpp
	ProtectorChain.cpp
	ProtectorChain.h
	ProtectorContext.h
	RepeatedTest.cpp
	ShlDynamicLibraryManager.cpp
	SourceLine.cpp
	StringTools.cpp
	SynchronizedObject.cpp
	Test.cpp
	TestAssert.cpp
	TestCase.cpp
	TestCaseDecorator.cpp
	TestComposite.cpp
	TestDecorator.cpp
	TestFactoryRegistry.cpp
	TestFailure.cpp
	TestLeaf.cpp
	TestNamer.cpp
	TestPath.cpp
	TestPlugInDefaultImpl.cpp
	TestResult.cpp
	TestResultCollector.cpp
	TestRunner.cpp
	TestSetUp.cpp
	TestSuccessListener.cpp
	TestSuite.cpp
	TestSuiteBuilderContext.cpp
	TextOutputter.cpp
	TextTestProgressListener.cpp
	TextTestResult.cpp
	TextTestRunner.cpp
	TypeInfoHelper.cpp
	XmlDocument.cpp
	XmlElement.cpp
	XmlOutputter.cpp
	XmlOutputterHook.cpp
)

if(UNIX)
	list(APPEND SOURCES
		UnixDynamicLibraryManager.cpp
	)
else()
	list(APPEND SOURCES
		DllMain.cpp
		Win32DynamicLibraryManager.cpp
	)
endif()

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(cppunit STATIC ${SOURCES})
install(TARGETS cppunit ARCHIVE DESTINATION lib)


