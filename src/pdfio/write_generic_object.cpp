#include "write_generic_object.h"

#include <map>
#include <cassert>

namespace
{

std::map<int, std::function<void(std::ostream &, const pdfio::GenericObject &)>> 
   &GetWriteHandlers()
{
   static std::map<int, std::function<void(std::ostream &, 
      const pdfio::GenericObject &)>> writeHandlers;
   return writeHandlers;
}

}

std::ostream &operator<<(std::ostream &ostream, 
   const pdfio::GenericObject &object)
{
   assert(GetWriteHandlers().find(object.typeId_) != GetWriteHandlers().end());
   GetWriteHandlers()[object.typeId_](ostream, object);
   return ostream;
}

namespace pdfio
{
   
void RegisterWriteHandler(int type, 
   std::function<void(std::ostream &, const GenericObject &)> handler)
{
   assert(GetWriteHandlers().find(type) == GetWriteHandlers().end());
   GetWriteHandlers()[type] = handler;
}

}
