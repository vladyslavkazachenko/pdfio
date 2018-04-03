#include "read_real.h"

namespace pdf1_0 = pdfio::pdf1_0;

std::istream &operator>>(std::istream &istream, pdf1_0::Real &real)
{
  double buffer;
  if(istream >> buffer)
  {
    real = buffer;
  }
  return istream;
}