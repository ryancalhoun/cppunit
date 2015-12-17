require 'rake/testtask'
require 'emplace'

project = Emplace::Project.new 'cppunit'

task :clean do
  rm_rf 'build'
  rm_rf 'dist'
end

task :cmake do
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
