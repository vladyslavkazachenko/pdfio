#pragma once

#include <list>

namespace pdfio
{
   
template <typename T> struct FileStructure
{
   typename T::Header header_;
   std::list<T> versions_;
};
   
}
