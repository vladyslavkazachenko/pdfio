#pragma once

#include <ostream>
#include <functional>

#include "generic_object.h"

/*! \brief Writes the object to the ostream*/
std::ostream &operator<<(std::ostream &ostream, 
   const pdfio::GenericObject &object);
   
namespace pdfio
{

/*! \brief Registers handler for the type*/
void RegisterWriteHandler(int type, 
   std::function<void(std::ostream &, const GenericObject &)>);
   
/*! \brief Nifty counter for registering write handler to the T*/
template <typename T> class WriteHandlerRegistrator
{
public:
   /*! \brief Constructs the WriteHandlerRegistrator registering the 
    * writeHandler as write handler for the T
    */
   WriteHandlerRegistrator(
      std::function<void(std::ostream &, const GenericObject &)> writeHandler)
   {
      if(GetCounter() == 0)
      {
         RegisterWriteHandler(GenericObject::TypeId<T>(), writeHandler);
         ++GetCounter();
      }
   }
   
private:
   static int &GetCounter()
   {
      static int counter = 0;
      return counter;
   }
};
   
}

#define REGISTER_WRITE_HANDLER_FOR_TYPE(type) \
   namespace pdfio \
   { \
      namespace type##ns \
      { \
         WriteHandlerRegistrator<type> typeRegistrator(\
            [](std::ostream &i, const GenericObject &o) \
            { \
               i << static_cast<const GenericObjectAdaptor<type> &>(o).object_; \
            }); \
      } \
   }
