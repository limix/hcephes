function(hcephes_add_test name)
    add_executable(test_${name} src/${name}.c)
    target_compile_definitions(test_${name} PRIVATE $<$<BOOL:${WIN32}>:_CRT_SECURE_NO_WARNINGS>)
    target_link_libraries(test_${name} PRIVATE HCEPHES::hcephes)
    add_test(NAME ${name} COMMAND test_${name} -E environment)

    # Ugly hacky to make the tests work on Windows.
    file(TO_CMAKE_PATH "$ENV{PATH}" PATH)
    list(APPEND PATH $<TARGET_FILE_DIR:HCEPHES::hcephes>)
    string(REPLACE ";" "\\;" PATH "${PATH}")
    set_tests_properties(${name} PROPERTIES ENVIRONMENT "PATH=${PATH}")
endfunction()

hcephes_add_test(hcephes)
