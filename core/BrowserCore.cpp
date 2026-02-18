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
    _tabManager->createTab(url);
    goToWebsite.emit(url.toStdString());
}


void BrowserCore::closeTab(TabId id)
{
    _tabManager->closeTab(id);
}

TabId BrowserCore::getActiveTabId()
{
    return _tabManager->getActiveTabId();
}
void BrowserCore::changeActiveTab(TabId id)
{
    _tabManager->changeActiveTab(id);
}
void BrowserCore::moveTab(TabId id, int newIndex)
{
    _tabManager->moveTab(id, newIndex);
}

Tab *BrowserCore::getTab(TabId id)
{
    return _tabManager->getTab(id);
}

const std::vector<TabId> &BrowserCore::getTabsOrder()
{
    return _tabManager->getTabsOrder();
}

void BrowserCore::visitUrl(TabId id, Url url)
{
    _tabManager->visitUrl(id, url);
    goToWebsite.emit(url.toStdString());
}

bool BrowserCore::canGoBack(TabId id)
{
    return _tabManager->canGoBack(id);
}
bool BrowserCore::canGoForward(TabId id)
{
    return _tabManager->canGoForward(id);
}
void BrowserCore::goBack(TabId id)
{
    _tabManager->goBack(id);
}
void BrowserCore::goForward(TabId id)
{
    _tabManager->goForward(id);
}