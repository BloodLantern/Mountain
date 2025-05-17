#include "ConcurrentModificationException.hpp"

using namespace Mountain;

ConcurrentModificationException::ConcurrentModificationException()
    : Exception(Message)
{
}
