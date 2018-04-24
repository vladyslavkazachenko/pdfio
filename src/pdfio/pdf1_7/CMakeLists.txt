add_library(pdf1_7 OBJECT 
   pdf.cpp 
   generic_object_type.cpp
   filters.cpp
)
add_dependencies(pdf1_7 pdf1_0)
