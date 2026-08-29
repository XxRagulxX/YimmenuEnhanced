include(FetchContent)

set(LIB_NAME "directxtk12")
message(STATUS "Setting up ${LIB_NAME}")

# DirectXTK12 is used as the drawing primitives layer for the new
# Stand-style custom renderer (src/Rendering/). It's DirectX12-native,
# unlike DirectXTK (D3D11), which is what stand-reference itself uses.
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(BUILD_FUZZING OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(BUILD_XAUDIO_WIN10 OFF CACHE BOOL "" FORCE)
set(BUILD_XAUDIO_REDIST OFF CACHE BOOL "" FORCE)
set(BUILD_GAMEINPUT OFF CACHE BOOL "" FORCE)
set(BUILD_WGI OFF CACHE BOOL "" FORCE)
set(BUILD_XINPUT OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    ${LIB_NAME}
    GIT_REPOSITORY https://github.com/microsoft/DirectXTK12.git
    GIT_TAG        may2026
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(${LIB_NAME})
