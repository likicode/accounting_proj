#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "category.h"
#include <QTextEdit>
#include <QDockWidget>
#include <QSplitter>
#include <QPushButton>
#include <QLabel>
#include "statis_detail.h"
#include <QTableView>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setStyleSheet("background-color: white;");
  /*  QPixmap bkgnd(":/images/back1.gif");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);*/


}

MainWindow::~MainWindow()
{
    delete ui;
}

//点击add按钮，会弹出选择类别的对话框
void MainWindow::on_addAccount_clicked()
{
    category *cat = new category;
    cat->show();
    return;
}

void MainWindow::on_today_detail_clicked()
{
    //我是一条有奇怪问题的分割线/////////////////////////////////
    //不知为何突然闪退，但是如果把这段代码加到main.cpp里面就能正常显示
    Statis_Detail statis;
    QTableView view;
    view.setModel(&statis);
    view.setWindowTitle(QObject::tr("Details"));
    view.resize(400,400);
    view.show();
}
