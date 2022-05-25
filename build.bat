@echo off

:: ------------------------------
::         build.bat v1.5        
:: ------------------------------
:: Run arguments:
:: --fast       -f      build only windows
:: --full       -F      build everything
:: 
:: --debug      -d
:: --release    -r
::
:: --clean      -c      delete old build before building
:: --install    -i      copy extension to your fusion install
::
:: --bundle     -b      create zip file with extension
::
:: --sdkconfig  -s      create FusionSDKConfig.ini with usefull settings
:: ------------------------------

setlocal enabledelayedexpansion

:: Modify this path if you have fusion installed somewhere else.
set ctf_path="C:\Program Files (x86)\Steam\steamapps\common\Clickteam Fusion 2.5\"

set project=Noise

:: Thiese are deafult
set full=1
set release=1
set clean=0
set install=0
set bundle=0
set sdkconfig=0


for %%x in (%*) do (
    if %%~x==--fast (
        set full=0
    ) else if %%~x==-f (
        set full=0
    ) else if %%~x==--full (
        set full=1
    ) else if %%~x==-F (
        set full=1
    ) else if %%~x==--debug (
        set release=0
    ) else if %%~x==-d (
        set release=0
    ) else if %%~x==--release (
        set release=1
    ) else if %%~x==-r (
        set release=1
    ) else if %%~x==--clean (
        set clean=1
    ) else if %%~x==-c (
        set clean=1
    ) else if %%~x==--install (
        set install=1
    ) else if %%~x==-i (
        set install=1
    ) else if %%~x==--bundle (
        set bundle=1
    ) else if %%~x==-b (
        set bundle=1
    ) else if %%~x==--sdkconfig (
        set sdkconfig=1
    ) else if %%~x==-s (
        set sdkconfig=1
    ) else (
        echo Argument %%~x is not defined!
        goto :exit
    )
)


if %clean%==1 (
    call :clean
)

if %sdkconfig%==1 (
    call :setupsdkconfig
)

if %release%==1 (
    call :build "%project%_Windows" , "Edittime Unicode" , "x86"
    call :build "%project%_Windows" , "Runtime Unicode" , "x86"
) else (
    call :build "%project%_Windows" , "Debug Unicode" , "x86"
)

if %full%==1 (
    if %release%==1 (
        call :build "%project%_Android" , "Runtime" , "ARM"
        call :build "%project%_Android" , "Runtime" , "ARM64"
        call :build "%project%_Android" , "Runtime" , "x86"
        call :build "%project%_Android" , "Runtime" , "x64"
    ) else (
        call :build "%project%_Android" , "Debug" , "ARM"
        call :build "%project%_Android" , "Debug" , "ARM64"
        call :build "%project%_Android" , "Debug" , "x86"
        call :build "%project%_Android" , "Debug" , "x64"
    )
)

if %install%==1 (
    call :install
)

if %bundle%==1 (
    call :bundle
)

goto :exit





:setupsdkconfig
    echo UseMultiProcessorCompilationInDebug = true > ..\FusionSDKConfig.ini
    echo FavorSizeOrSpeed = speed >> ..\FusionSDKConfig.ini
    echo UseLinkTimeCodeGeneration = true >> ..\FusionSDKConfig.ini
    echo DarkEdifUpdateCheckerTagging = Noise >> ..\FusionSDKConfig.ini
    echo EchoAllDefinesFromPropsFileDuringBuild = true >> ..\FusionSDKConfig.ini
    exit /B 0


:clean
    call :run rmdir MFX /s /q
    exit /B 0


:build
    :: arguments:
    :: - project name
    :: - configuration
    :: - platform
    call :run msbuild ./%project%.sln -t:"%~1" -p:Configuration="%~2";Platform="%~3";WarningLevel=all -nologo -m -clp:Summary;ForceNoAlign;verbosity=minimal
    exit /B 0


:install
    TASKLIST | FINDSTR /I "mmf2u.exe" > NUL
    IF NOT ERRORLEVEL 1 (
        echo Waiting for fusion to close...
        timeout /T 1 > NUL
        GOTO :install
    )

    call :run xcopy /s /v /c /y %~dp0MFX\*.* %ctf_path%
    exit /B 0


:bundle
    call :run mkdir %~dp0MFX\Examples\
    call :run xcopy /s /v /c /y %~dp0Examples\*.* %~dp0MFX\Examples\
    call :run xcopy /s /v /c /y %~dp0Help\*.* %~dp0MFX\Help\
    call :run tar -a -cf %project%.zip -C MFX *.*
    exit /B 0


:run
    :: arguments:
    :: - cmd
    echo [CMD] %*
    %*
    exit /B 0


:exit
echo Hopefully %project% will work?