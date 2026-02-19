#include "HandlerId.h"

HandlerId::HandlerId(unsigned int value_) : value(value_)
{}

HandlerId::operator size_t() const
{
    return value;
}
bool HandlerId::operator==(const HandlerId& other) const
{
    return value == other.value;
}
