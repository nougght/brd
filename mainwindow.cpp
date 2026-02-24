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
}

void MainWindow::setupUI()
{
    _centralWidget = new QWidget();
    _centralLayout = new QVBoxLayout(_centralWidget);
    _centralLayout->setContentsMargins(0,0,0,0);
    this->setCentralWidget(_centralWidget);
    _tabBar = new TabBarWithControl(_centralWidget);
    _search = new QLineEdit(_centralWidget);
    _page = new QWebEngineView(_centralWidget);

    _core = std::make_unique<BrowserCore>();

    _centralLayout->addWidget(_tabBar);
    _centralLayout->addWidget(_search);
    _centralLayout->addWidget(_page);
    this->setMinimumSize(1000, 700);
    this->setWindowFlags(Qt::WindowFlags::enum_type::FramelessWindowHint);
}

void MainWindow::setupEvents()
{
    // подписка на события из core
    // добавляем обработчик через invokeMethod, чтобы передать его в Qt поток

    _subscriptions.push_back(std::make_unique<Subscription<TabInfo>>(_core->tabCreated.subscribe(
        [this](TabInfo tabInfo)
        { QMetaObject::invokeMethod(this, [this, tabInfo] ()
                                    {this->onTabCreated(tabInfo); }, Qt::QueuedConnection); })));


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


    connect(_page, &QWebEngineView::urlChanged, this,
            &MainWindow::onEngineUrlChanged
            );

    // // auto sub2 = ;
    // _subscriptions.push_back(std::make_unique<Subscription<UrlChangedArgs>>(_core->urlChanged.subscribe(
    //     [this](UrlChangedArgs args)
    //     { this->updateUrlBar(QString::fromStdString(args.url.toStdString())); })));

    connect(_tabBar, &TabBarWithControl::minimiseClicked, this, &MainWindow::showMinimized);
    connect(_tabBar, &TabBarWithControl::closeClicked, this, &MainWindow::close);

}

void MainWindow::onNavigationCompleted(NavigationCompletedArgs args)
{
    switch(args.type)
    {
    case NavigationType::NewPage:
        onUrlVisited(convert(args.tabInfo.url));
        break;
    case NavigationType::BackForward:
        // onUrlVisited(convert(args.tabInfo.url));
        break;
    case NavigationType::Redirect:
        onEngineUrlChanged(convert(args.tabInfo.url));
        break;
    case NavigationType::Reload:
        // onUrlVisited(convert(args.tabInfo.url));
        break;

    }

}

void MainWindow::onTabCreated(TabInfo tabInfo)
{
    _activeTabId = tabInfo.id;
}

void MainWindow::onEngineUrlChanged(QUrl newUrl)
{
    QMetaObject::invokeMethod(this, [this, newUrl]{
        _core->changeTabUrl(_activeTabId, Url(newUrl.toString().toStdString()));
    }, Qt::QueuedConnection);
}

void MainWindow::updateUrlBar(QUrl newUrl)
{
    if (_search->text() != newUrl) {
        QSignalBlocker blocker(_search);
        _search->setText(newUrl.toString());
    }
}

void MainWindow::onSearchEditingFinished()
{
    // goToWebsite(_search->text());

    // qDebug() << "\nSIZE = " << _core->urlVisited.handlersSize();
    _core->visitUrl(_activeTabId, Url(_search->text().toStdString()));
}

void MainWindow::onUrlVisited(QUrl url)
{
    _page->load(url);
}

MainWindow::~MainWindow() {}
