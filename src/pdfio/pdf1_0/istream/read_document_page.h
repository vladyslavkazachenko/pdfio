#pragma once

#include <istream>

#include "pdfio/pdf1_0/document_page.h"
/*! \brief Reads the page from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::DocumentPage &page);
/*! \brief Reads the resources from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::DocumentPage::Resources &resources);
/*! \brief Reads the resource from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::DocumentPage::ResourceDictionary &resource);
/*! \brief Reads the contents from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::DocumentPage::Contents &contents);