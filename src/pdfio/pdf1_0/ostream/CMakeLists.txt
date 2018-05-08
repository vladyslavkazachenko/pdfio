add_library(pdf1_0_ostream OBJECT
   write_name.cpp
   write_indirect_reference.cpp
)
add_dependencies(pdf1_0_ostream pdf1_0)
