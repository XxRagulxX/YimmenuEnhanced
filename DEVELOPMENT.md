# Development Guide

This guide provides detailed information for developers working on YimMenuV2.

## Table of Contents

- [Environment Setup](#environment-setup)
- [Building the Project](#building-the-project)
- [Project Architecture](#project-architecture)
- [Debugging](#debugging)
- [Common Development Tasks](#common-development-tasks)
- [Troubleshooting](#troubleshooting)

## Environment Setup

### Windows Development

#### Required Tools

1. **Visual Studio 2022** (or newer)
   - Install "Desktop development with C++" workload
   - Ensure Clang tools are installed

2. **CMake** (3.20+)
   - Download from https://cmake.org/download/
   - Add to system PATH

3. **Ninja Build System**
   - Download from https://ninja-build.org/
   - Add to system PATH

4. **Git**
   - Download from https://git-scm.com/

#### Recommended Tools

- **Visual Studio Code** with C++ extensions
- **clang-format** for code formatting
- **clangd** for language server support

### Linux Development (Cross-Compilation)

#### Required Tools

```bash
sudo apt update
sudo apt install -y cmake ninja-build git
```

#### Zig Compiler

Follow the installation instructions at https://ziglang.org/download/

For Ubuntu/Debian:
```bash
wget https://ziglang.org/download/[version]/zig-linux-x86_64-[version].tar.xz
tar -xf zig-linux-x86_64-[version].tar.xz
sudo mv zig-linux-x86_64-[version] /opt/zig
echo 'export PATH=$PATH:/opt/zig' >> ~/.bashrc
source ~/.bashrc
```

## Building the Project

### Quick Build

#### Windows
```cmd
build.bat [BuildType]
```

#### Linux
```bash
./build.sh [BuildType]
```

Build types: `Debug`, `Release`, `RelWithDebInfo` (default)

### Manual Build

#### Windows (Clang)

```cmd
# Configure
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=RelWithDebInfo -S . -B build -G Ninja

# Build
cmake --build ./build --config RelWithDebInfo --target YimMenuV2
```

#### Linux (Cross-compile)

```bash
# Configure
cmake -DUSE_CROSSCOMPILER=Zig -DCMAKE_BUILD_TYPE=RelWithDebInfo -S . -B build -G Ninja

# Build
cmake --build ./build --config RelWithDebInfo --target YimMenuV2
```

### Clean Build

```bash
# Remove build directory
rm -rf build

# Reconfigure and build
[run build commands again]
```

## Project Architecture

### Directory Structure

```
YimmenuEnhanced/
├── src/
│   ├── core/              # Core framework
│   │   ├── backend/       # Core systems
│   │   ├── commands/      # Command system
│   │   ├── frontend/      # UI framework
│   │   ├── hooking/       # Hook management
│   │   ├── memory/        # Memory utilities
│   │   ├── renderer/      # Rendering system
│   │   └── scripting/     # Lua scripting
│   ├── game/              # Game-specific code
│   │   ├── backend/       # Game state management
│   │   ├── commands/      # Game commands
│   │   ├── features/      # Feature implementations
│   │   ├── frontend/      # Game UI
│   │   ├── gta/           # GTA-specific code
│   │   └── hooks/         # Game hooks
│   └── types/             # Type definitions
├── cmake/                 # CMake modules
└── .github/               # CI/CD workflows
```

### Key Components

#### Command System

Commands are the primary way to implement features:

- **Command**: One-time execution
- **LoopedCommand**: Executes every frame when enabled

#### Hook System

Hooks intercept game functions to add functionality:

- Located in `src/game/hooks/`
- Organized by category (GUI, Network, Script, etc.)
- Use MinHook for implementation

#### Script System

Manages game scripts:

- Fiber-based execution
- Lua scripting support
- Native function hooking

## Debugging

### Visual Studio

1. Set up the debugger to attach to GTA5.exe
2. Build with `Debug` or `RelWithDebInfo` configuration
3. Use breakpoints in the code
4. Inject the DLL after attaching the debugger

### Logging

The project uses AsyncLogger for logging:

```cpp
LOG(INFO) << "Information message";
LOG(WARNING) << "Warning message";
LOG(ERROR) << "Error message";
LOGF(INFO, "Formatted: {}", value);
```

Logs are saved to `%appdata%/YimMenuV2/cout.log`

### Common Debugging Scenarios

#### Crash on Injection

1. Check logs in `%appdata%/YimMenuV2/cout.log`
2. Verify game version compatibility
3. Ensure BattlEye is disabled
4. Try different injection methods

#### Feature Not Working

1. Add logging to track execution
2. Verify hook is being called
3. Check pointer validity
4. Test in single-player vs online

## Common Development Tasks

### Adding a New Feature

1. Create files in appropriate `src/game/features/` subdirectory
2. Implement as a Command or LoopedCommand
3. Register in the appropriate initialization code
4. Add to the GUI if needed
5. Test thoroughly

### Adding a New Hook

1. Identify the game function to hook
2. Create hook file in `src/game/hooks/`
3. Implement the hook function
4. Register in `Hooking::Init()`
5. Document the hook's purpose

### Updating Dependencies

Dependencies are managed via CMake modules in `cmake/`:

1. Update the corresponding CMake file
2. Test the build
3. Verify compatibility

## Troubleshooting

### Build Errors

#### "CMake not found"
- Ensure CMake is installed and in PATH
- Restart terminal/IDE after installation

#### "Clang not found"
- Install Clang via Visual Studio Installer
- Or use MSVC by removing `-DCMAKE_C_COMPILER` flags

#### "Ninja not found"
- Install Ninja and add to PATH
- Or use different generator: `-G "Visual Studio 17 2022"`

### Runtime Errors

#### "DLL failed to inject"
- Ensure GTA V is running
- BattlEye must be disabled
- Try different injector
- Check DLL architecture matches game (x64)

#### "Game crashes on injection"
- Update to latest game version
- Check logs for error messages
- Try Debug build for more information
- Verify all dependencies are loaded

### Performance Issues

#### Slow execution
- Use Release build for testing
- Check for inefficient loops
- Profile with a profiler
- Optimize hot paths

### Code Quality Issues

#### Many compiler warnings
- Fix warnings one by one
- Use Clang for better diagnostics
- Follow coding standards

#### Formatting issues
- Use `.clang-format` configuration
- Run clang-format on changed files
- Configure editor to format on save

## Additional Resources

- [CMake Documentation](https://cmake.org/documentation/)
- [Clang Documentation](https://clang.llvm.org/docs/)
- [ImGui Documentation](https://github.com/ocornut/imgui)
- [MinHook Documentation](https://github.com/TsudaKageyu/minhook)

## Getting Help

If you encounter issues not covered here:

1. Check existing GitHub issues
2. Review the code for similar implementations
3. Ask in discussions or open a new issue
4. Provide detailed information (logs, steps to reproduce, environment)
