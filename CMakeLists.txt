cmake_minimum_required(VERSION 3.15)
project(FileIntegrity)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(ZLIB REQUIRED)

set(
    SOURCE_FILES
    main.cpp
    utils.cpp
)

add_executable(
    FileIntegrity
    ${SOURCE_FILES}
)

target_link_libraries(FileIntegrity PRIVATE ZLIB::ZLIB)