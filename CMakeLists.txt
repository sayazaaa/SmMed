cmake_minimum_required(VERSION 3.5)

project(demo VERSION 0.1 LANGUAGES CXX)
set(CMAKE_OSX_ARCHITECTURES "x86_64")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)


add_executable(smmed
    ${PROJECT_SOURCES}
)

target_link_libraries(smmed PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

