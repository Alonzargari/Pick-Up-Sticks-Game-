#include "FormatException.h"

FormatException::FormatException(std::string str)
	:std::runtime_error(str)
{
}
