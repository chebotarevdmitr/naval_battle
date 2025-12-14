cmake_minimum_required(VERSION 3.16)
project(naval_battle VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем поддержку Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Ищем Qt6 с Quick-компонентами
find_package(Qt6 REQUIRED COMPONENTS Core Quick QuickControls2 Multimedia)

# Исходники
set(SOURCES
    src/core/Game.cpp
    src/gui/main.cpp
    qml.qrc  # ← ресурсный файл QML (создадим его позже)
)

# Исполняемый файл
add_executable(naval_battle ${SOURCES})

# Заголовки
target_include_directories(naval_battle PRIVATE src/core)

# Линковка
target_link_libraries(naval_battle
    Qt6::Core
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Multimedia
)