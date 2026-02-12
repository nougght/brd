#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWebEngineView>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onSearchEditingFinished();
    void onUrlChanged(QUrl newUrl);
private:
    void setupUI();
    void goToWebsite(QString address);
    QWidget * _centralWidget;
    QLineEdit * _search;
    QWebEngineView * _page;
};
#endif // MAINWINDOW_H
