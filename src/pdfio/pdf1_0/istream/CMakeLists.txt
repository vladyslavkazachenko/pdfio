add_library(pdf1_0_istream OBJECT 
	read_name.cpp
	read_integer.cpp
	read_indirect_reference.cpp
	read_generic_object.cpp
	read_dictionary.cpp
	read_file_trailer.cpp
	read_file_xref.cpp
	read_file_header.cpp
	read_file_version.cpp
	read_file.cpp
)