cmake_minimum_required (VERSION 2.6.4)

project(hcephes C)

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

file(STRINGS "VERSION" HCEPHES_VERSION)

include_directories( include/ )
include_directories( hcephes/ )
include_directories(.)

add_subdirectory(hcephes)

file(GLOB CPROB_SRC
    "hcephes/cprob/*.c"
)

file(GLOB BESSEL_SRC
    "hcephes/bessel/*.c"
)

file(GLOB ELLF_SRC
    "hcephes/ellf/*.c"
)

file(GLOB MISC_SRC
    "hcephes/misc/*.c"
)

file(GLOB POLYN_SRC
    "hcephes/polyn/*.c"
)

file(GLOB CMATH_SRC
    "hcephes/cmath/powi.c"
)

add_library(hcephes
    SHARED ${BESSEL_SRC} ${CMATH_SRC} ${CPROB_SRC} ${ELLF_SRC} ${MISC_SRC} ${POLYN_SRC}
           hcephes/mtherr.c)

add_library(hcephes_static
    STATIC ${BESSEL_SRC} ${CMATH_SRC} ${CPROB_SRC} ${ELLF_SRC} ${MISC_SRC} ${POLYN_SRC}
           hcephes/mtherr.c)

set_target_properties(hcephes
  PROPERTIES
    VERSION ${HCEPHES_VERSION}
    PUBLIC_HEADER include/hcephes/hcephes.h)

install(TARGETS hcephes
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION lib
    PUBLIC_HEADER DESTINATION include/hcephes)

install(TARGETS hcephes_static
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include/hcephes)

add_subdirectory(test)

enable_testing()
add_test(test_hcephes test/test_hcephes)
