cmake_minimum_required(VERSION 3.25)
project(KetamineMenu VERSION 0.4.8 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Static CRT: friends need no VC++ redistributable.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
# /EHa: the overlay catches exceptions with __try (Guarded); C++ destructors, and so mutex unlocks, must still run.
string(REPLACE "/EHsc" "/EHa" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include(FetchContent)
# Pinned archives + hashes. SOURCE_SUBDIR points nowhere so we only download and build the files we pick below.
FetchContent_Declare(imgui
    URL https://github.com/ocornut/imgui/archive/refs/tags/v1.92.9.tar.gz
    URL_HASH SHA256=af97ed649182c39314320514a672b82008ab462b9293fe23d37b30bfa5d05519
    SOURCE_SUBDIR none)
FetchContent_Declare(minhook
    URL https://github.com/TsudaKageyu/minhook/archive/refs/tags/v1.3.4.tar.gz
    URL_HASH SHA256=1aebeae4ca898330c507860acc2fca2eb335fe446a3a2b8444c3bf8b2660a14e
    SOURCE_SUBDIR none)
FetchContent_MakeAvailable(imgui minhook)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_dx12.cpp)
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends)
# ImGui's default IME handler talks to the game window from the render thread: we don't need IME.
target_compile_definitions(imgui PUBLIC IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS)

add_library(minhook STATIC
    ${minhook_SOURCE_DIR}/src/buffer.c
    ${minhook_SOURCE_DIR}/src/hook.c
    ${minhook_SOURCE_DIR}/src/trampoline.c
    ${minhook_SOURCE_DIR}/src/hde/hde64.c)
target_include_directories(minhook PUBLIC ${minhook_SOURCE_DIR}/include)

# The game statically imports winmm.dll, so a winmm.dll next to the exe is loaded at startup.
add_library(KetamineMenu SHARED src/dllmain.cpp src/overlay.cpp src/menu.cpp src/ue.cpp src/features.cpp src/esp.cpp src/lang.cpp src/resources.rc)
set_target_properties(KetamineMenu PROPERTIES OUTPUT_NAME winmm)
target_compile_definitions(KetamineMenu PRIVATE KM_VERSION="${PROJECT_VERSION}" WIN32_LEAN_AND_MEAN NOMINMAX)
target_compile_options(KetamineMenu PRIVATE /W4 /utf-8)
option(KM_DUMPER "Dev build that loads Dumper-7.dll from the game folder (SDK re-dump after a patch)" OFF)
if(KM_DUMPER)
    target_compile_definitions(KetamineMenu PRIVATE KM_DUMPER)
endif()
target_link_libraries(KetamineMenu PRIVATE imgui minhook dxgi delayimp)
# Load these only when the overlay initialises, not at game startup.
target_link_options(KetamineMenu PRIVATE /DELAYLOAD:d3dcompiler_47.dll /DELAYLOAD:dxgi.dll)

enable_testing()
add_executable(proxy_test tests/proxy_test.cpp)
add_test(NAME proxy_test COMMAND proxy_test $<TARGET_FILE:KetamineMenu>)

# Minimal DX11/DX12 app that loads the DLL, toggles the menu and saves a screenshot (manual check of the overlay).
add_executable(overlay_host tests/overlay_host.cpp)
target_link_libraries(overlay_host PRIVATE d3d11 d3d12 dxgi)
