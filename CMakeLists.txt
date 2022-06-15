cmake_minimum_required(VERSION 3.13)

project(openrts
    VERSION 1.0
    DESCRIPTION "Open RTS"
    LANGUAGES C CXX
)

# OOK Radio library
add_subdirectory(src/ookradio)

# C library
add_subdirectory(src/openrts)

# C++ library
add_subdirectory(src/openrtsxx)

# Unit tests
include(CTest)
add_subdirectory(test) 