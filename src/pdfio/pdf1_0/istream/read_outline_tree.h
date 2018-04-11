#pragma once

#include "pdfio/pdf1_0/outline_tree.h"
/*! \brief Reads the outlineTree from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::OutlineTree &outlineTree);
/*! \brief Reads the outlineTreeEntry from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::OutlineTree::Entry &outlineTreeEntry);