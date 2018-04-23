#include "info.h"

namespace pdfio
{

namespace pdf1_0
{
   
namespace
{
   
const Name kKeyCreator = Name("Creator");
const Name kKeyCreationDate = Name("CreationDate");
const Name kKeyAuthor = Name("Author");
const Name kKeyProducer = Name("Producer");

}
   
const String &Info::creator() const
{
   return get<String>(kKeyCreator);
}

const String &Info::creationDate() const
{
   return get<String>(kKeyCreationDate);
}

const String &Info::author() const
{
   return get<String>(kKeyAuthor);
}

const String &Info::producer() const
{
   return get<String>(kKeyProducer);
}

void Info::prepare4Reading()
{
   insert<String>(kKeyCreator);
   insert<String>(kKeyCreationDate);
   insert<String>(kKeyAuthor);
   insert<String>(kKeyProducer);
}
   
}

}
