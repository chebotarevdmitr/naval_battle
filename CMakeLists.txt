# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(naval_battle VERSION 0.1 LANGUAGES CXX)

# Требуем C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исполняемый файл из src/
add_executable(naval_battle src/main.cpp)

# (Опционально) Указываем, куда ставить бинарник
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)