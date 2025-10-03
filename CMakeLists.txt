cmake_minimum_required(VERSION 3.30)
project(CSApp LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt5 COMPONENTS Core Network REQUIRED)

add_subdirectory(server)
add_subdirectory(client)
