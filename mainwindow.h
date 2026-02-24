#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWebEngineView>
#include <QVBoxLayout>
#include <QStackedWidget>

#include <memory>
#include <map>

#include "tabbarwithcontrol.h"
#include "tabsmodel.h"

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
    void onTabsLoaded(std::vector<TabInfo>);
    void onTabCreated(TabInfo tabInfo);
    void onNavigationCompleted(NavigationCompletedArgs args);
    void onSearchEditingFinished();
    void onEngineUrlChanged(TabId id, QUrl newUrl);
    void updateUrlBar(QUrl newUrl);
    void onUrlVisited(Url url);

    void onActiveTabChanged(TabId id);

    void onNewTabClicked();
    void onTabClicked(TabId id);

private:
    void setupUI();
    void setupEvents();
    QWidget * _centralWidget;
    QVBoxLayout * _centralLayout;
    QLineEdit * _search;
    TabBarWithControl * _tabBar;
    QStackedWidget * _stackedWidget;


    std::unique_ptr<BrowserCore> _core;
    TabId _activeTabId;
    std::vector<std::unique_ptr<ISubscription>> _subscriptions;
    std::map<TabId, QWebEngineView*> _tabWidgets;
};
#endif // MAINWINDOW_H
