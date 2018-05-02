#include "action.h"

namespace pdfio
{
   
namespace pdf1_4
{
 
Action::Type Action::type() const
{
   return Type::kGoTo;
}
 
void Action::prepare4Reading()
{
   
}
   
}

}
