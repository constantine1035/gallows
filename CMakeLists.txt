cmake_minimum_required(VERSION 3.24)
project(gallows)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(gallows main.cpp gallows.cpp)
target_link_libraries(gallows PRIVATE sfml-graphics)
target_compile_features(gallows PRIVATE cxx_std_17)

install(TARGETS gallows)
