#include "file_structure.h"

namespace pdfio
{

namespace pdf1_0
{
   
namespace
{
   
const Name kKeySize = Name("Size");
const Name kKeyPrev = Name("Prev");
const Name kKeyRoot = Name("Root");
const Name kKeyInfo = Name("Info");
   
}

FileStructure::Trailer::Trailer()
{
   insert<Integer>(kKeySize);
}

FileStructure::Trailer &FileStructure::Trailer::operator=(
   const Trailer &other)
{
   static_cast<Dictionary &>(*this) = 
      static_cast<const Dictionary &>(other);
   return *this;
}

const Integer &FileStructure::Trailer::size() const
{
   return get<Integer>(kKeySize);
}

Integer &FileStructure::Trailer::size()
{
   return get<Integer>(kKeySize);
}

bool FileStructure::Trailer::hasPrev() const
{
   return contains(kKeyPrev);
}

const Integer &FileStructure::Trailer::prev() const
{
   return get<Integer>(kKeyPrev);
}

Integer &FileStructure::Trailer::prev()
{
   if(!hasPrev())
   {
      insert<Integer>(kKeyPrev);
   }
   return get<Integer>(kKeyPrev);
}

bool FileStructure::Trailer::hasRoot() const
{
   return contains(kKeyRoot);
}

const IndirectReference &FileStructure::Trailer::root() const
{
   return get<IndirectReference>(kKeyRoot);
}

IndirectReference &FileStructure::Trailer::root()
{
   return get<IndirectReference>(kKeyRoot);
}

bool FileStructure::Trailer::hasInfo() const
{
   return contains(kKeyInfo);
}

const IndirectReference &FileStructure::Trailer::info() const
{
   return get<IndirectReference>(kKeyInfo);
}

IndirectReference &FileStructure::Trailer::info()
{
   if(!hasInfo())
   {
      insert<IndirectReference>(kKeyInfo);
   }
   return get<IndirectReference>(kKeyInfo);
}

void FileStructure::Trailer::prepare4Reading()
{
   insert<Integer>(kKeyPrev);
   insert<IndirectReference>(kKeyRoot);
   insert<IndirectReference>(kKeyInfo);
}

}

}
