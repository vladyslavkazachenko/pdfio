#pragma once

extern "C" {
   int pdfio_docreader_create();
   void pdfio_docreader_destroy(int docreader);
   int pdfio_docreader_loadfile(int docreader, const char *fullFileName);
}