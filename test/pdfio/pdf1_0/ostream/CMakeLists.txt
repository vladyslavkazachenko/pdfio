add_executable(pdfio_pdf1_0_ostream_unittest_app 
   pdf1_0_ostream_unittest_app.cpp
   pdf1_0_ostream_name_testsuite.cpp
)
add_dependencies(pdfio_pdf1_0_ostream_unittest_app 
   pdf1_0_ostream
) 
target_link_libraries(pdfio_pdf1_0_ostream_unittest_app gtest
   $<TARGET_OBJECTS:pdfio_common>
   $<TARGET_OBJECTS:pdf1_0>
   $<TARGET_OBJECTS:pdf1_0_ostream>
)
add_test(NAME pdfio_pdf1_0_ostream_unittest_app 
   COMMAND pdfio_pdf1_0_ostream_unittest_app)
