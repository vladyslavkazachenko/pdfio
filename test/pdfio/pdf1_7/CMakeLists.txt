add_executable(pdfio_pdf1_7_unittest_app pdf1_7_unittest_app.cpp
	pdf1_7_pdf_testsuite.cpp
	pdf1_7_integer_testsuite.cpp
	pdf1_7_hexstring_testsuite.cpp
	pdf1_7_file_trailer_testsuite.cpp
	pdf1_7_array_testsuite.cpp
)
add_dependencies(pdfio_pdf1_7_unittest_app pdf1_7)
target_link_libraries(pdfio_pdf1_7_unittest_app gtest 
	$<TARGET_OBJECTS:pdf1_7> 
	$<TARGET_OBJECTS:pdf1_0>
)
add_test(NAME pdfio_pdf1_7_unittest_app COMMAND pdfio_pdf1_7_unittest_app)