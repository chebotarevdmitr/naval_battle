cmake_minimum_required(VERSION 3.16)
project(naval_battle VERSION 0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Находим Qt6 с Multimedia (для звуков)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)

# Явно указываем все исходники
set(SOURCES
    src/game/Game.cpp
    src/gui/MainWindow.cpp
    src/gui/main.cpp
    include/game/Game.h
    include/gui/MainWindow.h
)

# Создаём исполняемый файл
add_executable(naval_battle ${SOURCES})

# Указываем, где искать заголовки
target_include_directories(naval_battle PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Линкуем с Qt
target_link_libraries(naval_battle Qt6::Core Qt6::Widgets Qt6::Multimedia)