#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWebEngineView>
#include<QVBoxLayout>
#include <memory>

#include "tabbarwithcontrol.h"
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
    void onTabCreated(TabInfo tabInfo);
    void onNavigationCompleted(NavigationCompletedArgs args);
    void onSearchEditingFinished();
    void onEngineUrlChanged(QUrl newUrl);
    void updateUrlBar(QUrl newUrl);
    void onUrlVisited(QUrl url);

private:
    void setupUI();
    void setupEvents();
    QWidget * _centralWidget;
    QVBoxLayout * _centralLayout;
    QLineEdit * _search;
    QWebEngineView * _page;
    TabBarWithControl * _tabBar;

    std::unique_ptr<BrowserCore> _core;
    TabId _activeTabId;
    std::vector<std::unique_ptr<ISubscription>> _subscriptions;
};
#endif // MAINWINDOW_H
