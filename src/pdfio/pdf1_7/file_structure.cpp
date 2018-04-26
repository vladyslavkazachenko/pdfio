#include "file_structure.h"

namespace pdfio
{
   
namespace pdf1_7
{
   
namespace
{
   const Name kKeySize = Name("Size");
   const Name kKeyEncrypt = Name("Encrypt");
   const Name kKeyId = Name("ID");
   const Name kKeyXrefStm = Name("XrefStm");
   const Name kKeyType = Name("Type");
   const Name kKeyW = Name("W");
   const Name kKeyIndex = Name("Index");
   const Name kKeyXRefStm = Name("XRefStm");
}
 
FileStructure::Trailer &FileStructure::Trailer::operator=(const Trailer &other)
{
   dynamic_cast<Dictionary &>(*this) = dynamic_cast<const Dictionary &>(other);
   return *this;
}

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
   return get<pdf1_7::Array<pdf1_7::HexString>>(kKeyId);
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
   insert<Integer>(kKeyXrefStm);
}

const Name FileStructure::XrefStream::kTypeValue = Name("XRef");

FileStructure::XrefStream::XrefStream()
: Dictionary()
, Stream()
, Trailer()
{
   insert(kKeyType, kTypeValue);
   insert<Array<Integer>>(kKeyW);
}

bool FileStructure::XrefStream::hasIndex() const
{
   return contains(kKeyIndex);
}

const Array<Integer> &FileStructure::XrefStream::index() const
{
   return get<Array<Integer>>(kKeyIndex);
}

Array<Integer> &FileStructure::XrefStream::index()
{
   if(!hasIndex())
   {
      insert<Array<Integer>>(kKeyIndex);
   }
   return get<Array<Integer>>(kKeyIndex);
}

const Array<Integer> &FileStructure::XrefStream::w() const
{
   return get<Array<Integer>>(kKeyW);
}

Array<Integer> &FileStructure::XrefStream::w()
{
   return get<Array<Integer>>(kKeyW);
}

void FileStructure::XrefStream::prepare4Reading()
{
   Stream::prepare4Reading();
   Trailer::prepare4Reading();
   insert<Array<Integer>>(kKeyIndex);
   insert<Integer>(kKeyXRefStm);
}
   
}

}
