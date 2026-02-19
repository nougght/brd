#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWebEngineView>
#include <memory>


#include "core/BrowserCore.h"
#include "core/Url.h"
#include "core/TabId.h"
#include "core/Event.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onSearchEditingFinished();
    void onEngineUrlChanged(QUrl newUrl);
    void updateUrlBar(QUrl newUrl);
private:
    void setupUI();
    void onUrlVisited(QString address);
    QWidget * _centralWidget;
    QLineEdit * _search;
    QWebEngineView * _page;

    std::unique_ptr<BrowserCore> _core;
    TabId _activeTabId;
    std::vector<std::unique_ptr<ISubscription>> _subscriptions;
};
#endif // MAINWINDOW_H
