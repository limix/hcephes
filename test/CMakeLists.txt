include_directories (${TEST_SOURCE_DIR}/src)

add_executable (test_ncephes test_ncephes.c)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries (test_ncephes ncephes)
else()
  target_link_libraries (test_ncephes ncephes m)
endif()
