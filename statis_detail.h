#ifndef STATIS_DETAIL_H
#define STATIS_DETAIL_H
#include <QAbstractTableModel>
#include <QVector>
#include <QMap>
#include <QStringList>

extern "C"{
#include "stype.h"
}


class Statis_Detail:public QAbstractTableModel
{
public:
    explicit Statis_Detail(QObject *parent = 0 );
    virtual int rowCount(const QModelIndex &parent= QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent= QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
//signals:
//public slots:
private:
    QVector<short> cost_label;
    QMap<short,QString> cost_label_map;
    QStringList percent;
    QStringList value;
    QStringList header;
    ledger_entry entry;
    void populateModel();
};

#endif // STATIS_DETAIL_H
