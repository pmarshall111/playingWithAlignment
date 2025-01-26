cmake_minimum_required(VERSION 3.28)

project(alignment VERSION 1.0)

# Executables
add_executable(demonstrateCompilerAlignment.tsk demonstrateCompilerAlignment.cpp)
target_include_directories(demonstrateCompilerAlignment.tsk PRIVATE .)
target_compile_options(demonstrateCompilerAlignment.tsk PRIVATE -ggdb)

add_executable(speedTest.tsk speedTest.cpp)
target_include_directories(speedTest.tsk PRIVATE .)
# target_compile_options(speedTest.tsk PRIVATE -O2)