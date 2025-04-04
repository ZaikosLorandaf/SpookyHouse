cmake_minimum_required(VERSION 3.21)
project(QtGuiApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

file(GLOB SRC_FILES src/*)
file(GLOB HEADERS include/*)
include_directories(include/)

set(PROJECT_SOURCES
  ${SRC_FILES}
  ${HEADERS}
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Widgets
)

