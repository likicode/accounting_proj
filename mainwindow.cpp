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


int random_int() {
    int output = 0 + (rand() % 16777216);
    return output;
}


void MainWindow::show_chart() {
    QString fileName = "./ledger.txt";
    QFile file(fileName);

    if(!file.exists() || !file.open(QFile::ReadOnly | QFile::Text)) {
        return;
    }
    printf("a\n");

    QTextStream stream(&file);
    QString line;

    model->removeRows(0, model->rowCount(QModelIndex()), QModelIndex());

    int row = 0;
    double total = 0;
    line = stream.readLine();
    total = stream.readLine().toDouble();
    line = stream.readLine();
    do {
        line = stream.readLine();
        if (!line.isEmpty()) {
            model->insertRows(row, 1, QModelIndex());

            QStringList pieces = line.split(",", QString::SkipEmptyParts);
            model->setData(model->index(row, 0, QModelIndex()),
                           pieces.value(0));
            model->setData(model->index(row, 1, QModelIndex()),
                           QString::number(pieces.value(1).toDouble()/total));
            model->setData(model->index(row, 0, QModelIndex()),
                           QColor(random_int()), Qt::DecorationRole);
            row++;
        }
    } while (!line.isEmpty());

    file.close();

    return;
}
