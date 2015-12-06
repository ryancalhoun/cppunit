task :cmake do
  exit $?.exitstatus unless system 'cmake -G "Visual Studio 14 Win64"'
end

task :build do
  exit $?.exitstatus unless system 'msbuild /m:4 /p:Platform=%PLATFORM% /p:Config=%CONFIGURATION% cppunit.sln'
end

task :package do
  chdir('dist') do
    exit $?.exitstatus unless system '7z a cppunit-%PLATFORM%-%CONFIGURATION%.zip'.downcase
  end
end

