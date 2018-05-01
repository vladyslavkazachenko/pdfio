#include "file_version.h"

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
   
const std::string FileVersion::Header::kVersion1_0 = "%PDF−1.0";
const std::string FileVersion::Header::kVersion1_1 = "%PDF−1.1";
const std::string FileVersion::Header::kVersion1_2 = "%PDF−1.2";
const std::string FileVersion::Header::kVersion1_3 = "%PDF−1.3";
const std::string FileVersion::Header::kVersion1_4 = "%PDF−1.4";

bool FileVersion::Trailer::hasEncrypt() const
{
   return contains(kKeyEncrypt);
}

bool FileVersion::Trailer::hasId() const
{
   return contains(kKeyId);
}

const Array<HexString> &FileVersion::Trailer::id() const
{
   return get<Array<HexString>>(kKeyId);
}

Array<HexString> &FileVersion::Trailer::id()
{
   if(!hasId())
   {
      Array<HexString> id(2);
      insert(kKeyId, id);
   }
   return get<Array<HexString>>(kKeyId);
}

void FileVersion::Trailer::prepare4Reading()
{
   pdf1_0::FileStructure::Trailer::prepare4Reading();
   insert<IndirectReference>(kKeyEncrypt);
   insert<Array<HexString>>(kKeyId);
}
   
}
   
}
