#ifndef EVENT_ARGS_H
#define EVENT_ARGS_H

// #include "Identifier.h"
// #include "Url.h"
#include "Identifier.h"
#include "models.h"




struct NavigationCompletedArgs
{
    NavigationType type;
    TabInfo tabInfo;
};

struct TabMovedArgs
{
    TabId id;
    int fromIndex;
    int toIndex;
};



#endif