#include "statis_detail.h"

Statis_Detail::Statis_Detail(QObject *parent):QAbstractTableModel(parent)
{
    cost_label_map[1] = tr("Pet");
    cost_label_map[2] = tr("Food");
    cost_label_map[3] = tr("Dressing");
    cost_label_map[4] = tr("General Expenditure");
    cost_label_map[5] = tr("Transportation");
    cost_label_map[6] = tr("Daily Necessity");
    cost_label_map[7] = tr("Digital");
    cost_label_map[8] = tr("Cellphone");
    cost_label_map[9] = tr("Housing");
    cost_label_map[10] = tr("Education");
    cost_label_map[11] = tr("Medical");
    cost_label_map[12] = tr("Entertainment");
    populateModel();
}

void Statis_Detail::populateModel()
{
    header<<tr("Cost Label")<<tr("Percentage")<<tr("Value");
    cost_label<< 1 << 2 << 10 <<12;
    percent << tr("10.0%") <<tr("%20.0")<<tr("%35.5") <<tr("%35.5");
    value << tr("13") <<tr("12") <<tr("2000") <<tr("22");
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


