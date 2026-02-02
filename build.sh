#!/bin/bash
# Build script for YimMenuV2 (Cross-compilation with Zig)
# This script simplifies the build process for Linux developers

set -e

echo "========================================"
echo "YimMenuV2 Build Script (Cross-compile)"
echo "========================================"
echo ""

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
    echo "ERROR: CMake is not installed"
    echo "Install with: sudo apt install cmake"
    exit 1
fi

# Check if Ninja is installed
if ! command -v ninja &> /dev/null; then
    echo "ERROR: Ninja is not installed"
    echo "Install with: sudo apt install ninja-build"
    exit 1
fi

# Check if Zig is installed
if ! command -v zig &> /dev/null; then
    echo "ERROR: Zig is not installed"
    echo "Please install Zig from https://ziglang.org/download/"
    exit 1
fi

# Default build type
BUILD_TYPE="${1:-RelWithDebInfo}"

echo "Build type: $BUILD_TYPE"
echo ""

# Create build directory
mkdir -p build

# Configure CMake project
echo "Configuring CMake project..."
cmake -DUSE_CROSSCOMPILER=Zig -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -S . -B build -G Ninja

echo ""
echo "Building project..."
cmake --build ./build --config "$BUILD_TYPE" --target YimMenuV2

echo ""
echo "========================================"
echo "Build completed successfully!"
echo "========================================"
echo "Output: build/libYimMenuV2.dll"
echo "PDB: build/libYimMenuV2.pdb"
echo ""

exit 0
