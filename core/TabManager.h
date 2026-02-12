#ifndef TAB_MANAGER_H
#define TAB_MANAGER_H

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

public:
    TabId createTab(Url url);
    void closeTab(TabId id);
    Tab *getTab(TabId id);
    TabId getActiveTabId();
    void changeActiveTab(TabId id);
    void moveTab(TabId id, int newIndex);
    const std::vector<TabId> &getTabsOrder();
};
#endif