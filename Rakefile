if RUBY_PLATFORM =~ /mswin|mingw/
  def sh(cmd)
    exit $?.exitstatus unless system cmd
  end
  cmake_cmd = 'cmake -G "Visual Studio 14 Win64"'
  build_cmd = 'cmake --build . --target install --config %CONFIGURATION%'
  package_cmd = "7z a cppunit-win-#{ENV['PLATFORM']}-#{ENV['CONFIGURATION'].downcase}.zip"
else
  cmake_cmd = 'cmake .'
  build_cmd = 'make install'
  package_cmd = "tar czf cppunit-#{ENV['TRAVIS_OS_NAME'] || 'unix'}-x86_64-#{ENV['CC'] || 'gcc'}.tgz cppunit"
end

task :clean do
  rm_rf 'build'
  rm_rf 'dist'
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
