cmake_minimum_required(VERSION 3.15)

project(
    CHIPX
    VERSION 0.5
    LANGUAGES C
)

find_package(raylib REQUIRED)

add_subdirectory(src)