add_executable(pdfio_pdf1_7_unittest_app pdf1_7_unittest_app.cpp
   pdf1_7_pdf_testsuite.cpp
   pdf1_7_array_testsuite.cpp
   pdf1_7_file_structure_testsuite.cpp
   pdf1_7_filters_testsuite.cpp
)
add_dependencies(pdfio_pdf1_7_unittest_app 
   pdf1_0 pdf1_7
   pdfio_pdf1_0_unittest_app
)
target_link_libraries(pdfio_pdf1_7_unittest_app gtest
   $<TARGET_OBJECTS:pdfio_common> 
   $<TARGET_OBJECTS:pdf1_0>
   $<TARGET_OBJECTS:pdf1_7>
   z
)
add_test(NAME pdfio_pdf1_7_unittest_app COMMAND pdfio_pdf1_7_unittest_app)
