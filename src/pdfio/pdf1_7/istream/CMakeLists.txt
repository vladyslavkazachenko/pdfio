add_library(pdf1_7_istream OBJECT 
	read_file_header.cpp
	read_file_trailer.cpp
)
add_dependencies(pdf1_7_istream pdf1_7 pdf1_7_istream)