#pragma once

extern "C" {
   void pdfio_setdebuglogger(void (*f)(const char *msg));
   
   
   int pdfio_docreader_create();
   void pdfio_docreader_destroy(int docreader);
   int pdfio_docreader_loadfile(int docreader, const char *fullFileName);
}