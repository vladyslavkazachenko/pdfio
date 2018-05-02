#include "action.h"

#include "name.h"

namespace pdfio
{
   
namespace pdf1_4
{
   
namespace
{
   
const Name kKeyS = Name("S");
const Name kKeyD = Name("D");
const Name kKeyType = Name("Type");
const Name kTypeValue = Name("Action");
   
}

Action::Action()
{
   insert<Name>(kKeyS);
}

Name &Action::s()
{
   return get<Name>(kKeyS);
}

bool Action::hasD() const
{
   return contains(kKeyD);
}

Destination &Action::d()
{
   return get<Destination>(kKeyD);
}

void Action::prepare4Reading()
{
   insert(kKeyType, kTypeValue);
   insert<Destination>(kKeyD);
}
 
Action::Type Action::type() const
{
   return Type::kGoTo;
}

Action::GoTo &Action::go2()
{
   return value_.go2_;
}
   
}

}
