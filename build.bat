@echo off

:: --------------------------------------------------
::             Noise Object build script
:: --------------------------------------------------
:: Run arguments:
:: --fast               (default) build only windows
:: --full               build everything
::
:: --debug              (default)
:: --release
::
:: --clean              delete old build before building
:: --install            copy extension to your fusion install
::
:: --bundle             create zip file with extension
::
:: --sdkconfig          create FusionSDKConfig.ini with preset settings for github actions
::
:: --verbose            more logging
::
:: --failonerr          fail with error code if build failed (made for github actions)
::
:: --run                start fusion (steam version) after compilation
:: --kill               kill fusion before installing the extension (only works with --install)
:: --------------------------------------------------

setlocal enabledelayedexpansion



set project=Noise

:: These are deafult
set full=0
set release=0
set clean=0
set install=0
set bundle=0
set sdkconfig=0
set verbose=0
set failonerr=0
set runfusion=0
set killfusion=0


for %%x in (%*) do (
    if %%~x==--fast (
        set full=0
    ) else if %%~x==--full (
        set full=1
    ) else if %%~x==--debug (
        set release=0
    ) else if %%~x==--release (
        set release=1
    ) else if %%~x==--clean (
        set clean=1
    ) else if %%~x==--install (
        set install=1
    ) else if %%~x==--bundle (
        set bundle=1
    ) else if %%~x==--sdkconfig (
        set sdkconfig=1
    ) else if %%~x==--verbose (
        set verbose=1
    ) else if %%~x==--failonerr (
        set failonerr=1
    ) else if %%~x==--run (
        set runfusion=1
    ) else if %%~x==--kill (
        set killfusion=1
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

if %release%==1 (
    set conf=Runtime
) else (
    set conf=Debug
)

if %full%==1 (
    call :build "%project%_Android" , "%conf%" , "ARM"
    call :build "%project%_Android" , "%conf%" , "ARM64"
    call :build "%project%_Android" , "%conf%" , "x86"
    call :build "%project%_Android" , "%conf%" , "x64"
)


if %install%==1 (
    call :install
)

if %runfusion%==1 (
    call :run-fusion
)

if %bundle%==1 (
    call :bundle
)

goto :exit





:setupsdkconfig
    echo [Global] > ..\FusionSDKConfig.ini
    echo UseMultiProcessorCompilationInDebug = true > ..\FusionSDKConfig.ini
    echo FavorSizeOrSpeed = speed >> ..\FusionSDKConfig.ini
    echo UseLinkTimeCodeGeneration = true >> ..\FusionSDKConfig.ini
    echo DarkEdifUpdateCheckerTagging = Noise >> ..\FusionSDKConfig.ini

    if %verbose%==1 (
        echo EchoAllDefinesFromPropsFileDuringBuild = true >> ..\FusionSDKConfig.ini
    )

    exit /B 0


:clean
    call :run rmdir MFX /s /q
    call :run rmdir Temp /s /q
    exit /B 0


:build
    :: arguments:
    :: - project name
    :: - configuration
    :: - platform

    if %verbose%==1 (
        set verbosity=detailed
    ) else (
        set verbosity=quiet
    )

    call :run msbuild "./%project%.sln" -t:"%~1" -p:Configuration="%~2";Platform="%~3" -nologo -m -clp:ForceNoAlign;verbosity=%verbosity%

    exit /B 0


:install
    echo Searching for Fusion installation...

    fusionpath.exe > fusionpath.temp
    set /p ctf_path=<fusionpath.temp
    del /q fusionpath.temp
    set ctf_path="%ctf_path%"

    if %ctf_path%=="" (
        echo Could not find any Fusion installations.
        exit /B 0
    )

    echo Found: %ctf_path%

    TASKLIST | FINDSTR /I "mmf2u.exe" > NUL
    if not %ERRORLEVEL%==1 (
        if %killfusion%==1 (
            echo Killing fusion...
            taskkill /F /IM "mmf2u.exe"
            TASKLIST | FINDSTR /I "edrt.exe" > NUL
            if not %ERRORLEVEL%==1 (
                taskkill /F /IM "edrt.exe"
            )
        )

        echo Waiting for Fusion to close...
        timeout /T 1 > NUL
        goto :install
    )

    call :run mkdir "%~dp0MFX\Examples\"
    call :run xcopy /s /v /c /y /q "%~dp0Examples\*.*" "%~dp0MFX\Examples\"

    call :run xcopy /s /v /c /y /q "%~dp0MFX\*.*" %ctf_path%
    exit /B 0


:bundle
    call :run mkdir "%~dp0MFX\Examples\"
    call :run mkdir "%~dp0MFX\Help\"
    call :run xcopy /s /v /c /y "%~dp0Examples\*.*" "%~dp0MFX\Examples\"
    call :run xcopy /s /v /c /y "%~dp0Help\*.*" "%~dp0MFX\Help\"
    call :run tar -a -cf "%project%.zip" -C MFX *.*
    exit /B 0


:run
    :: arguments:
    :: - cmd
    echo [CMD] %*
    %*

    if not %ERRORLEVEL%==0 (
        if %failonerr%==1 (
            exit 1
        )
    )

    echo.

    exit /B 0


:run-fusion
    echo Starting fusion...
    start steam://run/248170
    exit /B 0


:exit
echo Hopefully %project% will work?
