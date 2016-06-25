ECHO OFF


REM ----- Generation configuration. ----- 
SET BUILDTYPE=Debug
SET SYSTEMPLATFORM=win
SET PLATFORM=x64
SET COMPILER=Visual2008
SET COMPILERNAME="Visual Studio 9 2008 Win64"
SET PROJECT_NAME=KLab

REM ----- Variables declarations. ----- 
SET FULLPROJECT_NAME=%PROJECT_NAME%
IF /I "%BUILDTYPE%" == "Debug" (
	SET FULLPROJECT_NAME=%PROJECT_NAME%_d
	IF /I "%PLATFORM%" == "x64" (
 		SET FULLPROJECT_NAME=%PROJECT_NAME%64_d
	)
)
IF /I "%BUILDTYPE%" == "Release" (
	SET FULLPROJECT_NAME=%PROJECT_NAME%
	IF /I "%PLATFORM%" == "x64" (
 		SET FULLPROJECT_NAME=%PROJECT_NAME%64
	)
)

SET CMAKEOUTPUT_PATH=CMakeOutput
SET CMAKEBUILD_PATH=%CMAKEOUTPUT_PATH%\%PLATFORM%\%BUILDTYPE%\
SET CMAKESOURCE_PATH=..\..\..\..\
SET FINALPROJECT_PATH=%COMPILER%_%PLATFORM%%BUILDTYPE%\
SET CMAKE_COMMAND=cmake -DCMAKE_BUILD_TYPE=%BUILDTYPE% -G%COMPILERNAME% %CMAKESOURCE_PATH%

REM ----- Remove previously generated files. -----
del %PROJECT_NAME%.vcproj
del /s/q/f %FINALPROJECT_PATH%
rmdir /s/q %FINALPROJECT_PATH%
del /s/q/f %CMAKEOUTPUT_PATH%
rmdir /s/q %CMAKEOUTPUT_PATH%

REM ----- Generating project file. -----
md %CMAKEBUILD_PATH%
cd %CMAKEBUILD_PATH%
%CMAKE_COMMAND% 

REM ----- Copy generated project to his final location. -----
cd %CMAKESOURCE_PATH%
md %SYSTEMPLATFORM%\%FINALPROJECT_PATH%
copy %SYSTEMPLATFORM%\%CMAKEBUILD_PATH%%FULLPROJECT_NAME%.vcproj %SYSTEMPLATFORM%\%FINALPROJECT_PATH%%FULLPROJECT_NAME%.vcproj

REM ------ Clean temporary files. ------
del /s/q/f %SYSTEMPLATFORM%\%CMAKEOUTPUT_PATH%
rmdir /s/q %SYSTEMPLATFORM%\%CMAKEOUTPUT_PATH%


REM ------ Create build file. ------
SET COMPILER_PATH=
IF /I "%COMPILER%" == "Visual2005" (
	SET COMPILER_PATH=C:\Program Files\Microsoft Visual Studio 8\Common7\IDE\
)
IF /I "%COMPILER%" == "Visual2008" (
	SET COMPILER_PATH=C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\
)

SET BUILD_FILE=%SYSTEMPLATFORM%\%FINALPROJECT_PATH%Build.bat
SET BUILD_COMMAND="%COMPILER_PATH%devenv.com" %FULLPROJECT_NAME%.vcproj /build %BUILDTYPE% /project %FULLPROJECT_NAME%

ECHO ECHO ON >> %BUILD_FILE%
ECHO %BUILD_COMMAND% >> %BUILD_FILE% 
ECHO ECHO OFF >> %BUILD_FILE%
ECHO del /s/q/f %FULLPROJECT_NAME%.dir >> %BUILD_FILE%
ECHO rmdir /s/q %FULLPROJECT_NAME%.dir >> %BUILD_FILE%
ECHO del /s/q/f ..\cmakeoutput >> %BUILD_FILE%
ECHO rmdir /s/q ..\cmakeoutput >> %BUILD_FILE%
ECHO del /s/q/f ..\..\..\obj\%SYSTEMPLATFORM% >> %BUILD_FILE%
ECHO rmdir /s/q ..\..\..\obj\%SYSTEMPLATFORM% >> %BUILD_FILE%
ECHO del /s/q/f ..\..\..\bin\%SYSTEMPLATFORM%\%BUILDTYPE%\*.idb >> %BUILD_FILE%
ECHO del /s/q/f ..\..\..\bin\%SYSTEMPLATFORM%\%BUILDTYPE%\*.pdb >> %BUILD_FILE%
ECHO del /s/q/f ..\..\..\bin\%SYSTEMPLATFORM%\%BUILDTYPE%\*.ilk >> %BUILD_FILE%
