#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWebEngineView>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QProgressBar>

#include <memory>
#include <map>

#include "tabbarwithcontrol.h"
#include "tabsmodel.h"

#include "core/BrowserCore.h"
#include "core/Url.h"
#include "core/TabId.h"
#include "core/Event.h"


// to do: выделить контроллер из виджета и оставить только ui

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
    void onEngineTitleChanged(TabId id, QString newTitle);
    void onLoadingStatusChanged(TabId id, bool isLoading);
    void onLoadingProgressChanged(TabId id, int progress);

    void setLoadingBarVisible(bool isVisible);
    void updateUrlBar(QUrl newUrl);
    void updateTabTitle(TabId id, std::string title);
    void reloadTab(TabId id);
    void navigateBack(TabInfo tabInfo);
    void navigateForward(TabInfo tabInfo);
    void onUrlVisited(TabInfo tab);
    void onTabsModelDataChanged(const QModelIndex &topLeft,
                                const QModelIndex &bottomRight,
                                const QList<int> &roles = QList<int>());

    void onActiveTabChanged(TabId id);

    void onNewTabClicked();
    void onTabClicked(TabId id);
    void onReloadClicked();
    void onBackClicked();
    void onForwardClicked();

private:
    void setupUI();
    void setupEvents();
    void setupTabViewEvents(TabId tabId, QWebEngineView *tabView);

    TabsModel *_tabsModel;

    QWidget * _centralWidget;
    QVBoxLayout * _centralLayout;
    QHBoxLayout * _searchBarLayout;
    QLineEdit * _search;
    QPushButton * _reloadButton;
    QPushButton * _backButton;
    QPushButton * _forwardButton;
    TabBarWithControl * _tabBar;
    QProgressBar * _loadingBar;
    QWidget * _prgsBarPlaceholder;
    QStackedWidget * _stackedWidget;


    std::unique_ptr<BrowserCore> _core;
    TabId _activeTabId;
    std::map<TabId, QWebEngineView*> _tabWidgets;
};
#endif // MAINWINDOW_H
