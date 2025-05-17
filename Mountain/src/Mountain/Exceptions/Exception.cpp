#include "Exception.hpp"

using namespace Mountain;

const char_t* Exception::GetMessage() const
{
    return what();
}
