add_library(pdf1_0_istream_documentreader OBJECT
   istream_pool.cpp
   file_reader.cpp
   document_reader.cpp
)
add_dependencies(pdf1_0_istream_documentreader pdf1_0_istream)
