# YimMenuV2 - Enhanced Edition

Experimental menu for GTA 5: Enhanced

[![CI](https://github.com/XxRagulxX/YimmenuEnhanced/workflows/CI/badge.svg)](https://github.com/XxRagulxX/YimmenuEnhanced/actions)

## Table of Contents

- [Features](#features)
- [How to Use](#how-to-use)
- [Building from Source](#building-from-source)
- [Development](#development)
- [How to Open the Menu](#how-to-open-the-menu)
- [Common Issues](#common-issues)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Modern C++23** implementation optimized for performance
- **Comprehensive hooks** for game modification
- **Lua scripting** support for custom features
- **User-friendly GUI** built with ImGui
- **Command system** with hotkey support
- **Save/load functionality** for locations and settings

## How to Use

1. Download the latest version of FSL from [here](https://www.unknowncheats.me/forum/grand-theft-auto-v/616977-fsl-local-gtao-saves.html) and place version.dll in your GTA V directory. Using FSL is now optional but highly recommended for account safety
2. Download YimMenuV2 from [GitHub Releases](https://github.com/YimMenu/YimMenuV2/releases/tag/nightly)
3. Download an injector, such as [Xenos](https://www.unknowncheats.me/forum/general-programming-and-reversing/124013-xenos-injector-v2-3-2-a.html)
4. Open Rockstar Launcher, select Grand Theft Auto V Enhanced, go to settings, and disable BattlEye. If you are using Steam or Epic Games, you may have to pass the -nobattleye command line parameter as well
5. Launch GTA V, then use your injector to inject YimMenuV2.dll at the main menu

## Building from Source

### Prerequisites

- **CMake** 3.20 or higher
- **C++23 compatible compiler**:
  - Clang (recommended)
  - MSVC with C++23 support
- **Ninja** build system
- **Git** for cloning the repository

### Windows (Native Compilation)

```bash
# Clone the repository
git clone https://github.com/XxRagulxX/YimmenuEnhanced.git
cd YimmenuEnhanced

# Setup MSVC environment (if using Visual Studio)
# Run from Developer Command Prompt for VS 2022

# Generate CMake project
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=RelWithDebInfo -S . -B build -G Ninja

# Build the DLL
cmake --build ./build --config RelWithDebInfo --target YimMenuV2
```

The built DLL will be in `build/YimMenuV2.dll`

### Linux (Cross-Compilation with Zig)

```bash
# Install dependencies
sudo apt update
sudo apt install -y cmake ninja-build

# Setup Zig (follow instructions at https://ziglang.org/download/)

# Generate CMake project
cmake -DUSE_CROSSCOMPILER=Zig -DCMAKE_BUILD_TYPE=RelWithDebInfo -S . -B build -G Ninja

# Build the DLL
cmake --build ./build --config RelWithDebInfo --target YimMenuV2
```

The built DLL will be in `build/libYimMenuV2.dll`

### Build Configurations

- **RelWithDebInfo**: Optimized build with debug symbols (recommended for development)
- **Release**: Fully optimized build without debug symbols
- **Debug**: Debug build with all symbols (slower execution)

## Development

### Project Structure

```
YimmenuEnhanced/
├── src/
│   ├── core/          # Core framework features
│   ├── game/          # Game-specific implementations
│   └── types/         # Type definitions
├── cmake/             # CMake modules
├── .github/           # GitHub Actions workflows
└── docs/              # Documentation (if available)
```

### Code Style

- Use Clang for compilation to catch more warnings
- Follow C++23 best practices
- Use `std::string_view` for immutable string parameters
- Prefer `std::to_array` for constexpr arrays
- Use `static_cast`/`reinterpret_cast` instead of C-style casts
- Format code using the provided `.clang-format` file

### Adding New Features

All new features should be implemented as `Command` objects:
- See `game/features/self/` for examples
- Normal commands: One-time execution
- Looped commands: Execute every frame

## How to Open the Menu

Press the `INSERT` key or `Ctrl+\` to open the menu

## Common Issues

### I keep getting desynced from public sessions every five minutes

We currently do not have a BattlEye bypass, and legitimate hosts will eventually remove you due to a heartbeat failure. There is currently no way to stop this other than using an actual (private) bypass

### I removed FSL and all my progress disappeared!

FSL reroutes account save data to disk, so any progress made with FSL will only show up if you have FSL enabled. If you don't want this, you can also use YimMenuV2 without FSL, but this is not recommended

### I removed FSL and the game doesn't start up anymore

This is a known issue; delete "Documents/GTAV Enhanced/Profiles" to fix

## Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

**Important**: PRs containing AI-generated code will NOT BE ACCEPTED!

## Documentation

- **[Quick Start Guide](QUICKSTART.md)** - Get started in minutes
- **[Development Guide](DEVELOPMENT.md)** - Comprehensive development documentation
- **[Contributing Guidelines](CONTRIBUTING.md)** - How to contribute
- **[Security Policy](SECURITY.md)** - Security best practices and reporting
- **[Changelog](CHANGELOG.md)** - Project history and changes

## License

This project is licensed under the terms specified in [LICENSE](LICENSE).