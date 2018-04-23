add_library(pdf1_0 OBJECT 
   generic_object_type.cpp 
   stream.cpp 
   document_catalog.cpp 
   outline_tree.cpp
   document_pages_tree.cpp
   info.cpp
   file_structure.cpp
)
add_dependencies(pdf1_0 pdfio_common)
