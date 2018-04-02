cmake_minimum_required(VERSION 3.9.6)
project(pdfio)

set(CMAKE_CXX_STANDARD 17)

find_package(Doxygen)
configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
COMMENT "Generating documentation with Doxygen" VERBATIM
)

enable_testing()
include_directories("${PROJECT_SOURCE_DIR}/src")
if(DEFINED PDF_VERSION)
	if(${PDF_VERSION} STREQUAL "1_7")
		add_subdirectory(src/pdfio/pdf1_0)
		add_subdirectory(test/pdfio/pdf1_0)
		add_subdirectory(src/pdfio/pdf1_0/istream)
		add_subdirectory(test/pdfio/pdf1_0/istream)
		add_subdirectory(src/pdfio/pdf1_7)
		add_subdirectory(test/pdfio/pdf1_7)
		add_library(pdfio $<TARGET_OBJECTS:pdf1_0> $<TARGET_OBJECTS:pdf1_0_istream> $<TARGET_OBJECTS:pdf1_7>)
	elseif(${PDF_VERSION} STREQUAL "1_1")
		add_subdirectory(src/pdfio/pdf1_0)
		add_subdirectory(test/pdfio/pdf1_0)
		add_subdirectory(src/pdfio/pdf1_0/istream)
		add_subdirectory(test/pdfio/pdf1_0/istream)
		add_library(pdfio $<TARGET_OBJECTS:pdf1_0> $<TARGET_OBJECTS:pdf1_0_istream>)
	endif(${PDF_VERSION} EQUAL "1_7")
endif(DEFINED PDF_VERSION)