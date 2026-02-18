#include "mainwindow.h"
#include <QVBoxLayout>
#include "core/BrowserCore.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _centralWidget = new QWidget();
    auto centralLayout = new QVBoxLayout(_centralWidget);
    this->setCentralWidget(_centralWidget);

    _search = new QLineEdit(_centralWidget);
    _page = new QWebEngineView(_centralWidget);

    _core = std::make_unique<BrowserCore>();
    _activeTabId = _core->createTab(Url("https://google.com"));

    // подписка на событие из core
    _core->goToWebsite.subscribe(
        [this](std::string url){
            this->onGoToWebsite(QString::fromStdString(url));});


    connect(_search, &QLineEdit::editingFinished, this,
            &MainWindow::onSearchEditingFinished
        // [&](){
        //     QString adr = _search->text();
        //     goToWebsite(adr);}
    );

    connect(_page, &QWebEngineView::urlChanged, this, &MainWindow::onUrlChanged);

    centralLayout->addWidget(_search);
    centralLayout->addWidget(_page);
    this->setMinimumSize(1000, 700);

}

void MainWindow::onUrlChanged(QUrl newUrl)
{
    _search->setText(newUrl.toString());
}

void MainWindow::onSearchEditingFinished()
{
    // goToWebsite(_search->text());
    _core->visitUrl(_activeTabId, Url(_search->text().toStdString()));
}

void MainWindow::onGoToWebsite(QString address)
{
    _page->load(QUrl(address));
}

MainWindow::~MainWindow() {}
