cmake_minimum_required(VERSION 3.9.6)
project(pdfio)

set(CMAKE_CXX_STANDARD 17)

if(DEFINED PDF_LOG)
   add_definitions(-DPDF_LOG)
endif(DEFINED PDF_LOG)

function (buildPdf1_0)
   add_subdirectory(src/pdfio)
   add_subdirectory(src/pdfio/pdf1_0)
   add_subdirectory(test/pdfio/pdf1_0)
   add_subdirectory(src/pdfio/pdf1_0/istream)
   add_subdirectory(test/pdfio/pdf1_0/istream)
   add_subdirectory(src/pdfio/pdf1_0/istream/document_reader)
   if(${OSTREAM})
      add_subdirectory(src/pdfio/pdf1_0/ostream)
      add_subdirectory(test/pdfio/pdf1_0/ostream)
   endif(${OSTREAM})
endfunction(buildPdf1_0)

function (buildPdf1_4)
   buildPdf1_0()
   add_subdirectory(src/pdfio/pdf1_4)
   add_subdirectory(src/pdfio/pdf1_4/istream)
   add_subdirectory(test/pdfio/pdf1_4/istream)
endfunction(buildPdf1_4)

enable_testing()
include_directories("${PROJECT_SOURCE_DIR}/src")
if(DEFINED PDF_VERSION)
   if(${PDF_VERSION} STREQUAL "1_7")
      buildPdf1_4()
      add_subdirectory(src/pdfio/pdf1_7)
      add_subdirectory(test/pdfio/pdf1_7)
      add_subdirectory(src/pdfio/pdf1_7/istream)
      add_subdirectory(test/pdfio/pdf1_7/istream)
      add_subdirectory(src/pdfio/pdf1_7/istream/file_reader)
      add_library(pdfio
         $<TARGET_OBJECTS:pdf1_7_istream> 
         $<TARGET_OBJECTS:pdf1_7>
         $<TARGET_OBJECTS:pdf1_4_istream> 
         $<TARGET_OBJECTS:pdf1_4>
         $<TARGET_OBJECTS:pdf1_0_istream_documentreader>
         $<TARGET_OBJECTS:pdf1_0_istream>
         $<TARGET_OBJECTS:pdf1_0>
         $<TARGET_OBJECTS:pdfio_common>
      )
      add_dependencies(pdfio pdf1_7_istream pdf1_7 pdf1_0_istream pdf1_0 pdfio_common)
   elseif(${PDF_VERSION} STREQUAL "1_4")
      buildPdf1_4()
      add_library(pdfio
         $<TARGET_OBJECTS:pdf1_4_istream> 
         $<TARGET_OBJECTS:pdf1_4>
         $<TARGET_OBJECTS:pdf1_0_istream_documentreader>
         $<TARGET_OBJECTS:pdf1_0_istream>
         $<TARGET_OBJECTS:pdf1_0>
         $<TARGET_OBJECTS:pdfio_common>
      )
   elseif(${PDF_VERSION} STREQUAL "1_0")
      buildPdf1_0()
      add_library(pdfio 
         $<TARGET_OBJECTS:pdf1_0_istream_documentreader>
         $<TARGET_OBJECTS:pdf1_0_istream>
         $<TARGET_OBJECTS:pdf1_0>
         $<TARGET_OBJECTS:pdfio_common>
      )
   else(${PDF_VERSION} STREQUAL "1_7")
      message(FATAL_ERROR "PDF_VERSION is invalid, possible values are 1_7 and 1_0")
   endif(${PDF_VERSION} STREQUAL "1_7")
else(DEFINED PDF_VERSION)
   message(FATAL_ERROR "PDF_VERSION is not defined")
endif(DEFINED PDF_VERSION)

find_package(Doxygen)
configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
COMMENT "Generating documentation with Doxygen" VERBATIM
)
