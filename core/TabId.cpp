#include "TabId.h"

TabId::TabId(unsigned int value_) : value(value_)
{}

bool TabId::operator==(const TabId& other) const
{
    return value == other.value;
}
