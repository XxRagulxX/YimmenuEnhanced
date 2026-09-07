@echo off
rem Activates the x64 Visual Studio developer environment - sets INCLUDE,
rem LIB and PATH so both cl.exe and clang-cl.exe can find the MSVC/Windows
rem SDK headers and libs - for every cmake/ninja invocation CMake Tools
rem makes, via the "cmake.environmentSetupScript" setting in
rem .vscode/settings.json.
rem
rem Needed because CMakePresets.json's toolset/architecture "external"
rem strategy - used here purely for compiler detection at configure time -
rem turns out to be a Visual-Studio-IDE-only integration. VS reads a
rem VSInheritEnvironments.txt marker it writes next to the CMake cache and
rem activates the matching environment itself before invoking cmake/ninja.
rem VS Code's CMake Tools has no equivalent for that file and just runs
rem cmake/ninja in whatever environment it was launched in, which is why a
rem build from VS Code failed with "Cannot open include file: windows.h"
rem even though configure itself succeeded.
rem
rem Resolved via vswhere, Visual Studio's own installation-query tool, not
rem a hardcoded path, so this keeps working across VS updates without
rem editing this file. vswhere.exe ships alongside every VS instance but
rem isn't on PATH by default - vcvarsall.bat needs it reachable, so its
rem directory is added first.
rem
rem Deliberately no setlocal here - CMake Tools calls this script expecting
rem its environment changes (and vcvars64.bat's own, below) to persist
rem into the calling process for every subsequent cmake/ninja invocation,
rem the exact same way opening a real "Developer Command Prompt" works.
set "PATH=C:\Program Files (x86)\Microsoft Visual Studio\Installer;%PATH%"
set "VSWHERE=C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"

if not exist "%VSWHERE%" (
    echo [vcvars64.bat] vswhere.exe not found at "%VSWHERE%" - install Visual Studio, or edit this script if it moved. 1>&2
    exit /b 1
)

for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -prerelease -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
    set "VSINSTALLPATH=%%i"
)

if not defined VSINSTALLPATH (
    echo [vcvars64.bat] No Visual Studio installation with the "Desktop development with C++" VC.Tools.x86.x64 component was found. 1>&2
    exit /b 1
)

call "%VSINSTALLPATH%\VC\Auxiliary\Build\vcvars64.bat"

rem This machine has NoDefaultCurrentDirectoryInExePath set (a Windows
rem security hardening variable that stops CreateProcess/cmd.exe from
rem implicitly searching the current directory for a bare command name -
rem see Microsoft KB Q156276). DirectXTK12's own vendored CMakeLists.txt
rem (fetched by cmake/directxtk12.cmake) runs its shader-compile step as
rem "cmake -E env ... CompileShaders.cmd ARGS..." - a bare relative name,
rem no ".\" prefix - which needs exactly that implicit current-directory
rem search to resolve, and fails with a bare "no such file or directory"
rem otherwise. Clearing it only for this script's own child-process tree
rem (cmake/ninja and whatever they spawn for this one project's build),
rem not the system/user-wide setting, so nothing else on this machine
rem loses that hardening.
set "NoDefaultCurrentDirectoryInExePath="
