cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(bare-i2c-testing)

target_sources(app PRIVATE src/main.c)

#external modules
add_subdirectory(src/raafat-bmi323)
add_subdirectory(src/bmi323)