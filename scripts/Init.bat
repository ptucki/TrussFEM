@echo off
:: -- Any arguments provided?
:: -- Determine build type
echo first - %1
set current_build_type=""
set build_type=""

if "%1"=="-r" (
  if not exist config.txt (
    goto :end
  ) else (
    set /p build_type=<"config.txt"
    goto :start
  )
)

if "%1"=="-clean" ( goto :start )

if not exist "config.txt" (

  :: init Debug setup if no args provided
  if "%1"=="" (
    set build_type=Debug

    echo New file
    goto :start
  ) else (
    if "%1"=="Debug" (
      echo Debug>"config.txt"
      goto :start
      )
    if "%1"=="Release" (
      echo Release>"config.txt"
      goto :start
    )
    echo New file
    goto :check-args
  )
) else (
  set /p current_build_type=<"config.txt"
  goto :check-args
)

:check-args
if "%1"=="" (
  goto :end
) else (
  if "%1"=="Debug" (
    set build_type=Debug
  )
  if "%1"=="Release" (
    set build_type=Release
    )
  echo %build_type%>"config.txt"
)

if defined build_type (
  echo BUILD TYPE DEFINED - %build_type%
  if "%build_type%"=="%current_build_type%" ( goto :end )
  goto :start
) else (
  echo Build type is not defined
  goto :end
)


:: -- Clear project
:start
echo %build_type%>"config.txt"

rmdir /s /q ..\lib\
rmdir /s /q ..\include\
rmdir /s /q ..\src\imgui\

if "%1"=="-clean" ( 
  if exist "config.txt" ( del "config.txt" )
  goto :end
)

:: -- Building and compiling GLFW lib


cmake -S ..\extern\GLFW\ -B ..\extern\GLFW\build\ -D CMAKE_BUILD_TYPE=%build_type%
cmake --build ..\extern\GLFW\build\ --config %build_type%

xcopy ..\extern\GLFW\build\src\%build_type%\ ..\lib\GLFW\ /Y /I /E
xcopy ..\extern\GLFW\include\ ..\include\ /Y /I /E

:: -- Building and compiling freetype lib

cmake -S ..\extern\freetype\ -B ..\extern\freetype\build\ -D CMAKE_BUILD_TYPE=%build_type%
cmake --build ..\extern\freetype\build\ --config %build_type%

xcopy ..\extern\freetype\build\%build_type%\ ..\lib\freetype\ /Y /I /E
xcopy ..\extern\freetype\include ..\include\freetype\ /Y /I /E

:: --- Copy imgui source files to src

set src_folder=..\extern\imgui
set dst_folder=..\src\imgui

echo Copying imgui files to %dst_folder%
for /f "tokens=*" %%i in (imgui-file-list.txt) DO (
  echo   %%i
  xcopy  "%src_folder%\%%i" "%dst_folder%\%%i*" /Y /i > nul
)

echo DO NOT MODIFY ANY FILE IN THIS DIRECTORY! > ..\src\imgui\info.txt

:end
