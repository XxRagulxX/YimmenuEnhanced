@echo off
REM Build script for YimMenuV2
REM This script simplifies the build process for Windows developers

setlocal enabledelayedexpansion

echo ========================================
echo YimMenuV2 Build Script
echo ========================================
echo.

REM Check if CMake is installed
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo ERROR: CMake is not installed or not in PATH
    echo Please install CMake from https://cmake.org/download/
    exit /b 1
)

REM Check if Ninja is installed
where ninja >nul 2>nul
if %errorlevel% neq 0 (
    echo ERROR: Ninja is not installed or not in PATH
    echo Please install Ninja from https://ninja-build.org/
    exit /b 1
)

REM Default build type
set BUILD_TYPE=RelWithDebInfo
if not "%~1"=="" set BUILD_TYPE=%~1

echo Build type: %BUILD_TYPE%
echo.

REM Create build directory
if not exist build mkdir build

REM Configure CMake project
echo Configuring CMake project...
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -S . -B build -G Ninja
if %errorlevel% neq 0 (
    echo ERROR: CMake configuration failed
    exit /b 1
)

echo.
echo Building project...
cmake --build ./build --config %BUILD_TYPE% --target YimMenuV2
if %errorlevel% neq 0 (
    echo ERROR: Build failed
    exit /b 1
)

echo.
echo ========================================
echo Build completed successfully!
echo ========================================
echo Output: build\YimMenuV2.dll
echo PDB: build\YimMenuV2.pdb
echo.

exit /b 0
