#include "mainwindow.h"
#include <QVBoxLayout>
#include <core/BrowserCore.h>
#include <core/models.h>
#include <core/types.h>
#include <core/eventArgs.h>
#include <QWebEngineProfile>
#include <Qt>

QUrl convert(Url url)
{
    return QUrl(QString::fromStdString(url.toStdString()));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setupEvents();
    qDebug() << QWebEngineProfile::defaultProfile()->httpUserAgent();
    qDebug() << "\nSIZE = " << _core->navigationCompleted.handlersSize();

    _core->loadTabs();
}

void MainWindow::setupUI()
{
    _centralWidget = new QWidget();
    _centralLayout = new QVBoxLayout(_centralWidget);
    _centralLayout->setContentsMargins(0,0,0,0);
    this->setCentralWidget(_centralWidget);
    _tabBar = new TabBarWithControl(_centralWidget);
    _search = new QLineEdit(_centralWidget);

    _stackedWidget = new QStackedWidget(_centralWidget);
    // _page = new QWebEngineView(_centralWidget);

    _core = std::make_unique<BrowserCore>();

    _centralLayout->addWidget(_tabBar);
    _centralLayout->addWidget(_search);
    _centralLayout->addWidget(_stackedWidget);
    this->setMinimumSize(1000, 700);
    this->setWindowFlags(Qt::WindowFlags::enum_type::FramelessWindowHint);
}

void MainWindow::setupEvents()
{
    // подписка на события из core
    // добавляем обработчик через invokeMethod, чтобы передать его в Qt поток


    _subscriptions.push_back(std::make_unique<Subscription<std::vector<TabInfo>>>(
        _core->tabsLoaded.subscribe([this](std::vector<TabInfo> tabs){
            QMetaObject::invokeMethod(this,[this, tabs = std::move(tabs)]() {
                this->onTabsLoaded(std::move(tabs));});
        })));

    _subscriptions.push_back(std::make_unique<Subscription<TabInfo>>(_core->tabCreated.subscribe(
        [this](TabInfo tabInfo)
        { QMetaObject::invokeMethod(this, [this, tabInfo] ()
                                    {this->onTabCreated(tabInfo); }, Qt::QueuedConnection); })));


    _subscriptions.push_back(std::make_unique<Subscription<TabId>>(_core->activeTabChanged.subscribe(
        [this](TabId id)
        { QMetaObject::invokeMethod(this, [this, id] ()
                                    {this->onActiveTabChanged(id); }, Qt::QueuedConnection); })));

    _subscriptions.push_back(std::make_unique<Subscription<NavigationCompletedArgs>>(
        _core->navigationCompleted.subscribe(
            [this](NavigationCompletedArgs args)
            { QMetaObject::invokeMethod(this, [this, args] ()
                                        {this->onNavigationCompleted(args); }, Qt::QueuedConnection); })));


    connect(_search, &QLineEdit::returnPressed, this,
            &MainWindow::onSearchEditingFinished
            // [&](){
            //     QString adr = _search->text();
            //     goToWebsite(adr);}
            );


    // подписка на событие из core
    // auto sub = ;



    // // auto sub2 = ;
    // _subscriptions.push_back(std::make_unique<Subscription<UrlChangedArgs>>(_core->urlChanged.subscribe(
    //     [this](UrlChangedArgs args)
    //     { this->updateUrlBar(QString::fromStdString(args.url.toStdString())); })));

    connect(_tabBar, &TabBarWithControl::newTabClicked, this, &MainWindow::onNewTabClicked);
    connect(_tabBar, &TabBarWithControl::tabClicked, this, &MainWindow::onTabClicked);
    connect(_tabBar, &TabBarWithControl::minimiseClicked, this, &MainWindow::showMinimized);
    connect(_tabBar, &TabBarWithControl::closeClicked, this, &MainWindow::close);

}


void MainWindow::onNewTabClicked()
{
    _core->createTab();
}


void MainWindow::onTabClicked(TabId id)
{
    _core->changeActiveTab(id);
}

void MainWindow::onNavigationCompleted(NavigationCompletedArgs args)
{
    qDebug() << "\nNavigationHandlers " << _core->navigationCompleted.handlersSize() << "\n";
    switch(args.type)
    {
    case NavigationType::NewPage:
        onUrlVisited(args.tabInfo.url);
        break;
    case NavigationType::BackForward:
        // onUrlVisited(convert(args.tabInfo.url));
        break;
    case NavigationType::Redirect:
        updateUrlBar(convert(args.tabInfo.url));
        break;
    case NavigationType::Reload:
        // onUrlVisited(convert(args.tabInfo.url));
        break;

    }
}

void MainWindow::onTabsLoaded(std::vector<TabInfo> tabs)
{
    for (int i = 0; i < tabs.size(); ++i)
    {
        auto tabWidget = new QWebEngineView();

        _stackedWidget->addWidget(tabWidget);

        connect(tabWidget, &QWebEngineView::urlChanged, this,
                [this, id = tabs[i].id] (QUrl url){
                    onEngineUrlChanged(id, url);
                });

        tabWidget->load(convert(tabs[i].url));
        _tabWidgets[tabs[i].id] = std::move(tabWidget);
    }
    TabId lastId = tabs.back().id;
    _tabBar->setInitialTabs(std::move(tabs));
    onActiveTabChanged(lastId);
}


void MainWindow::onTabCreated(TabInfo tabInfo)
{
    _tabBar->addTab(tabInfo);

    auto tabWidget = new QWebEngineView();

    _stackedWidget->addWidget(tabWidget);

    connect(tabWidget, &QWebEngineView::urlChanged, this,
            [this, id = tabInfo.id](QUrl url){
                        onEngineUrlChanged(id, url);
                });

    tabWidget->load(convert(tabInfo.url));
    _tabWidgets[tabInfo.id] = std::move(tabWidget);
    onActiveTabChanged(tabInfo.id);

}


void MainWindow::onEngineUrlChanged(TabId id, QUrl newUrl)
{
    // QMetaObject::invokeMethod(this, [this, newUrl]{
        _core->changeTabUrl(id, Url(newUrl.toString().toStdString()));
    // }, Qt::QueuedConnection);
}

void MainWindow::updateUrlBar(QUrl newUrl)
{
    if (_search->text() != newUrl) {
        QSignalBlocker blocker(_search);
        _search->setText(newUrl.toString());
        _search->setCursorPosition(0);
    }
}

void MainWindow::onSearchEditingFinished()
{
    // goToWebsite(_search->text());

    // qDebug() << "\nSIZE = " << _core->urlVisited.handlersSize();
    _core->visitUrl(_activeTabId, Url(_search->text().toStdString()));
}

void MainWindow::onUrlVisited(Url url)
{
    _tabBar->updateTabUrl(_activeTabId, url);
    _tabWidgets[_activeTabId]->load(convert(url));
}


void MainWindow::onActiveTabChanged(TabId tabId) {
    auto it = _tabWidgets.find(tabId);
    if (it != _tabWidgets.end()) {
        // находим индекс виджета и переключаемся
        int index = _stackedWidget->indexOf(it->second);
        _stackedWidget->setCurrentIndex(index);

        it->second->setFocus();
        _activeTabId = tabId;
    }
}

MainWindow::~MainWindow() {}
