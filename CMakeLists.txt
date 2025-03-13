project(melatonin_hsluv VERSION 1.0.0 LANGUAGES C CXX
    DESCRIPTION "JUCE module for hsluv colors"
    HOMEPAGE_URL "https://github.com/sudara/melatonin_hsluv")

add_library(hsluv-c STATIC hsluv/hsluv.h hsluv/hsluv.c)

# In Windows SDK, math functions are part of C runtime lib.
if(NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
    target_link_libraries(hsluv-c m)
endif()

juce_add_module("${CMAKE_CURRENT_LIST_DIR}")
target_link_libraries(melatonin_hsluv INTERFACE hsluv-c)
