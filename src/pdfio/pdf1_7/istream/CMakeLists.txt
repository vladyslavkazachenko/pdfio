add_library(pdf1_7_istream OBJECT 
	read_file_header.cpp
	read_file_trailer.cpp
	read_file_structure.cpp
	read_name_tree.cpp
	read_document_catalog.cpp
)
add_dependencies(pdf1_7_istream pdf1_7)