cmake_minimum_required(VERSION 3.16)
project(naval_battle VERSION 0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Важно: включить AUTOMOC ДО find_package
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Говорим CMake, где заголовки
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Явно указываем исходники
file(GLOB_RECURSE SOURCES
    src/*.cpp
    include/*.h
)

add_executable(naval_battle ${SOURCES})

# Говорим, что заголовки в include/
target_include_directories(naval_battle PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(naval_battle Qt6::Core Qt6::Widgets)