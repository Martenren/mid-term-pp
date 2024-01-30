cmake_minimum_required(VERSION 3.27)
project(mid_term_pp)

# Set the C and C++ compilers
set(CMAKE_C_COMPILER "/usr/local/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
set(OpenMP_CXX_LIB_NAMES "omp")
set(OpenMP_omp_LIBRARY "/usr/local/opt/llvm/lib/libomp.dylib")

# Find OpenMP package
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib")
endif()

add_executable(mid_term_pp main.cpp BigramGenerator.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(mid_term_pp PRIVATE OpenMP::OpenMP_CXX)
endif()