cmake_minimum_required(VERSION 3.30)
project(SpookyHouse)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++17")

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

file(GLOB_RECURSE sources
        "${CMAKE_SOURCE_DIR}/src/*.c"
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        )

add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/headers")
