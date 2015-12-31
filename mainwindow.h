#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <category.h>
#include "statis_detail.h"
#include <QApplication>
#include <QTableView>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_addAccount_clicked();

    void on_today_detail_clicked();

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
