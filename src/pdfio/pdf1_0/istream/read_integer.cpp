#include "read_integer.h"

std::istream &operator>>(std::istream &istream, pdf1_0::Integer &integer)
{
	long long buffer;
	if(istream >> buffer)
	{
		integer = buffer;
	}
	return istream;
}