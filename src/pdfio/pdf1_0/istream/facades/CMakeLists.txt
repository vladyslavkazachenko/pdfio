add_library(pdf1_0_istream_facades OBJECT 
   file_reader.cpp 
   istream_pool.cpp 
   document_reader.cpp
   pdfio.cpp
)
add_dependencies(pdf1_0_istream_facades pdf1_0_istream)