cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)
project(hcephes VERSION 0.4.1 LANGUAGES C)

# Generate compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# Set RPATH only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif()

add_library(hcephes
    src/bessel/airy.c
    src/bessel/hyp2f1.c
    src/bessel/hyperg.c
    src/bessel/i0.c
    src/bessel/i1.c
    src/bessel/iv.c
    src/bessel/j0.c
    src/bessel/j1.c
    src/bessel/jn.c
    src/bessel/jv.c
    src/bessel/k0.c
    src/bessel/k1.c
    src/bessel/kn.c
    src/bessel/struve.c
    src/bessel/yn.c
    src/cmath/cbrt.c
    src/cmath/powi.c
    src/cprob/bdtr.c
    src/cprob/btdtr.c
    src/cprob/chdtr.c
    src/cprob/drand.c
    src/cprob/expx2.c
    src/cprob/fdtr.c
    src/cprob/gamma.c
    src/cprob/gdtr.c
    src/cprob/igam.c
    src/cprob/igami.c
    src/cprob/incbet.c
    src/cprob/incbi.c
    src/cprob/kolmogorov.c
    src/cprob/nbdtr.c
    src/cprob/ndtr.c
    src/cprob/ndtri.c
    src/cprob/pdtr.c
    src/cprob/stdtr.c
    src/cprob/unity.c
    src/ellf/cmplx.c
    src/ellf/ellie.c
    src/ellf/ellik.c
    src/ellf/ellpe.c
    src/ellf/ellpj.c
    src/ellf/ellpk.c
    src/misc/beta.c
    src/misc/chbevl.c
    src/misc/dawsn.c
    src/misc/ei.c
    src/misc/expn.c
    src/misc/fac.c
    src/misc/fresnl.c
    src/misc/planck.c
    src/misc/polylog.c
    src/misc/psi.c
    src/misc/revers.c
    src/misc/rgamma.c
    src/misc/shichi.c
    src/misc/sici.c
    src/misc/simpsn.c
    src/misc/spence.c
    src/misc/zeta.c
    src/misc/zetac.c
    src/mtherr.c
    src/mtherr.c
    src/polyn/euclid.c
    src/polyn/polevl.c
    src/polyn/polmisc.c
    src/polyn/polrt.c
    src/polyn/polyn.c
)
add_library(HCEPHES::hcephes ALIAS hcephes)

target_include_directories(hcephes
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
set_target_properties(hcephes PROPERTIES PUBLIC_HEADER include/hcephes.h)
set_target_properties(hcephes PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(hcephes PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(hcephes PROPERTIES C_STANDARD 99)
set_target_properties(hcephes PROPERTIES DEFINE_SYMBOL HCEPHES_EXPORTS)
target_compile_definitions(hcephes PRIVATE $<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>)
target_compile_definitions(hcephes PRIVATE $<$<BOOL:${WIN32}>:_CRT_NONSTDC_NO_DEPRECATE>)
target_link_libraries(hcephes INTERFACE $<$<BOOL:${UNIX}>:m>)
target_compile_options(hcephes PRIVATE
    $<$<STREQUAL:${CMAKE_C_COMPILER_ID},MSVC>:/W3 /WX>
    $<$<NOT:$<STREQUAL:${CMAKE_C_COMPILER_ID},MSVC>>:-Wall -Wextra -Wstrict-prototypes
        -Wshadow -Wconversion -Wmissing-prototypes -Wno-unused-parameter>
)

install(TARGETS hcephes EXPORT hcephes-targets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)
install(EXPORT hcephes-targets
    FILE hcephes-targets.cmake
    NAMESPACE HCEPHES::
    DESTINATION lib/cmake/hcephes
)
include(CMakePackageConfigHelpers)
configure_package_config_file(hcephes-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/hcephes-config.cmake
    INSTALL_DESTINATION lib/cmake/hcephes
    NO_SET_AND_CHECK_MACRO
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/hcephes-config.cmake
    DESTINATION lib/cmake/hcephes
)

enable_testing()
add_subdirectory(test)
