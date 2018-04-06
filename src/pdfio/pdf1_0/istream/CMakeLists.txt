add_library(pdf1_0_istream OBJECT
   generic_object_readers.cpp
   read_name.cpp
   read_integer.cpp
   read_indirect_reference.cpp
   read_dictionary.cpp
   read_file_trailer.cpp
   read_file_xref.cpp
   read_file_header.cpp
   read_file_version.cpp
   read_file.cpp
   read_indirect_object.cpp
   read_document_catalog.cpp
   read_document_page_tree_root_node.cpp
   read_stream.cpp
   read_document_page.cpp
   read_document_page_description.cpp
   read_hexstring.cpp
   read_real.cpp
   read_literalstring.cpp
   read_file_structure.cpp
)
add_dependencies(pdf1_0_istream pdf1_0)