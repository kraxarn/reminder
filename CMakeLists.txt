cmake_minimum_required(VERSION 3.5)
project(reminder LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

file(GLOB PROJECT_SOURCES "src/*.[hc]pp")

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(reminder MANUAL_FINALIZATION ${PROJECT_SOURCES})
else ()
	if (ANDROID)
		add_library(reminder SHARED ${PROJECT_SOURCES})
	else ()
		add_executable(reminder ${PROJECT_SOURCES})
	endif ()
endif ()

target_link_libraries(reminder PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if (QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(reminder)
endif ()
