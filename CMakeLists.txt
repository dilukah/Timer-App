cmake_minimum_required(VERSION 3.16)

project(CountdownTimer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

set(TS_FILES CountdownTimer_en_FI.ts)
enable_testing(true)

add_library(CountdownTimer SHARED
  main.cpp
  countdowntimer.cpp
  countdowntimer.h
  countdowntimer.ui
  ${TS_FILES}
  style.qss
)


target_link_libraries(CountdownTimer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(CountdownTimer PROPERTIES
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CountdownTimer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CountdownTimer)
endif()


# new executable for the tests
add_executable(UnitTests UnitTests/Tests.cpp)

# adding the test to CTest
add_test(NAME ApiTest COMMAND ApiTest)

# link library to test code
#target_link_libraries(UnitTests PRIVATE Qt${QT_VERSION_MAJOR}::Test CountdownTimer)
target_link_libraries(UnitTests PRIVATE Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::Widgets CountdownTimer)
