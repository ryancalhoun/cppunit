require 'rake/testtask'
require 'emplace'

project = Emplace::Project.new 'cppunit'

task :clean do
  rm_rf 'build'
  rm_rf 'dist'
end

file "build/cppunit_version.txt" do
  sh "git describe --tags > build/cppunit_version.txt"
end

task :cmake => ['build/cppunit_version.txt'] do
  project.cmake!
end

task :build do
  project.build!
end

task :package do
  project.package!
end

Rake::TestTask.new {|t|
  t.test_files = FileList['test/**/*est.rb']
}

task :default => [:cmake, :build, :test, :package]
