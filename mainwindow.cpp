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
#include <QFile>
#include <QtWidgets>
#include <QGridLayout>
#include "pieview.h"

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


    setLayout(mainLayout);


    //export
    //connect(ui->today_detail, SIGNAL(clicked(bool)), this, SLOT(showDetail()));
    setupTableView();

    connect(ui->commit, SIGNAL(clicked(bool)), this, SLOT(commit()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(show_in_out()));

    pthread_mutex_init(&send_lock, NULL);
    pthread_mutex_init(&recv_lock, NULL);

    //this->setStyleSheet("background-color: white;");
  /*  QPixmap bkgnd(":/images/back1.gif");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);*/

    setupModel();
    setupViews();

    show_chart();
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
    //view->show();
    setupTableView();
}


void MainWindow::qt_add_entry(QString name) {
    lines.push_back(new QLine());
    entrys.push_back(qMakePair(new QLabel(name), new QLineEdit(tr("0"))));
    ui->formLayout->addRow(entrys.back().first, entrys.back().second);
    return;
}


void MainWindow::save2file(char *fn) {
    int i = 0, num_row = ui->formLayout->rowCount();
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

    save_entry(fn, &entry);

    return;
}


void MainWindow::commit() {
    int port = 22222;
    char *ip = "107.170.242.23";
    char *fn1 = "./tmp.txt";
    char *fn2 = "./ledger.txt";

    save2file(fn1);

    fupdate(ip, port, fn1);
    fsynchronize(ip, port, fn2);
    show_chart();

    return;
}


void MainWindow::setupModel()
{
    model = new QStandardItemModel(0, 2, this);
    model->setHeaderData(0, Qt::Horizontal, tr("Label"));
    model->setHeaderData(1, Qt::Horizontal, tr("proportion"));
}

void MainWindow::setupViews()
{
    QSplitter *splitter = new QSplitter(this);
    QTableView *table = new QTableView(this);
    pieChart = new PieView(ui->frame);
    splitter->addWidget(table);
    splitter->addWidget(pieChart);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    table->setModel(model);
    pieChart->setModel(model);

    QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
    table->setSelectionModel(selectionModel);
    pieChart->setSelectionModel(selectionModel);

    QHeaderView *headerView = table->horizontalHeader();
    headerView->setStretchLastSection(true);

    // setCentralWidget(splitter);

    QVBoxLayout *nl = new QVBoxLayout;
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,2);
    nl->addWidget(splitter);
    ui->frame->setLayout(nl);
}

void MainWindow::setupTableView()
{
    statis = new Statis_Detail();
    QStandardItemModel *model = new QStandardItemModel();
    ledger_entry entry;
    QMap<short,QString> cost_label_map;
    cost_label_map = statis->getMap();
    entry  = statis->getEntry();
    for(int i = 0; i < entry.size; ++i) {
        QString labelName = cost_label_map[i];
        QStandardItem *Label = new QStandardItem(labelName);
        QStandardItem *Value = new QStandardItem(QString::number(entry.values[i]));
        QStandardItem *Percent = new QStandardItem(QString::number(100*entry.values[i] / entry.total,'f',2)+tr("%"));
        model->setItem(i,0,Label);
        model->setItem(i,1,Value);
        model->setItem(i,2,Percent);
    }

    model->setColumnCount(3);
    model->setRowCount(statis->rowCount());
    model->setHeaderData(0,Qt::Horizontal,"Cost Label");
    model->setHeaderData(2,Qt::Horizontal,"Percent");
    model->setHeaderData(1,Qt::Horizontal,"Value");
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,80);
    ui->tableView->setColumnWidth(1,60);
    ui->tableView->setColumnWidth(2,60);
    ui->tableView->horizontalHeader()->setStyleSheet("");
}

int random_int(int row, int size) {
    int mid = (row+1.0)/(2*size)*RAND_MAX;
    int output = rand() % 16777216;
    return output;
}


void MainWindow::show_in_out() {
    show_chart();

    return;
}


void MainWindow::show_chart() {
    char* fileName = "./ledger.txt";
    ledger_entry entry;
    if (parse_entry(fileName, &entry) == -1 ) {
        return;
    }

    model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());

    int i = 0, row = 0;
    double in_value = 0;
    double out_value = 0;
    int idx = ui->comboBox->currentIndex();
    for (i = 0; i < entry.size; ++i) {
        if (idx == 0 && entry.values[i] >= 0) {
            model->insertRows(row, 1, QModelIndex());
            model->setData(model->index(row, 0, QModelIndex()),
                           QVariant(entry.labels[i]));
            model->setData(model->index(row, 1, QModelIndex()),
                           QString::number(entry.values[i]/entry.total));
            model->setData(model->index(row, 0, QModelIndex()),
                           QColor(random_int(i, entry.size)), Qt::DecorationRole);
            in_value += entry.values[i];
            ++row;
        } else if (idx == 1 && entry.values[i] <= 0) {
            model->insertRows(row, 1, QModelIndex());
            model->setData(model->index(row, 0, QModelIndex()),
                           QVariant(entry.labels[i]));
            model->setData(model->index(row, 1, QModelIndex()),
                           QString::number(-entry.values[i]/entry.total));
            model->setData(model->index(row, 0, QModelIndex()),
                           QColor(random_int(i, entry.size)), Qt::DecorationRole);
            out_value -= entry.values[i];
            ++row;
        }
    }

    ui->inValue->setText(QString::number(in_value));
    ui->outValue->setText(QString::number((out_value)));

    return;
}


void MainWindow::update_statistics() {
    ;

    return;
}
