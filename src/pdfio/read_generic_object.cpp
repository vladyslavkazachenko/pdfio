#include "read_generic_object.h"

#include <map>
#include <cassert>

namespace
{

std::map<int, std::function<void(std::istream &, pdfio::GenericObject &)>> &GetReadHandlers()
{
   static std::map<int, std::function<void(std::istream &, pdfio::GenericObject &)>> readHandlers;
   return readHandlers;
}

}

std::istream &operator>>(std::istream &istream, pdfio::GenericObject &object)
{
   assert(GetReadHandlers().find(object.typeId_) != GetReadHandlers().end());
   GetReadHandlers()[object.typeId_](istream, object);
   return istream;
}

namespace pdfio
{
   
void RegisterReadHandler(int type, std::function<void(std::istream &, GenericObject &)> handler)
{
   assert(GetReadHandlers().find(type) == GetReadHandlers().end());
   GetReadHandlers()[type] = handler;
}

}