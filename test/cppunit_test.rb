require 'test/unit'

class CppUnitTest < Test::Unit::TestCase

  def testCppUnit
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      output = `./cppunit_test`
      assert_equal 1, $?.exitstatus
      assert output.index '.F......'
      assert_match /Run:\s+8\s+Failures:\s+1\s+Errors:\s+0/, output
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
      output = `./cppunit_test -x 2>&1`
      assert_equal 1, $?.exitstatus
      assert_match /invalid option -x/, output
    }
  end

  def testCppUnitDisableProgress
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      %w(-p --no-print-progress).each {|opt|
        output = `./cppunit_test #{opt}`
        assert_equal 1, $?.exitstatus
        assert_nil output.index '.F......'
        assert_match /Run:\s+8\s+Failures:\s+1\s+Errors:\s+0/, output
      }
    }
  end

  def testCppUnitDisableResult
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      %w(-r --no-print-result).each {|opt|
        output = `./cppunit_test #{opt}`
        assert_equal 1, $?.exitstatus
        assert output.index '.F......'
        assert_no_match /Run:\s+8\s+Failures:\s+1\s+Errors:\s+0/, output
      }
    }
  end

  def testCppUnitVerbose
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      %w(-V --verbose).each {|opt|
        output = `./cppunit_test #{opt}`
        assert_equal 1, $?.exitstatus
        assert_match /FooTest::test\w+/, output
        assert_match /Run:\s+8\s+Failures:\s+1\s+Errors:\s+0/, output
      }
    }
  end

  def testCppUnitByName
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      output = `./cppunit_test -V FooTest`
      assert_equal 1, $?.exitstatus
      assert_match /FooTest/, output
      assert_no_match /BarTest/, output
      assert_match /Run:\s+7\s+Failures:\s+1\s+Errors:\s+0/, output

      output = `./cppunit_test -V BarTest`
      assert_equal 0, $?.exitstatus
      assert_no_match /FooTest/, output
      assert_match /BarTest/, output
      assert_match /OK\s+\(1\stests\)/, output
    }
  end
end
