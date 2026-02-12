#include "HandlerId.h"

HandlerId::HandlerId(unsigned int value_) : value(value_)
{}

bool HandlerId::operator==(const HandlerId& other) const
{
    return value == other.value;
}
