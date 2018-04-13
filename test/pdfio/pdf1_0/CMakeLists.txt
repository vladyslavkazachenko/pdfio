add_executable(pdfio_pdf1_0_unittest_app pdf1_0_unittest_app.cpp
   pdf1_0_name_testsuite.cpp
   pdf1_0_indirect_reference_testsuite.cpp
   pdf1_0_dictionary_testsuite.cpp
   pdf1_0_indirect_object_testsuite.cpp
   pdf1_0_document_catalog_testsuite.cpp
   pdf1_0_array_testsuite.cpp
   pdf1_0_hexstring_testsuite.cpp
)
add_dependencies(pdfio_pdf1_0_unittest_app pdf1_0)
target_link_libraries(pdfio_pdf1_0_unittest_app gtest z 
   $<TARGET_OBJECTS:pdf1_0>
)
add_test(NAME pdfio_pdf1_0_unittest_app COMMAND pdfio_pdf1_0_unittest_app)