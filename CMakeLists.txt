cmake_minimum_required(VERSION 3.16)
project(laba8_dop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Widgets Concurrent REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Concurrent REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    filesearcher.cpp
)

set(PROJECT_HEADERS
    mainwindow.h
    filesearcher.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(laba8_dop
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        mainwindow.ui
    )
else()
    add_executable(laba8_dop
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
    )
endif()

target_link_libraries(laba8_dop PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Concurrent
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(laba8_dop)
endif()
