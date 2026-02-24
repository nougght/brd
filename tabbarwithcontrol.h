#ifndef TABBARWITHCONTROL_H
#define TABBARWITHCONTROL_H

#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>

class TabBarWithControl : public QFrame
{
    Q_OBJECT
public:
    TabBarWithControl(QWidget *parent);
    void setupUI();
signals:
    void closeClicked();
    void minimiseClicked();
private:
    QHBoxLayout *_layout;
    QListView *_tabsList;
    QFrame *_controlPanel;
    QPushButton *_minimiseButton;
    QPushButton *_closeButton;
};

#endif // TABBARWITHCONTROL_H
