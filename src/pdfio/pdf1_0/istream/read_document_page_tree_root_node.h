#pragma once

#include <istream>

#include "pdfio/pdf1_0/document_page_tree_root_node.h"
/*! \brief Reads the root from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::pdf1_0::DocumentPageTreeRootNode &root);