#include "tabbarwithcontrol.h"
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QSizePolicy>
#include "tabsmodel.h"

TabBarWithControl::TabBarWithControl(QWidget *parent) : QFrame(parent)
{
    setupUI();
}

void TabBarWithControl::setupUI()
{
    _layout = new QHBoxLayout(this);
    _layout->setSpacing(0);
    _layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(_layout);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    _tabsList = new QListView();
    _tabsList->setFlow(QListView::LeftToRight);
    _tabsList->setWrapping(false);
    _tabsList->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    _tabsList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    TabsModel *model = new TabsModel();
    model->addItem("один");
    model->addItem("два");
    _tabsList->setModel(model);
    _layout->addWidget(_tabsList);
    auto spacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    _layout->addItem(spacer);

    _controlPanel = new QFrame();
    auto _controlLayout = new QHBoxLayout(_controlPanel);


    _minimiseButton = new QPushButton("—");
    _minimiseButton->setObjectName("minimiseButton");
    connect(_minimiseButton, &QPushButton::clicked, this, [this]{emit this->minimiseClicked();});
    _closeButton = new QPushButton("✕");
    _closeButton->setObjectName("closeButton");
    connect(_closeButton, &QPushButton::clicked, this, [this]{emit this->closeClicked();});


    _controlLayout->setContentsMargins(0, 0, 0, 0);
    _controlLayout->setSpacing(0);
    _controlLayout->addWidget(_minimiseButton);
    _controlLayout->addWidget(_closeButton);
    _layout->addWidget(_controlPanel);
    qDebug() << _layout->count();
}
