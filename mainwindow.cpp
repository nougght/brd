#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _centralWidget = new QWidget();
    auto centralLayout = new QVBoxLayout(_centralWidget);
    this->setCentralWidget(_centralWidget);

    _search = new QLineEdit(_centralWidget);
    connect(_search, &QLineEdit::editingFinished, this,
            &MainWindow::onSearchEditingFinished
        // [&](){
        //     QString adr = _search->text();
        //     goToWebsite(adr);}
    );

    centralLayout->addWidget(_search);
    _page = new QWebEngineView(_centralWidget);
    goToWebsite("https://github.com/");
    connect(_page, &QWebEngineView::urlChanged, this, &MainWindow::onUrlChanged);
    this->setMinimumSize(1000, 700);
    centralLayout->addWidget(_page);

}

void MainWindow::onUrlChanged(QUrl newUrl)
{
    _search->setText(newUrl.toString());
}

void MainWindow::onSearchEditingFinished()
{
    goToWebsite(_search->text());
}

void MainWindow::goToWebsite(QString address)
{
    _page->load(QUrl(address));
}

MainWindow::~MainWindow() {}
