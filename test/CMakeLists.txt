add_library(unity STATIC EXCLUDE_FROM_ALL unity.c)
target_include_directories(unity PUBLIC .)

add_subdirectory(test_openrts)
add_subdirectory(test_openrtsxx)