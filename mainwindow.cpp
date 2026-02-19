#include "mainwindow.h"
#include <QVBoxLayout>
#include "core/BrowserCore.h"
#include "core/EventTypes.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _centralWidget = new QWidget();
    auto centralLayout = new QVBoxLayout(_centralWidget);
    this->setCentralWidget(_centralWidget);

    _search = new QLineEdit(_centralWidget);
    _page = new QWebEngineView(_centralWidget);

    _core = std::make_unique<BrowserCore>();

    connect(_search, &QLineEdit::returnPressed, this,
            &MainWindow::onSearchEditingFinished
            // [&](){
            //     QString adr = _search->text();
            //     goToWebsite(adr);}
            );


    // подписка на событие из core
    // auto sub = ;

    _subscriptions.push_back(std::make_unique<Subscription<UrlVisitedArgs>>(_core->urlVisited.subscribe(
        [this](UrlVisitedArgs args)
        { this->onUrlVisited(QString::fromStdString(args.url.toStdString())); })));
    qDebug() << "\nSIZE = " << _core->urlVisited.handlersSize();


    connect(_page, &QWebEngineView::urlChanged, this,
            &MainWindow::onEngineUrlChanged
    );

    // auto sub2 = ;
    _subscriptions.push_back(std::make_unique<Subscription<UrlChangedArgs>>(_core->urlChanged.subscribe(
        [this](UrlChangedArgs args)
        { this->updateUrlBar(QString::fromStdString(args.url.toStdString())); })));

    _activeTabId = _core->createTab(Url("https://google.com"));

    centralLayout->addWidget(_search);
    centralLayout->addWidget(_page);
    this->setMinimumSize(1000, 700);
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

    qDebug() << "\nSIZE = " << _core->urlVisited.handlersSize();
    QMetaObject::invokeMethod(this, [this]
                              { _core->visitUrl(_activeTabId, Url(_search->text().toStdString())); }, Qt::QueuedConnection);
}

void MainWindow::onUrlVisited(QString address)
{
    _page->load(QUrl(address));
}

MainWindow::~MainWindow() {}
