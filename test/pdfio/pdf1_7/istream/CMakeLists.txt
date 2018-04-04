add_executable(pdfio_pdf1_7_istream_unittest_app pdf1_7_istream_unittest_app.cpp
	pdf1_7_istream_file_header_testsuite.cpp
	pdf1_7_istream_file_trailer_testsuite.cpp
	pdf1_7_istream_file_structure_testsuite.cpp
)
add_dependencies(pdfio_pdf1_7_istream_unittest_app pdf1_7_istream pdf1_7 log) 
target_link_libraries(pdfio_pdf1_7_istream_unittest_app gtest 
	$<TARGET_OBJECTS:pdf1_7_istream> 
	$<TARGET_OBJECTS:pdf1_7>
	$<TARGET_OBJECTS:pdf1_0_istream> 
	$<TARGET_OBJECTS:pdf1_0> 
  $<TARGET_OBJECTS:log>
)
add_test(NAME pdfio_pdf1_7_istream_unittest_app COMMAND pdfio_pdf1_7_istream_unittest_app)