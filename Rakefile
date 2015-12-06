if RUBY_PLATFORM =~ /win/
  def sh(cmd)
    exit $?.exitstatus unless system cmd
  end
  cmake_cmd = 'cmake -G "Visual Studio 14 Win64"'
  build_cmd = 'cmake --build . --target install --config %CONFIGURATION%'
  package_cmd = "7z a cppunit-#{RUBY_PLATFORM}-%CONFIGURATION%.zip"
else
  cmake_cmd = 'cmake .'
  build_cmd = 'make install'
  package_cmd = "tar czf cppunit-#{RUBY_PLATFORM}-#{ENV['CC'] || 'gcc'}.tgz cppunit"
end

task :cmake do
  sh cmake_cmd
end

task :build do
  sh build_cmd
end

task :package do
  chdir('dist') do
    sh package_cmd
  end
end

task :default => [:cmake, :build, :package]
