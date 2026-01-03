# ============================================================
# Cross-compilation settings (clang-cl / MSVC ABI via msvc-wine)
# ============================================================

if(WIN32 OR CYGWIN)
    set(CROSSCOMPILE_DEFAULT OFF)
else()
    set(CROSSCOMPILE_DEFAULT ON)
endif()

option(CROSSCOMPILE "Enable cross-compilation using clang-cl (MSVC ABI)" ${CROSSCOMPILE_DEFAULT})

if(CROSSCOMPILE)
    message(STATUS "Cross-compile is enabled (clang-cl / MSVC ABI).")

    # ------------------------------------------------------------
    # Target system
    # ------------------------------------------------------------
    set(CMAKE_SYSTEM_NAME Windows)
    set(CMAKE_SYSTEM_PROCESSOR x86_64)

    # ------------------------------------------------------------
    # Locate clang-cl
    # ------------------------------------------------------------
    find_program(CLANG_CL_EXECUTABLE clang-cl)
    if(NOT CLANG_CL_EXECUTABLE)
        message(FATAL_ERROR "clang-cl not found. Install LLVM.")
    endif()

    set(CMAKE_C_COMPILER   ${CLANG_CL_EXECUTABLE} CACHE STRING "" FORCE)
    set(CMAKE_CXX_COMPILER ${CLANG_CL_EXECUTABLE} CACHE STRING "" FORCE)
    set(CMAKE_LINKER       lld-link              CACHE STRING "" FORCE)

    set(CMAKE_C_COMPILER_TARGET   x86_64-pc-windows-msvc)
    set(CMAKE_CXX_COMPILER_TARGET x86_64-pc-windows-msvc)

    # ------------------------------------------------------------
    # MSVC runtime
    # ------------------------------------------------------------
    set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded)

    # ------------------------------------------------------------
    # msvc-wine root (CHANGE IF NEEDED)
    # ------------------------------------------------------------
    set(MSVC_WINE_ROOT "$ENV{HOME}/my_msvc")

    if(NOT EXISTS "${MSVC_WINE_ROOT}/bin")
        message(FATAL_ERROR
            "msvc-wine not found at ${MSVC_WINE_ROOT}\n"
            "Install it using https://github.com/mstorsjo/msvc-wine"
        )
    endif()

    message(STATUS "Using msvc-wine at: ${MSVC_WINE_ROOT}")

    # ------------------------------------------------------------
    # Inject MSVC + Windows SDK paths
    # ------------------------------------------------------------
    file(GLOB MSVC_LIB_DIR "${MSVC_WINE_ROOT}/lib/*/x64")
    file(GLOB MSVC_INC_DIR "${MSVC_WINE_ROOT}/include/*")

    set(ENV{LIB}     "${MSVC_LIB_DIR}")
    set(ENV{INCLUDE} "${MSVC_INC_DIR}")
    set(ENV{PATH}    "${MSVC_WINE_ROOT}/bin:$ENV{PATH}")

    # ------------------------------------------------------------
    # Disable MinGW / Unix search behavior
    # ------------------------------------------------------------
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)

    # ------------------------------------------------------------
    # Compiler flags (safe for DLL injection)
    # ------------------------------------------------------------
    add_compile_options(
        /EHsc
        /permissive-
        /Zc:__cplusplus
        /Zc:inline
        /GS-
    )

    # ------------------------------------------------------------
    # Linker flags
    # ------------------------------------------------------------
    add_link_options(
        /NOLOGO
        /INCREMENTAL:NO
    )

    message(STATUS "clang-cl + msvc-wine toolchain configured successfully.")
endif()