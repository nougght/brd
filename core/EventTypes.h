#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

#include "Identifier.h"
#include "Url.h"

struct UrlVisitedArgs
{
    TabId id;
    Url url;
};

struct UrlChangedArgs
{
    TabId id;
    Url url;
};
#endif