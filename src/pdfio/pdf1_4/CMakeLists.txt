add_library(pdf1_4 OBJECT 
   file_structure.cpp
   file_version.cpp
   document_catalog.cpp
)
add_dependencies(pdf1_4 pdf1_0)
