add_library(pdf1_4_istream OBJECT 
   read_file_structure.cpp
   read_file_version.cpp
)
add_dependencies(pdf1_4_istream pdf1_4)
