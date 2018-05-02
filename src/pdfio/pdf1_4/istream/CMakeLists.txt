add_library(pdf1_4_istream OBJECT 
   read_file_structure.cpp
   read_file_version.cpp
   read_document_catalog.cpp
   read_action.cpp
   read_destination.cpp
)
add_dependencies(pdf1_4_istream pdf1_4)
