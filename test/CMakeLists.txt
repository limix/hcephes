include_directories (${TEST_SOURCE_DIR}/src)

add_executable (test_hcephes test_hcephes.c)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  target_link_libraries (test_hcephes hcephes)
else()
  target_link_libraries (test_hcephes hcephes m)
endif()
