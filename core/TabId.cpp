#include "TabId.h"

TabId::TabId()
{
    value = 0;
}

TabId::TabId(unsigned int value_) : value(value_)
{}

TabId::TabId(TabId &other) : value(other.value)
{}

TabId &TabId::operator=(const TabId& other)
{
    value = other.value;
    return *this;
}
TabId::operator size_t() const
{
    return value;
}
bool TabId::operator==(const TabId& other) const
{
    return value == other.value;
}

bool TabId::isValid()
{
    return !(value == 0);
}