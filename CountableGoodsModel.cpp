#include "CountableGoodsModel.h"
#include <QDebug>


const QString CountableGoodsModel::COL_TITLE_GOODS_COUNT = QObject::tr("Количество");
const QString CountableGoodsModel::COL_TITLE_TOTAL_PRICE = QObject::tr("Общая стоимость");


CountableGoodsModel::CountableGoodsModel(QObject *parent)
    : GoodsModel(parent)
{}


QVariant CountableGoodsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if ((orientation == Qt::Horizontal) && (section >= GoodsModel::COLUMN_COUNT))
    {
        switch (section) {
        case COL_NUM_GOODS_COUNT:
            return COL_TITLE_GOODS_COUNT;
            break;
        case COL_NUM_TOTAL_PRICE:
            return COL_TITLE_TOTAL_PRICE;
            break;
        default:
            return QVariant();
            break;
        }
    }
    else
        return GoodsModel::headerData(section, orientation, role);
}


int CountableGoodsModel::rowCount(const QModelIndex &parent) const
{
    return GoodsModel::rowCount(parent);
}


int CountableGoodsModel::columnCount(const QModelIndex &) const
{
    return COLUMN_COUNT;
}


QVariant CountableGoodsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (((role == Qt::DisplayRole) || (role == Qt::EditRole)) && (index.column() >= GoodsModel::COLUMN_COUNT))
    {
        switch (index.column()) {
        case COL_NUM_GOODS_COUNT:
            return qobject_cast<CountableGoods*>(fGoods.at(index.row()))->count();
            break;
        case COL_NUM_TOTAL_PRICE:
            return qobject_cast<CountableGoods*>(fGoods.at(index.row()))->totalPrice();
            break;
        default:
            return QVariant();
            break;
        }
    }
    else
        return GoodsModel::data(index, role);
}

bool CountableGoodsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (index.column() < GoodsModel::COLUMN_COUNT)
            return GoodsModel::setData(index, value, role);

        CountableGoods *item = qobject_cast<CountableGoods*>(fGoods[index.row()]);
        switch (index.column()) {
        case COL_NUM_GOODS_COUNT:
            item->setCount(value.toInt());
            break;
        case COL_NUM_TOTAL_PRICE:
            item->setTotalPrice(value.toDouble());
            break;
        default:
            return false;
        }

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}


Qt::ItemFlags CountableGoodsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if (index.column() < GoodsModel::COLUMN_COUNT)
        return GoodsModel::flags(index);
    else {
        Qt::ItemFlags flg = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

        switch (index.column()) {
        case COL_NUM_PRICE:
            if (!isPriceReadOnly())
                flg |= Qt::ItemIsEditable;
            break;
        case COL_NUM_GOODS_COUNT:
            if (!isGoodsCountReadOnly())
                flg |= Qt::ItemIsEditable;
            break;
        default:
            flg |= Qt::ItemIsEditable;
            break;
        }

        return flg;
    }
}


bool CountableGoodsModel::isGoodsCountReadOnly() const
{
    return fGoodsCountReadOnly;
}


void CountableGoodsModel::setGoods(QList<CountableGoods *> newGoods)
{
    QList<Goods*> baseGoods;
    foreach (Goods* g, newGoods) {
        baseGoods.append(g);
    }
    GoodsModel::setGoods(baseGoods);
}


void CountableGoodsModel::setGoodsCountReadOnly(const bool &value)
{
    fGoodsCountReadOnly = value;
}
