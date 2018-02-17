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
add_subdirectory(test/googletest)
include_directories("${PROJECT_SOURCE_DIR}/src")
add_subdirectory(test/pdfio/pdf1_0)
add_subdirectory(test/pdfio/pdf1_0/istream)