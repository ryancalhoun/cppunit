task :cmake do
  system "cmake -G 'Vistual Studio 14 Win64"
end

task :build do
  system "msbuild /m:4 /p:Platform=%PLATFORM% /p:Config=%CONFIGURATION% cppunit.sln"
end
