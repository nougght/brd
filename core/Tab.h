#ifndef TAB_H
#define TAB_H

#include "TabId.h"
#include "TabHistory.h"

// browser tab state with visit history
class Tab {
private:
    TabId _id;
    TabHistory _history;
    Url _currentUrl;
    std::string _title;
    
public:
    Tab(TabId id, Url url);
    TabId getId();
    void visitUrl(Url url);
    bool canGoBack();
    bool canGoForward();
    void goBack();
    void goForward();

    void onTitleChanged(std::string &title);
};
#endif