# Quick Start Guide

Get up and running with YimMenuV2 development in minutes!

## For Users

### Installation (5 minutes)

1. **Download Prerequisites**
   - [FSL](https://www.unknowncheats.me/forum/grand-theft-auto-v/616977-fsl-local-gtao-saves.html) (optional but recommended)
   - [YimMenuV2 DLL](https://github.com/YimMenu/YimMenuV2/releases/tag/nightly)
   - [Xenos Injector](https://www.unknowncheats.me/forum/general-programming-and-reversing/124013-xenos-injector-v2-3-2-a.html)

2. **Setup**
   - Install FSL's version.dll to GTA V directory
   - Disable BattlEye in Rockstar Launcher settings
   - Launch GTA V

3. **Inject**
   - At main menu, use Xenos to inject YimMenuV2.dll
   - Press `INSERT` or `Ctrl+\` to open menu

## For Developers

### First Time Setup (15 minutes)

#### Windows

```cmd
# 1. Install prerequisites
# - Visual Studio 2022 with C++ and Clang
# - CMake (https://cmake.org/download/)
# - Ninja (https://ninja-build.org/)

# 2. Clone repository
git clone https://github.com/XxRagulxX/YimmenuEnhanced.git
cd YimmenuEnhanced

# 3. Build
build.bat

# Output: build\YimMenuV2.dll
```

#### Linux (Cross-compile)

```bash
# 1. Install prerequisites
sudo apt install cmake ninja-build git

# Install Zig from https://ziglang.org/download/

# 2. Clone repository
git clone https://github.com/XxRagulxX/YimmenuEnhanced.git
cd YimmenuEnhanced

# 3. Build
chmod +x build.sh
./build.sh

# Output: build/libYimMenuV2.dll
```

### Making Your First Change (30 minutes)

1. **Find an example feature**
   ```bash
   # Look at existing features
   ls src/game/features/self/
   ```

2. **Create new feature** (example: src/game/features/self/MyFeature.cpp)
   ```cpp
   #include "MyFeature.hpp"
   
   namespace YimMenu::Features
   {
       MyFeature g_MyFeature("my_feature", "My Feature");
       
       void MyFeature::OnCall()
       {
           LOG(INFO) << "My feature was called!";
           // Your feature code here
       }
   }
   ```

3. **Build and test**
   ```cmd
   build.bat RelWithDebInfo
   # Inject the new DLL and test
   ```

4. **Submit PR**
   - Create branch: `git checkout -b feature/my-feature`
   - Commit: `git commit -am "Add my feature"`
   - Push: `git push origin feature/my-feature`
   - Open PR on GitHub

## Next Steps

### For Users
- Read the full [README.md](README.md) for detailed usage
- Check [Common Issues](README.md#common-issues) if you have problems
- Join the community for support

### For Developers
- Read [DEVELOPMENT.md](DEVELOPMENT.md) for in-depth guide
- Check [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines
- Review existing code for patterns and examples
- Start with small changes to understand the codebase

## Quick Reference

### Useful Commands

```bash
# Build (default: RelWithDebInfo)
build.bat           # Windows
./build.sh          # Linux

# Build specific configuration
build.bat Debug
build.bat Release

# Clean build
rm -rf build
build.bat

# Check code
git status
git diff
```

### Important Files

- `src/main.cpp` - Entry point
- `src/common.hpp` - Common includes
- `src/game/features/` - Feature implementations
- `src/game/hooks/` - Game hooks
- `CMakeLists.txt` - Build configuration

### Key Shortcuts

- `INSERT` or `Ctrl+\` - Open menu in-game
- Various in-game hotkeys (configurable)

## Troubleshooting

### Build fails
- Ensure all prerequisites are installed
- Check CMake/Ninja are in PATH
- Try clean build: `rm -rf build`

### Injection fails
- Disable BattlEye
- Use correct DLL for your platform
- Try different injector
- Check antivirus isn't blocking

### Game crashes
- Check logs: `%appdata%/YimMenuV2/cout.log`
- Try Debug build for better error messages
- Verify game version compatibility

## Getting Help

- **Issues**: https://github.com/XxRagulxX/YimmenuEnhanced/issues
- **Documentation**: Check DEVELOPMENT.md and README.md
- **Code Examples**: Review existing features in src/game/features/

---

Ready to enhance the project? Start coding! 🚀
