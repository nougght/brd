#include "TabId.h"

TabId::TabId(unsigned int value_) : value(value_)
{}

TabId::TabId(TabId &other) : value(other.value)
{}

bool TabId::operator==(const TabId& other) const
{
    return value == other.value;
}
