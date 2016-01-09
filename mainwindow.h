#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <category.h>
#include "statis_detail.h"
#include <QApplication>
#include <QTableView>
#include <QPair>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>
#include <QGridLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void qt_add_entry(QString name);
    void save2file(char *fn);
    void show_chart();
    void update_statistics();
    ~MainWindow();

private slots:
    void on_addAccount_clicked();

    void on_today_detail_clicked();

    void commit();

    void show_in_out();

private:
    Ui::MainWindow *ui;
    category *cat;
    QTableView *view;
    Statis_Detail *statis;
    QVector<QPair<QLabel*, QLineEdit*> > entrys;
    QVector<QLine*> lines;

    void setupModel();
    void setupViews();

    QAbstractItemModel *model;
    QAbstractItemView *pieChart;
    QItemSelectionModel *selectionModel;
    QGridLayout *mainLayout;

};

#endif // MAINWINDOW_H
