#ifndef BROWSER_CORE_H
#define BROWSER_CORE_H

#include <string>
#include <vector>
#include <memory>
#include "TabManager.h"
#include "Event.h"

class BrowserCore
{
private:
    std::unique_ptr<TabManager> _tabManager;
public:
    BrowserCore();
    TabManager *getTabManager();


    TabId createTab(Url url);
    void closeTab(TabId id);
    TabId getActiveTabId();
    void changeActiveTab(TabId id);
    void moveTab(TabId id, int newIndex);
    Tab *getTab(TabId id);
    const std::vector<TabId> &getTabsOrder();

    void visitUrl(TabId id, Url url);
    bool canGoBack(TabId id);
    bool canGoForward(TabId id);
    void goBack(TabId id);
    void goForward(TabId id);




    // events
    Event<std::string> goToWebsite;
    
};
#endif