#include "ui_mainwindow.h"
#include "category.h"
#include "mainwindow.h"
#include "statis_detail.h"
#include <QTextEdit>
#include <QDockWidget>
#include <QSplitter>
#include <QPushButton>
#include <QLabel>
#include <QTableView>


extern "C" {
#include "file_client.h"
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statis = new Statis_Detail();
    view = new QTableView();
    view->setModel(statis);
    view->setWindowTitle(QObject::tr("Details"));
    view->resize(400,400);

    ui->formLayout->setLabelAlignment(Qt::AlignLeft);

    connect(ui->commit, SIGNAL(clicked(bool)), this, SLOT(commit()));

    pthread_mutex_init(&send_lock, NULL);
    pthread_mutex_init(&recv_lock, NULL);

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
    cat = new category(this, Qt::Tool);
    cat->show();
    return;
}

void MainWindow::on_today_detail_clicked()
{
    view->show();
}


void MainWindow::qt_add_entry(QString name) {
    lines.push_back(new QLine());
    entrys.push_back(qMakePair(new QLabel(name), new QLineEdit(tr("0"))));
    ui->formLayout->addRow(entrys.back().first, entrys.back().second);
    return;
}


void MainWindow::save2file(char *fn) {
    int i = 0, num_row = ui->formLayout->rowCount();
    char *fn1 = "/Users/huangli/Documents/Tongji/spring_junior/LinuxProgramming/accounting_proj/tmp.txt";
    QLabel *label = NULL;
    QLineEdit *widget = NULL;
    ledger_entry entry;

    entry.size = 0;
    entry.t = 0;
    entry.total = 0;
    entry.labels = NULL;
    entry.values = NULL;

    for(i = 0; i < num_row; ++i) {
        widget = qobject_cast<QLineEdit*>(ui->formLayout->itemAt(i*2+1)->widget());
        label = qobject_cast<QLabel*>(ui->formLayout->itemAt(i*2)->widget());
        add_entry(&entry, label->text().toLatin1().data(), widget->text().toDouble());
    }

    save_entry(fn1, &entry);

    return;
}


void MainWindow::commit() {
    int port = 22222;
    char *ip = "0.0.0.0";
    char *fn1 = "/Users/huangli/Documents/Tongji/spring_junior/LinuxProgramming/accounting_proj/tmp.txt";
    char *fn2 = "/Users/huangli/Documents/Tongji/spring_junior/LinuxProgramming/accounting_proj/ledger.txt";

    save2file(fn1);

    fupdate(ip, port, fn1);
    fsynchronize(ip, port, fn2);

    return;
}
