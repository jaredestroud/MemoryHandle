cmake_minimum_required(VERSION 3.17)
project(MemoryHandle)

set(CMAKE_CXX_STANDARD 14)
set(SOURCES
        src/main.cpp
        src/sysinfo.cpp
)

add_executable( ${PROJECT_NAME} ${SOURCES})

target_include_directories( ${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/inc)