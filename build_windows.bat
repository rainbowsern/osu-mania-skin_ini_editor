@echo off
setlocal

:: Check if MinGW is available in PATH
where gcc >nul 2>&1
if %errorlevel% equ 0 (
    echo Using MinGW from system PATH
    goto build
)

:: If not in PATH, check for mingw folder in project directory
if exist "mingw\bin\gcc.exe" (
    echo Using MinGW from project directory
    set PATH=%~dp0mingw\bin;%PATH%
    goto build
)

:: If MinGW not found anywhere
echo Error: MinGW compiler not found!
echo.
echo Solutions:
echo 1. Install MinGW-w64 and add it to system PATH
echo 2. Or extract MinGW to a 'mingw' folder in project directory
echo.
pause
exit /b 1

:build
:: Clean and build
if exist build rmdir /s /q build
mkdir build
cd build

cmake -G "MinGW Makefiles" ..
if %errorlevel% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

cmake --build . --config Release
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build completed! Executable at bin\skin_ini_editor.exe
pause
