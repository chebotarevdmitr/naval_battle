cmake_minimum_required(VERSION 3.16)
project(naval_battle VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматическая обработка Qt (MOC, RCC, UIC)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Найти Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Quick Multimedia)

# Список исходников
set(SOURCES
    src/core/Game.cpp
    src/gui/main.cpp
    qml.qrc
)

# Исполняемый файл
add_executable(naval_battle ${SOURCES})

# Указать, где искать заголовки
target_include_directories(naval_battle PRIVATE ${CMAKE_SOURCE_DIR}/src/core)

# Подключить библиотеки Qt
target_link_libraries(naval_battle
    Qt6::Core
    Qt6::Quick
    Qt6::Multimedia
)