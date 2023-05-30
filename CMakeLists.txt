cmake_minimum_required(VERSION 3.21)

project(
    "sdl-tutorials"
    VERSION 0.1.0
    LANGUAGES C CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(USE_SDL_MIXER "Use SDL mixer." ON)

option(ENABLE_WARNINGS "Enable to add warnings to a target." ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable to treat warnings as errors." OFF)

option(ENABLE_TESTING "Enable a Unit Testing build." ON)

option(ENABLE_CLANG_TIDY "Enable to add clang tidy." OFF)

option(ENABLE_SANITIZE_ADDR "Enable address sanitize." OFF)
option(ENABLE_SANITIZE_UNDEF "Enable undefined sanitize." OFF)
option(ENABLE_SANITIZE_LEAK "Enable leak sanitize (Gcc/Clang only)." OFF)
option(ENABLE_SANITIZE_THREAD "Enable thread sanitize (Gcc/Clang only)." OFF)

option(ENABLE_CLANG_FORMAT "Enable to add clang-format." ON)
option(ENABLE_CMAKE_FORMAT "Enable to add cmake-format." ON)

option(ENABLE_LTO "Enable to add Link Time Optimization." ON)

# Project/Library Names
set(LIBRARY_NAME "lib")
set(UNIT_TEST_NAME "unit_tests")
set(EXECUTABLE_NAME "main")

# CMAKE MODULES
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
include(ConfigSafeGuards)
include(AddGitSubmodule)
include(Docs)
include(Tools)

if(ENABLE_WARNINGS)
    include(Warnings)
endif()

add_cmake_format_target()
add_clang_format_target()

if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEF)
    include(Sanitizer)
    add_sanitizer_flags()
endif()

if(ENABLE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()

if(ENABLE_LTO)
    include(LTO)
endif()

# EXTERNAL LIBRARIES
include(CPM)
CPMAddPackage("gh:fmtlib/fmt#9.1.0")
CPMAddPackage("gh:nlohmann/json@3.11.2")
CPMAddPackage("gh:catchorg/Catch2@2.13.9")
CPMAddPackage("gh:jarro2783/cxxopts@3.1.1")
#CPMAddPackage("gh:gabime/spdlog@1.11.0")

CPMAddPackage(
  GITHUB_REPOSITORY gabime/spdlog
  VERSION 1.11.0
  OPTIONS
  "SPDLOG_FMT_EXTERNAL YES"
  "SPDLOG_INSTALL NO"
  "SPDLOG_BUILD_EXAMPLE NO"
  "SPDLOG_BUILD_SHARED NO"
  "SPDLOG_BUILD_TESTS NO"
)

CPMAddPackage(
  GITHUB_REPOSITORY libsdl-org/SDL
  GIT_TAG release-2.26.3
  OPTIONS
  "SDL2_DISABLE_UNINSTALL NO"
  "SDL_SHARED NO"
  "SDL_SHARED_ENABLED_BY_DEFAULT NO"
  "SDL_STATIC YES"
  "SDL_STATIC_ENABLED_BY_DEFAULT YES"
  "SDL_TEST NO"
  "SDL_TEST_ENABLED_BY_DEFAULT NO"
  "SDL2_IMAGE_INSTALL NO"
  "SDL2_DISABLE_INSTALL NO"
)

CPMAddPackage(
  GITHUB_REPOSITORY libsdl-org/SDL_image
  GIT_TAG release-2.6.3
  OPTIONS
  "BUILD_SHARED_LIBS NO"
  "SDL2IMAGE_SAMPLES NO"
)

CPMAddPackage(
  GITHUB_REPOSITORY libsdl-org/SDL_mixer
  GIT_TAG release-2.6.3
  OPTIONS
  "BUILD_SHARED_LIBS NO"
  "SDL2MIXER_SAMPLES NO"
  "SDL2MIXER_DEPS_SHARED NO"
  "SDL2MIXER_BUILD_SHARED_LIBS NO"
  #"SDL2MIXER_VENDORED NO"
  "SDL2MIXER_MOD NO"
  "SDL2MIXER_FLAC NO"
  "SDL2MIXER_OPUS NO"
  "SDL2MIXER_OPUS_SHARED NO"
  "SDL2MIXER_VORBIS_VORBISFILE_SHARED NO"
)

CPMAddPackage(
  GITHUB_REPOSITORY libsdl-org/SDL_ttf
  GIT_TAG release-2.20.2
  OPTIONS
  "BUILD_SHARED_LIBS NO"
  "SDL2TTF_SAMPLES NO"
)

CPMAddPackage(
  GITHUB_REPOSITORY libsdl-org/SDL_net
  GIT_TAG release-2.2.0
  OPTIONS
  "BUILD_SHARED_LIBS NO"
  "SDL2NET_SAMPLES NO"
)

# SUB DIRECTORIES

add_subdirectory(configured)
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tutorials)
add_subdirectory(tests)

# INSTALL TARGETS

install(
    TARGETS ${EXECUTABLE_NAME}
    EXPORT ${LIBRARY_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(
    TARGETS ${LIBRARY_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib)
