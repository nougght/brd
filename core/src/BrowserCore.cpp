#include <core/BrowserCore.h>
#include "services/tabs/TabManager.h"


BrowserCore::BrowserCore() :  _eventLoopWorker([this] {_run(); })
{
    _subs.push_back(std::make_unique<Subscription<TabInfo>>(_tabManager->tabCreated.subscribe([this](TabInfo tabInfo)
          {
              this->tabCreated.invoke(tabInfo);
          })));
    _tabManager = std::make_unique<TabManager>();
}

BrowserCore::~BrowserCore()
{
    // отключаем event loop поток
    _shutdownEventLoop();
}

void BrowserCore::_shutdownEventLoop()
{
    _shouldStop = true;
    _condVar.notify_all();
    if (_eventLoopWorker.joinable())
    {
        _eventLoopWorker.join();
    }
}

void BrowserCore::_run()
{
    // выполняется в своем потоке пока не будет остановлен
    while (!_shouldStop)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(_mutex);
            // ожидание внешней остановки или появления новой задачи
            _condVar.wait(lock,
                          [this]
                          { return this->_shouldStop || !(this->_tasks.empty()); });
            if (_shouldStop)
                break;
            // перемещение данных в core поток
            task = std::move(_tasks.front());
            _tasks.pop();
        }
        // выполнение очередной задачи
        task();
    }
}

void BrowserCore::_post(std::function<void()> task)
{
    {
        // блокировка для доступа к очереди
        std::lock_guard<std::mutex> lock(_mutex);
        // добавляем задачу в очередь
        _tasks.push(std::move(task));
    }
    // уведомляем о появлении новой задачи
    _condVar.notify_one();
}

// TabManager *BrowserCore::getTabManager()
// {
//     return _tabManager.get();
// }

void BrowserCore::loadTabs()
{
    _post([this]()
          { tabsLoaded.invoke(_tabManager->getTabInfos()); });
}

void BrowserCore::createTab(Url url)
{
    _post([this, url = std::move(url)]
          {
              TabId id = _tabManager->createTab(url);
              // TabInfo tabInfo = _tabManager->getTab(id)->toTabInfo();
              // tabCreated.invoke(tabInfo);
              // navigationCompleted.invoke(NavigationCompletedArgs{NavigationType::NewPage, tabInfo});
          });
}

void BrowserCore::closeTab(TabId id)
{
    _post([this, id]
          {
              if (!id.isValid()) return;
              _tabManager->closeTab(id);
          });
}

void BrowserCore::visitUrl(TabId id, Url url)
{
    _post([this, id, url]
          {
              std::cerr << "\nVisitURL\n";
              if (!id.isValid())
                  return;
              _tabManager->visitUrl(id, url);
              navigationCompleted.invoke(NavigationCompletedArgs{
                                                                 NavigationType::NewPage,
                                                                 _tabManager->getTab(id)->toTabInfo()});
              // urlVisited.invoke(UrlVisitedArgs{id, url});
          });
}

void BrowserCore::changeTabUrl(TabId id, Url url)
{
    _post([this, id, url]
          {
              if (!id.isValid())
                  return;
              _tabManager->changeTabUrl(id, url);
              navigationCompleted.invoke(NavigationCompletedArgs{
                                                                 NavigationType::Redirect,
                                                                 _tabManager->getTab(id)->toTabInfo()});
          });
}




void BrowserCore::reloadTab(TabId id)
{
    if (!id.isValid())
        return;
    _tabManager->reloadTab(id);
    navigationCompleted.invoke(NavigationCompletedArgs{
                                                       NavigationType::Reload,
                                                       _tabManager->getTab(id)->toTabInfo()});
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

// --------

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

TabId BrowserCore::getActiveTabId()
{
    return _tabManager->getActiveTabId();
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
