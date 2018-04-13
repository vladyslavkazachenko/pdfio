add_executable(pdfio_pdf1_0_istream_unittest_app pdf1_0_istream_unittest_app.cpp
   pdf1_0_istream_name_testsuite.cpp
   pdf1_0_istream_indirect_reference_testsuite.cpp
   pdf1_0_istream_dictionary_testsuite.cpp
   pdf1_0_istream_generic_object_testsuite.cpp
   pdf1_0_istream_indirect_object_testsuite.cpp
   pdf1_0_istream_document_catalog_testsuite.cpp
   pdf1_0_istream_array_testsuite.cpp
   pdf1_0_istream_stream_testsuite.cpp
   pdf1_0_istream_hexstring_testsuite.cpp
   pdf1_0_istream_literalstring_testsuite.cpp
   pdf1_0_istream_string_testsuite.cpp
   pdf1_0_istream_file_structure_testsuite.cpp
   pdf1_0_istream_outline_tree_testsuite.cpp
   pdf1_0_istream_document_pages_tree.cpp
)
add_dependencies(pdfio_pdf1_0_istream_unittest_app 
   pdfio_common pdf1_0 pdf1_0_istream
   pdfio_pdf1_0_unittest_app) 
target_link_libraries(pdfio_pdf1_0_istream_unittest_app gtest z
   $<TARGET_OBJECTS:pdfio_common>
   $<TARGET_OBJECTS:pdf1_0>
   $<TARGET_OBJECTS:pdf1_0_istream>
)
add_test(NAME pdfio_pdf1_0_istream_unittest_app COMMAND pdfio_pdf1_0_istream_unittest_app)