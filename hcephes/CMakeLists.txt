function(define_sources BASE_DIR _SOURCES)
    file(GLOB CPROB_SRC
        "cprob/*.c"
    )

    file(GLOB BESSEL_SRC
        "bessel/*.c"
    )

    file(GLOB ELLF_SRC
        "ellf/*.c"
    )

    file(GLOB MISC_SRC
        "misc/*.c"
    )

    file(GLOB POLYN_SRC
        "polyn/*.c"
    )

    file(GLOB CMATH_SRC
        "cmath/*.c"
    )

    list(APPEND SOURCES "mtherr.c;${CPROB_SRC};${BESSEL_SRC};${ELLF_SRC}")
    list(APPEND SOURCES "${MISC_SRC};${POLYN_SRC};${CMATH_SRC}")

    limix_convert_rel_to_full(FULL_SOURCES ${BASE_DIR} "${SOURCES}")
    set(${_SOURCES} ${FULL_SOURCES} PARENT_SCOPE)
endfunction(define_sources)
