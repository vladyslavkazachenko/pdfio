add_executable(pdfio_pdf1_7_istream_unittest_app pdf1_7_istream_unittest_app.cpp
   pdf1_7_istream_file_structure_testsuite.cpp
   pdf1_7_istream_name_tree_testsuite.cpp
   pdf1_7_istream_document_catalog_testsuite.cpp
   pdf1_7_istream_indirect_object_testsuite.cpp
)
add_dependencies(pdfio_pdf1_7_istream_unittest_app 
   pdf1_7_istream
   pdfio_pdf1_7_unittest_app) 
target_link_libraries(pdfio_pdf1_7_istream_unittest_app gtest
   $<TARGET_OBJECTS:pdfio_common>
   $<TARGET_OBJECTS:pdf1_0>
   $<TARGET_OBJECTS:pdf1_0_istream>
   $<TARGET_OBJECTS:pdf1_4>
   $<TARGET_OBJECTS:pdf1_4_istream>
   $<TARGET_OBJECTS:pdf1_7> 
   $<TARGET_OBJECTS:pdf1_7_istream>
   z
)
add_test(NAME pdfio_pdf1_7_istream_unittest_app COMMAND pdfio_pdf1_7_istream_unittest_app)
