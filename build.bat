@echo off

SET runpath=%~dp0
SET ctfpath="C:\Program Files (x86)\Steam\steamapps\common\Clickteam Fusion 2.5\"
SET "arg=%1"

IF "%arg%"=="--help" goto :help
IF "%arg%"=="/help" goto :help
IF "%arg%"=="-h" goto :help
IF "%arg%"=="/h" goto :help
IF "%arg%"=="-?" goto :help
IF "%arg%"=="/?" goto :help

echo Building Noise...
echo IF MSBUILD IS NOT FOUND TRY ADDING MSBUILD DIR TO THE PATH!

rmdir MFX /s /q

IF "%arg%"=="--debug" goto :debug
IF "%arg%"=="/debug" goto :debug

IF "%arg%"=="--fast" goto :fast
IF "%arg%"=="/fast" goto :fast
IF 1==1 goto :build



:build
msbuild -t:"Noise_Windows" -p:Configuration="Edittime Unicode" -p:Platform="x86" ./Noise.sln
msbuild -t:"Noise_Windows" -p:Configuration="Runtime Unicode" -p:Platform="x86" ./Noise.sln
msbuild -t:"Noise_Android" -p:Configuration="Runtime" -p:Platform="x86" ./Noise.sln
msbuild -t:"Noise_Android" -p:Configuration="Runtime" -p:Platform="x64" ./Noise.sln
msbuild -t:"Noise_Android" -p:Configuration="Runtime" -p:Platform="ARM" ./Noise.sln
msbuild -t:"Noise_Android" -p:Configuration="Runtime" -p:Platform="ARM64" ./Noise.sln
goto :finish


:debug
msbuild -t:"Noise_Windows" -p:Configuration="Debug Unicode" -p:Platform="x86" ./Noise.sln
msbuild -t:"Noise_Android" -p:Configuration="Debug" -p:Platform="x86" ./Noise.sln
msbuild -t:"Noise_Android" -p:Configuration="Debug" -p:Platform="x64" ./Noise.sln
msbuild -t:"Noise_Android" -p:Configuration="Debug" -p:Platform="ARM" ./Noise.sln
msbuild -t:"Noise_Android" -p:Configuration="Debug" -p:Platform="ARM64" ./Noise.sln
goto :finish


:fast
msbuild -t:"Noise_Windows" -p:Configuration="Debug Unicode" -p:Platform="x86" ./Noise.sln
goto :finish


:help
echo Why? - This tool was made to make not using vs 2022 easier.
echo Run arguments:
echo   --debug /debug  -  Build debug
echo   --fast /fast  -  Build only debug unicode windows.
echo   --help -h -? /help /h /?  -  Display this very unhelpfull message.
echo Common errors:
echo   'msbuild' is not recognized as an internal or external command, operable program or batch file.  -  Find where msbuild is installed and add that path to PATH env variable.
echo   Failed to copy and simmilar errors  -  Try to modify ctfpath on top of this bat file to path to your CTF instalation.
goto :exit



:finish
echo Instaling extension...
echo IF IT FAILS MODIFY CTFPATH OR CLOSE CTF!

echo xcopy /s /v /c /y %runpath%\MFX\*.* %ctfpath%
xcopy /s /v /c /y %runpath%\MFX\*.* %ctfpath%

echo Done.

:exit