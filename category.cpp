#include "category.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include "mainwindow.h"


category::category(QWidget* parent,Qt::WindowFlags f):QToolBox(parent,f)
{    
    //outcome layer
    this->move(600,250);
    setWindowTitle(tr("Add Accout"));
    outBtn_1 = new QToolButton;
    outBtn_1->setText(tr("General Expenditure"));
    outBtn_1->setIcon(QPixmap(":/images/expenditure.jpg"));
    //outBtn_1->setIconSize(QPixmap(":/images/expenditure.jpg").size());
    outBtn_1->setAutoRaise(true);
    outBtn_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    outBtn_2 = new QToolButton;
    outBtn_2->setIcon(QPixmap(":/images/foods.png"));
    outBtn_2->setText(tr("Food"));
    outBtn_2->setAutoRaise(true);
    outBtn_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    outBtn_3 = new QToolButton;
    outBtn_3->setIcon(QPixmap(":/images/entertainment.png"));
    outBtn_3->setText(tr("Entertainment"));
    outBtn_3->setAutoRaise(true);
    outBtn_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    outBtn_4 = new QToolButton;
    outBtn_4->setIcon(QPixmap(":/images/transport.png"));
    outBtn_4->setText(tr("Transportation"));
    outBtn_4->setAutoRaise(true);
    outBtn_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    outBtn_5 = new QToolButton;
    outBtn_5->setIcon(QPixmap(":/images/Dressing.png"));
    outBtn_5->setText(tr("Dressing"));
    outBtn_5->setAutoRaise(true);
    outBtn_5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    outBtn_6 = new QToolButton;
    outBtn_6->setIcon(QPixmap(":/images/neccessity.png"));
    outBtn_6->setText(tr("Daily Necessity"));
    outBtn_6->setAutoRaise(true);
    outBtn_6->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    outBtn_7 = new QToolButton;
    outBtn_7->setIcon(QPixmap(":/images/digital.png"));
    outBtn_7->setText(tr("Digital"));
    outBtn_7->setAutoRaise(true);
    outBtn_7->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    outBtn_8 = new QToolButton;
    outBtn_8->setIcon(QPixmap(":/images/celephone.png"));
    outBtn_8->setText(tr("Celephone"));
    outBtn_8->setAutoRaise(true);
    outBtn_8->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    outBtn_9 = new QToolButton;
    outBtn_9->setIcon(QPixmap(":/images/house.png"));
    outBtn_9->setText(tr("Housing"));
    outBtn_9->setAutoRaise(true);
    outBtn_9->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    outBtn_10 = new QToolButton;
    outBtn_10->setIcon(QPixmap(":/images/Education.png"));
    outBtn_10->setText(tr("Education"));
    outBtn_10->setAutoRaise(true);
    outBtn_10->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    outBtn_11 = new QToolButton;
    outBtn_11->setIcon(QPixmap(":/images/medicine.png"));
    outBtn_11->setText(tr("Medical"));
    outBtn_11->setAutoRaise(true);
    outBtn_11->setIcon(QPixmap(":/images/medicine.png"));
    outBtn_11->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    outBtn_12 = new QToolButton;
    outBtn_12->setIcon(QPixmap(":/images/Pet.png"));
    outBtn_12->setText(tr("Pet"));
    outBtn_12->setAutoRaise(true);
    outBtn_12->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    outBtn_add = new QToolButton;
    outBtn_add->setAutoFillBackground(true);
    outBtn_add->setStyleSheet("Background-color:rgb(216,191,216);color:rgb(10,10,10)");
    outBtn_add->setText(tr("＋new label"));
    outBtn_add->setAutoRaise(true);
    outBtn_add->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QGroupBox *groupBox1 = new QGroupBox;
    QVBoxLayout *layout1 = new QVBoxLayout(groupBox1);
    layout1 ->setMargin(10);
    layout1 ->setAlignment(Qt::AlignCenter);
    layout1->addWidget(outBtn_1);
    layout1->addWidget(outBtn_2);
    layout1->addWidget(outBtn_3);
    layout1->addWidget(outBtn_4);
    layout1->addWidget(outBtn_5);
    layout1->addWidget(outBtn_6);
    layout1->addWidget(outBtn_7);
    layout1->addWidget(outBtn_8);
    layout1->addWidget(outBtn_9);
    layout1->addWidget(outBtn_10);
    layout1->addWidget(outBtn_11);
    layout1->addWidget(outBtn_12);
    layout1->addWidget(outBtn_add);
    layout1->addStretch();
    //income layer
    inBtn_1 = new QToolButton;
    inBtn_1->setIcon(QPixmap(":/images/salary.png"));
    inBtn_1->setText(tr("Salary"));
    inBtn_1->setAutoRaise(true);
    inBtn_1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    inBtn_2 = new QToolButton;
    inBtn_2->setIcon(QPixmap(":/images/revenue.png"));
    inBtn_2->setText(tr("Revenue"));
    inBtn_2->setAutoRaise(true);
    inBtn_2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    inBtn_3 = new QToolButton;
    inBtn_3->setIcon(QPixmap(":/images/tips.jpg"));
    inBtn_3->setText(tr("Wechat tips"));
    inBtn_3->setAutoRaise(true);
    inBtn_3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    inBtn_4 = new QToolButton;
    inBtn_4->setIcon(QPixmap(":/images/invest.png"));
    inBtn_4->setText(tr("Investment"));
    inBtn_4->setAutoRaise(true);
    inBtn_4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    inBtn_add = new QToolButton;
    inBtn_add->setText(tr("＋new Label"));
    inBtn_add->setAutoFillBackground(true);
    inBtn_add->setStyleSheet("Background-color:rgb(216,191,216);color:rgb(10,10,10)");
    inBtn_add->setAutoRaise(true);
    inBtn_add->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QGroupBox *groupBox2 = new QGroupBox;
    QVBoxLayout *layout2 = new QVBoxLayout(groupBox2);
    layout2 ->setMargin(10);
    layout2 ->setAlignment(Qt::AlignCenter);
    layout2 ->addWidget(inBtn_1);
    layout2->addWidget(inBtn_2);
    layout2->addWidget(inBtn_3);
    layout2->addWidget(inBtn_4);
    layout2->addWidget(inBtn_add);

    this->addItem((QWidget*)groupBox1,tr("Expenditure"));
    this->addItem((QWidget*)groupBox2,tr("Income"));

    connect(this->outBtn_1,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->outBtn_2,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->outBtn_3,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->outBtn_4,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->outBtn_5,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->outBtn_6,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->outBtn_7,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->outBtn_8,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->outBtn_9,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->outBtn_10,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->outBtn_11,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->outBtn_12,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->outBtn_add,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->inBtn_1,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->inBtn_2,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->inBtn_3,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->inBtn_4,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
    connect(this->inBtn_add,SIGNAL(clicked(bool)),this,SLOT(add_entry()));
}


void category::add_entry() {
    MainWindow *p = NULL;
    QToolButton* obj = qobject_cast<QToolButton*>(sender());
    p = qobject_cast<MainWindow*>(this->parent());
    p->qt_add_entry(obj->text());
}
