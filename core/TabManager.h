#ifndef TAB_MANAGER_H
#define TAB_MANAGER_H

#include "Identifier.h"
#include "Tab.h"
#include "TabIdGenerator.h"
#include <unordered_map>
#include <vector>
#include <memory>

class TabManager
{
private:
    std::unordered_map<TabId, std::unique_ptr<Tab>> _tabs;
    // порядок вкладок
    std::vector<TabId> _tabsOrder;
    TabIdGenerator _idGenerator;
    TabId _activeTabId;

    std::pair<TabId, std::unique_ptr<Tab>> _findTab(TabId id);

public:
    TabId createTab(Url url);
    void closeTab(TabId id);
    TabId getActiveTabId();
    void changeActiveTab(TabId id);
    void moveTab(TabId id, int newIndex);
    Tab *getTab(TabId id);
    const std::vector<TabId> &getTabsOrder();

    bool canGoBack(TabId id);
    bool canGoForward(TabId id);
    void goBack(TabId id);
    void goForward(TabId id);

    void visitUrl(TabId id, Url url);
    void changeTabUrl(TabId id, Url url);
};

#endif