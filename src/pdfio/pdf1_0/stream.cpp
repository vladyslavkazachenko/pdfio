#include "stream.h"

namespace pdfio
{
   
namespace pdf1_0
{

const Name Stream::kKeyLength = Name("Length");
const Name Stream::kKeyDecodeParms = Name("DecodeParms");
const Name Stream::kKeyFilter = Name("Filter");
const Name Stream::kKeyColumns = Name("Columns");
const Name Stream::kKeyPredictor = Name("Predictor");
   
Stream::Stream()
{
   insert<Integer>(kKeyLength);
}

const Integer &Stream::length() const
{
   return get<Integer>(kKeyLength);
}

Integer &Stream::length()
{
   return get<Integer>(kKeyLength);
}

bool Stream::hasDecodeParms() const
{
   return contains(kKeyDecodeParms);
}

const Dictionary &Stream::decodeParms() const
{
   return get<Dictionary>(kKeyDecodeParms);
}

Dictionary &Stream::decodeParms()
{
   if(!hasDecodeParms())
   {
      insert<Dictionary>(kKeyDecodeParms);
   }
   return get<Dictionary>(kKeyDecodeParms);
}

bool Stream::hasFilter() const
{
   return contains(kKeyFilter);
}

const Name &Stream::filter() const
{
   return get<Name>(kKeyFilter);
}

Name &Stream::filter()
{
   if(!hasDecodeParms())
   {
      insert<Name>(kKeyFilter);
   }
   return get<Name>(kKeyFilter);
}

const std::string &Stream::data() const
{
   return data_;
}

std::string &Stream::data()
{
   return data_;
}

void Stream::prepare4Reading()
{
   Dictionary decodeParms;
   decodeParms.insert<Integer>(kKeyColumns);
   decodeParms.insert<Integer>(kKeyPredictor);
   insert(kKeyDecodeParms, decodeParms);
   insert<Name>(kKeyFilter);
}
   
}

}
