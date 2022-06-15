# Unity unit test library
add_library(unity STATIC EXCLUDE_FROM_ALL unity/src/unity.c)
target_include_directories(unity PUBLIC unity/src)

# Open RTC C library test suite
add_subdirectory(openrts)

# Open RTC C++ bindings test suite
add_subdirectory(openrtsxx)