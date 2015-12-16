require 'rake/testtask'
require 'emplace'

task :clean do
  rm_rf 'build'
  rm_rf 'dist'
end

task :cmake do
  Emplace.cmake
end

task :build do
  Emplace.build
end

task :package do
  chdir('dist') do
    Emplace.package('cppunit')
  end
end

Rake::TestTask.new {|t|
  t.test_files = FileList['test/**/*est.rb']
}

task :default => [:cmake, :build, :test, :package]
