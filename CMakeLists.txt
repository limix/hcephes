cmake_minimum_required (VERSION 2.6.4)

project(ncephes C)

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
                  OUTPUT_VARIABLE GCC_VERSION)

  if (GCC_VERSION VERSION_GREATER 4.9)
    set (CMAKE_C_STANDARD 11)
  else ()
    set (CMAKE_C_FLAGS "--std=gnu99 ${CMAKE_C_FLAGS}")
  endif ()
endif ()

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-Dinline=__inline)
endif()

file(STRINGS "VERSION" NCEPHES_VERSION)

include_directories( include/ )
include_directories(.)

add_subdirectory(ncephes)

add_library(ncephes SHARED ncephes/ncephes.c)

add_library(ncephes_static STATIC ncephes/ncephes.c)

set_target_properties(ncephes
  PROPERTIES
    VERSION ${NCEPHES_VERSION}
    PUBLIC_HEADER include/ncephes/ncephes.h)

install(TARGETS ncephes
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION lib
    PUBLIC_HEADER DESTINATION include/ncephes)

install(TARGETS ncephes_static
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/ncephes)

add_subdirectory(test)

# enable_testing()
# add_test(test_ncephes test/test_ncephes)
