#ifndef MODELS_H
#define MODELS_H

#include "types.h"
#include "Identifier.h"
#include "Url.h"
#include <string>

struct TabInfo {
    TabId id;
    Url url;
    std::string title;

    bool canGoBack;
    bool canGoForward;
    bool isLoading;
};
#endif
