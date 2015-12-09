require 'test/unit'

class CppUnitTest < Test::Unit::TestCase

  def testCppUnit
    Dir.chdir(File.join(File.dirname(__FILE__), '..', 'build', 'test', ENV['CONFIGURATION'].to_s)) {
      output = `./cppunit_test`
      assert_equal 1, $?.exitstatus
      assert_match /Run:\s+4\s+Failures:\s+1\s+Errors:\s+0/, output
    }
  end

end
