#pragma once

#include <istream>
#include <functional>
#include <map>

#include "generic_object.h"

/*! \brief Reads the object from the istream*/
std::istream &operator>>(std::istream &istream, pdfio::GenericObject &object);

namespace pdfio
{

/*! \brief Registers handler for the type*/
void RegisterReadHandler(int type, std::function<void(std::istream &, GenericObject &)>);

/*! \brief Nifty counter for registering read handler to the T*/
template <typename T> class ReadHandlerRegistrator
{
public:
   ReadHandlerRegistrator(std::function<void(std::istream &, GenericObject &)> readHandler)
   {
      if(GetCounter() == 0)
      {
         RegisterReadHandler(GenericObject::TypeId<T>(), readHandler);
      }
      ++GetCounter();
   }
   
private:
   static int &GetCounter()
   {
      static int counter = 0;
      return counter;
   }
};

}
