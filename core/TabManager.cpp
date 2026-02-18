#include "TabManager.h"

TabId TabManager::createTab(Url url)
{
    auto tab = std::make_unique<Tab>(_idGenerator.create(), std::move(url));
    _tabs.emplace(tab->getId(), tab);

    _tabsOrder.push_back(tab->getId());
}

void TabManager::closeTab(TabId id)
{
    auto it = std::find(_tabsOrder.begin(), _tabsOrder.end(), id);
    if (it != _tabsOrder.end() && _activeTabId == id)
    {
        if (_tabs.size() == 1)
        {
            // to do: закрытие последней вкладки
        }
        else
        {
            auto nextIt = std::next(it);
            // переход на правую от текущей вкладки
            if (nextIt != _tabsOrder.end())
            {
                _activeTabId = *(nextIt);
            }
            else
            {
                _activeTabId = *(std::prev(it));
            }
        }
        _tabsOrder.erase(it);
        _tabs.erase(id);
    }
}

Tab *TabManager::getTab(TabId id)
{
    auto tabIt = _tabs.find(id);
    if (tabIt != _tabs.end())
    {
        return tabIt->second.get();
    }
}

TabId TabManager::getActiveTabId()
{
    return _activeTabId;
}

void TabManager::changeActiveTab(TabId id)
{
    if (_tabs.find(id) != _tabs.end())
    {
        _activeTabId = id;
    }
}

void TabManager::moveTab(TabId id, int newIndex)
{
    auto it = std::find(_tabsOrder.begin(), _tabsOrder.end(), id);
    if (it != _tabsOrder.end())
    {
        _tabsOrder.erase(it);
        _tabsOrder.insert(_tabsOrder.begin() + newIndex, id);
    }
}

const std::vector<TabId> &TabManager::getTabsOrder()
{
    return _tabsOrder;
}

bool TabManager::canGoBack(TabId id)
{
    auto existing = _tabs.find(id);
    if (existing != _tabs.end())
    {
        return existing->second->canGoBack();
    }
    return false;
}
bool TabManager::canGoForward(TabId id)
{

    auto existing = _tabs.find(id);
    if (existing != _tabs.end())
    {
        return existing->second->canGoForward();
    }
    return false;
}
void TabManager::goBack(TabId id)
{

    auto existing = _tabs.find(id);
    if (existing != _tabs.end())
    {
        existing->second->goBack();
    }
}
void TabManager::goForward(TabId id)
{

    auto existing = _tabs.find(id);
    if (existing != _tabs.end())
    {
        existing->second->goForward();
    }
}

void TabManager::visitUrl(TabId id, Url url)
{
    auto existing = _tabs.find(id);
    if (existing != _tabs.end())
    {
        existing->second->visitUrl(url);
    }
}