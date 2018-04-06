cmake_minimum_required(VERSION 3.0)

project(ldf
        VERSION 1.0.0.0)

set(CMAKE_CXX_STANDARD 17)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INC_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(SRC_FILES
        ${INC_DIR}/base.h
        ${INC_DIR}/version.h
        ${INC_DIR}/Strings.h
        ${INC_DIR}/time/Date.h
        ${INC_DIR}/time/DateTime.h
        ${INC_DIR}/time/Time.h
        ${SRC_DIR}/time/Date.cpp
        ${SRC_DIR}/time/DateTime.cpp
        ${SRC_DIR}/time/Time.cpp
        ${SRC_DIR}/Strings.cpp
        )

configure_file(${INC_DIR}/version.tcc ${INC_DIR}/version.h)

add_library(ldf2 ${SRC_FILES})


# TEST
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${TEST_DIR})

set(TEST_SOURCES
        ${TEST_DIR}/main.cpp
        ${TEST_DIR}/time/testTime.cpp
        )
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch ldf2)