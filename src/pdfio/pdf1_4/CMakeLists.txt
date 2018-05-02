add_library(pdf1_4 OBJECT 
   file_structure.cpp
   file_version.cpp
   document_catalog.cpp
   action.cpp
   generic_object_type.cpp
)
add_dependencies(pdf1_4 pdf1_0)
