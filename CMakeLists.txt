cmake_minimum_required(VERSION 3.15)

project(efanna2e)
set(CMAKE_C_STANDARD 11)



#OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
else ()
    message(FATAL_ERROR "no OpenMP supprot")
endif ()

#OpenBLAS
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/module)
find_package(OpenBLAS REQUIRED)
include_directories(${OpenBLAS_INCLUDE_DIR})
set(BLAS_LIB ${OpenBLAS_LIB})


add_definitions(-O3 -lboost -march=native -Wall -DINFO)


# Find source files
file(GLOB SOURCES src/*.cpp)
# Include header files
include_directories(include)
# Create shared library
add_library(${PROJECT_NAME} SHARED ${SOURCES})
# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})
# Install library headers
file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

