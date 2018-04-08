add_library(pdf1_0 OBJECT generic_object_type.cpp stream.cpp document_catalog.cpp)
add_dependencies(pdf1_0 pdfio_common)