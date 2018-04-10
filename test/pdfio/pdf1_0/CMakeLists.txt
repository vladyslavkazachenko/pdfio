add_executable(pdfio_pdf1_0_unittest_app pdf1_0_unittest_app.cpp
   pdf1_0_name_testsuite.cpp
   pdf1_0_indirect_reference_testsuite.cpp
   pdf1_0_dictionary_testsuite.cpp
   pdf1_0_file_trailer_testsuite.cpp
   pdf1_0_file_xref_testsuite.cpp
   pdf1_0_file_version_testsuite.cpp
   pdf1_0_file_testsuite.cpp
   pdf1_0_indirect_object_testsuite.cpp
   pdf1_0_document_catalog_testsuite.cpp
   pdf1_0_array_testsuite.cpp
   pdf1_0_document_page_tree_root_node_testsuite.cpp
   pdf1_0_document_page_testsuite.cpp
   pdf1_0_hexstring_testsuite.cpp
)
add_dependencies(pdfio_pdf1_0_unittest_app pdfio)
target_link_libraries(pdfio_pdf1_0_unittest_app gtest pdfio z)
add_test(NAME pdfio_pdf1_0_unittest_app COMMAND pdfio_pdf1_0_unittest_app)