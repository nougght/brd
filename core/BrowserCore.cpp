#include "BrowserCore.h"

BrowserCore::BrowserCore() : _tabManager(std::make_unique<TabManager>())
{
}

TabManager *BrowserCore::getTabManager()
{
    return _tabManager.get();
}

TabId BrowserCore::createTab(Url url)
{
    TabId id = _tabManager->createTab(url);
    urlVisited.invoke(UrlVisitedArgs{id, url});
    return id;
}

void BrowserCore::closeTab(TabId id)
{
    if (!id.isValid())
        return;

    _tabManager->closeTab(id);
}

TabId BrowserCore::getActiveTabId()
{
    return _tabManager->getActiveTabId();
}

void BrowserCore::changeActiveTab(TabId id)
{
    if (!id.isValid())
        return;
    _tabManager->changeActiveTab(id);
}
void BrowserCore::moveTab(TabId id, int newIndex)
{
    if (!id.isValid())
        return;
    _tabManager->moveTab(id, newIndex);
}

Tab *BrowserCore::getTab(TabId id)
{
    if (!id.isValid())
        return nullptr;
    return _tabManager->getTab(id);
}

const std::vector<TabId> &BrowserCore::getTabsOrder()
{
    return _tabManager->getTabsOrder();
}

void BrowserCore::visitUrl(TabId id, Url url)
{
    std::cerr <<"\nVisitURL\n";
    if (!id.isValid())
        return;
    _tabManager->visitUrl(id, url);
    urlVisited.invoke(UrlVisitedArgs{id, url});
}

bool BrowserCore::canGoBack(TabId id)
{
    if (!id.isValid())
        return false;
    return _tabManager->canGoBack(id);
}
bool BrowserCore::canGoForward(TabId id)
{
    if (!id.isValid())
        return false;
    return _tabManager->canGoForward(id);
}
void BrowserCore::goBack(TabId id)
{
    if (!id.isValid())
        return;
    _tabManager->goBack(id);
}
void BrowserCore::goForward(TabId id)
{
    if (!id.isValid())
        return;
    _tabManager->goForward(id);
}

void BrowserCore::changeTabUrl(TabId id, Url url)
{
    if (!id.isValid())
        return;
    _tabManager->changeTabUrl(id, url);
    urlChanged.invoke(UrlChangedArgs{id, url});
}