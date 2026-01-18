cmake_minimum_required(VERSION 3.1.0)

project(EventLoop VERSION 2.0.0)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

find_package(Threads REQUIRED)

include_directories(include)

# INCLUDES variable defines the headers required by apps using this library
set(INCLUDES
    include/Event.h
    include/EventLoop.h)
set(SOURCES
    src/Event.cpp
    src/EventLoop.cpp
    src/EventManager.cpp
    src/EventSender.cpp
    src/EventReceiver.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_library(${PROJECT_NAME} SHARED
    ${INCLUDES}
    ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME ${PROJECT_NAME}
    CXX_STANDARD_REQUIRED YES
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

# --------------------
# Tests
# --------------------

add_executable(EventLoopTests
    tests/EventLoopBasicTest.cpp
)	

target_link_libraries(EventLoopTests
    PRIVATE
    gtest
    gtest_main
    EventLoop
)

add_test(
    NAME EventLoopBasicTest
    COMMAND EventLoopTests
)

