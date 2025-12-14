cmake_minimum_required(VERSION 3.16)
project(naval_battle VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем автоматическую обработку Qt (MOC, RCC, UIC)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Ищем Qt6 с необходимыми модулями
find_package(Qt6 REQUIRED COMPONENTS Core Quick Multimedia)

# Указываем все исходные файлы
set(SOURCES
    src/core/Game.cpp
    src/gui/main.cpp
    qml.qrc
)

# Создаём исполняемый файл
add_executable(naval_battle ${SOURCES})

# Говорим компилятору, где искать заголовочные файлы
target_include_directories(naval_battle PRIVATE src/core)

# Подключаем библиотеки Qt
target_link_libraries(naval_battle
    Qt6::Core
    Qt6::Quick
    Qt6::Multimedia
)