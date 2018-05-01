#include "file_structure.h"
#include "name.h"
#include "indirect_reference.h"

namespace pdfio
{
   
namespace pdf1_4
{
 
namespace
{
   const Name kKeyEncrypt = Name("Encrypt");
   const Name kKeyId = Name("ID");
}
 
/*FileStructure::Trailer &FileStructure::Trailer::operator=(const Trailer &other)
{
   dynamic_cast<Dictionary &>(*this) = dynamic_cast<const Dictionary &>(other);
   return *this;
}*/

bool FileStructure::Trailer::hasEncrypt() const
{
   return contains(kKeyEncrypt);
}

bool FileStructure::Trailer::hasId() const
{
   return contains(kKeyId);
}

const Array<HexString> &FileStructure::Trailer::id() const
{
   return get<Array<HexString>>(kKeyId);
}

Array<HexString> &FileStructure::Trailer::id()
{
   if(!hasId())
   {
      Array<HexString> id(2);
      insert(kKeyId, id);
   }
   return get<Array<HexString>>(kKeyId);
}

void FileStructure::Trailer::prepare4Reading()
{
   pdf1_0::FileStructure::Trailer::prepare4Reading();
   insert<IndirectReference>(kKeyEncrypt);
   insert<Array<HexString>>(kKeyId);
}
   
}

}
