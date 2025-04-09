cmake_minimum_required(VERSION 3.21) #I picked this version at random for real
project(EscapeSerge LANGUAGES CXX) #Yes, that's the name. Deal with it!

set(CMAKE_CXX_STANDARD 17) #Features will continue untill morale improves.
set(CMAKE_CXX_STANDARD_REQUIRED ON) #You'll have your features and you will enjoy it!

set(CMAKE_AUTOMOC ON) #Qt MOC
set(CMAKE_AUTOUIC ON) #Qt UI files compiler
set(CMAKE_AUTORCC ON) #Qt qrc files compiler

find_package(Qt6 REQUIRED COMPONENTS Widgets) # Yes, we do really need it

qt_standard_project_setup() #We're "standard" alright!

file(GLOB SRC_FILES src/*) #source files, ui files, and qrc files
file(GLOB HEADERS include/*) #headers, just headers
include_directories(include/) #so that #include "header.h" resolves properly

set(PROJECT_SOURCES #fuck it! it all needs to be processed anyway.
  ${SRC_FILES} #SOURCES
  ${HEADERS} #HEADERS
) #AND EVERYTHING NICE

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES}
    src/lockCirculaire.cpp
    include/loclCirculaire.h
    include/lockCirculaireTile.h
    src/lockCirculaire_tile.cpp) #CHEMICAL Q

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Widgets #No Qt, no bueno
)

