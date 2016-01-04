#include "statis_detail.h"


extern "C"{
#include "stype.h"
}


Statis_Detail::Statis_Detail(QObject *parent):QAbstractTableModel(parent)
{
    int i = 0;
    char *fn2 = "/Users/huangli/Documents/Tongji/spring_junior/LinuxProgramming/accounting_proj/ledger.txt";

    parse_entry(fn2, &(this->entry));

    for(i = 0; i < entry.size; ++i) {
        cost_label_map[i] = tr(entry.labels[i]);
    }

    populateModel();
}

void Statis_Detail::populateModel()
{
    int i = 0;
    header<<tr("Cost Label")<<tr("Percentage")<<tr("Value");
    /*
    cost_label<< 1 << 2 << 10 <<12;
    percent << tr("10.0%") <<tr("%20.0")<<tr("%35.5") <<tr("%35.5");
    value << tr("13") <<tr("12") <<tr("2000") <<tr("22");
    */

    for(i = 0; i < entry.size; ++i) {
        cost_label << i;
        percent << QString::number(entry.values[i] / entry.total)+tr("%");
        value << QString::number(entry.values[i]);
    }
}

//模型的列数
int Statis_Detail::columnCount(const QModelIndex &parent) const
{
    return  3;
}
//模型的行数
int Statis_Detail::rowCount(const QModelIndex &parent) const
{
    return cost_label.size();
}

QVariant Statis_Detail::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(role == Qt::DisplayRole){
        switch(index.column()){
            case 0:
                return cost_label_map[cost_label[index.row()]];
                break;
            case 1:
                return percent[index.row()];
                break;
            case 2:
                return value[index.row()];
                break;
            default:
                return QVariant();

        }
    }
    return QVariant();
}

QVariant Statis_Detail::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole&&orientation == Qt::Horizontal){
        return header[section];
    }
    return QAbstractTableModel::headerData(section,orientation,role);
}


