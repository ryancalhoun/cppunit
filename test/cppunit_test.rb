require 'test/unit'
require 'open3'

class CppUnitTest < Test::Unit::TestCase

  def testCppUnit
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      output = `./cppunit_test`
      assert_equal 1, $?.exitstatus
      assert_match /^[\.FE]+$/, output
      assert_match /Run:\s+\d+\s+Failures:\s+\d+\s+Errors:\s+\d+/, output
    }
  end

  def testCppUnitHelp
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      %w(-h --help).each {|opt|
        output = `./cppunit_test #{opt}`
        assert_equal 0, $?.exitstatus
        assert_match /Show this help message/, output
      }
    }
  end

  def testCppUnitBadOption
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      output, error, status = Open3.capture3 './cppunit_test -x'
      assert_equal 1, status.exitstatus
      assert_match /invalid option -x/, error
    }
  end

  def testCppUnitDisableProgress
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      %w(-p --no-print-progress).each {|opt|
        output = `./cppunit_test #{opt}`
        assert_equal 1, $?.exitstatus
        assert_no_match /^[\.FE]+$/, output
        assert_match /Run:\s+\d+\s+Failures:\s+\d+\s+Errors:\s+\d+/, output
      }
    }
  end

  def testCppUnitDisableResult
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      %w(-r --no-print-result).each {|opt|
        output = `./cppunit_test #{opt}`
        assert_equal 1, $?.exitstatus
        assert_match /^[\.FE]+$/, output
        assert_no_match /Run:\s+\d+\s+Failures:\s+\d+\s+Errors:\s+\d+/, output
      }
    }
  end

  def testCppUnitVerbose
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      %w(-V --verbose).each {|opt|
        output = `./cppunit_test #{opt}`
        assert_equal 1, $?.exitstatus
        assert_match /FooTest::test\w+/, output
        assert_match /Run:\s+\d+\s+Failures:\s+\d+\s+Errors:\s+\d+/, output
      }
    }
  end

  def testCppUnitByName
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      output = `./cppunit_test -V FooTest`
      assert_equal 1, $?.exitstatus
      assert_match /FooTest/, output
      assert_no_match /BarTest/, output
      assert_match /Run:\s+\d+\s+Failures:\s+\d+\s+Errors:\s+\d+/, output

      output = `./cppunit_test -V BarTest`
      assert_equal 0, $?.exitstatus
      assert_no_match /FooTest/, output
      assert_match /BarTest/, output
      assert_match /OK\s+\(1\stests\)/, output
    }
  end

  def testCppUnitByMethod
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      output = `./cppunit_test -V FooTest::testOk`
      assert_equal 0, $?.exitstatus
      assert_match /FooTest::testOk/, output
      assert_match /OK\s+\(1\stests\)/, output
    }
  end
end
