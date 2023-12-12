REM -- Building and compiling GLFW lib

cmake -S ..\extern\GLFW\ -B ..\extern\GLFW\build\ -D CMAKE_BUILD_TYPE=Release
cmake --build ..\extern\GLFW\build\ --config Release

xcopy ..\extern\GLFW\build\src\Release\ ..\lib\GLFW\ /Y /I /E
xcopy ..\extern\GLFW\include\ ..\include\ /Y /I /E

REM -- Building and compiling freetype lib

cmake -S ..\extern\freetype\ -B ..\extern\freetype\build\ -D CMAKE_BUILD_TYPE=Release
cmake --build ..\extern\freetype\build\ --config Release

xcopy ..\extern\freetype\build\Release\ ..\lib\freetype\ /Y /I /E
xcopy ..\extern\freetype\include ..\include\freetype\ /Y /I /E

REM --- Copy imgui source files to src

@echo off
set src_folder=..\extern\imgui
set dst_folder=..\src\imgui

echo Copying imgui files to %dst_folder%
for /f "tokens=*" %%i in (imgui-file-list.txt) DO (
  echo   %%i
  xcopy  "%src_folder%\%%i" "%dst_folder%\%%i*" /Y /i > nul
)

echo DO NOT MODIFY ANY FILE IN THIS DIRECTORY! > ..\src\imgui\info.txt
