#pragma once

#ifdef PDF_VERSION
#if PDF_VERSION == 1_7
#include "pdf1_7/pdf.h"
namespace pdfio
{
	namespace pdf = pdf1_7;
}
#elif  PDF_VERSION == 1_0
#include "pdf1_0/pdf.h"
namespace pdfio
{
	namespace pdf = pdf1_0;
}
#endif //PDF_VERSION == 1_7
#endif //PDF_VERSION