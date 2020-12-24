#include "GoodsModel.h"
#include <QStringList>
#include <QRegExp>
#include <QDebug>


const QString GoodsModel::COL_TITLE_GOOD_NAME = QObject::tr("Наименование");
const QString GoodsModel::COL_TITLE_PRICE = QObject::tr("Стоимость за ед.");
const QString GoodsModel::COL_TITLE_BAR_CODES = QObject::tr("Штрихкоды");


GoodsModel::GoodsModel(QObject *parent)
    : QAbstractTableModel(parent)
{}


QVariant GoodsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Vertical)
            return section + 1;
        else {
            switch (section) {
            case COL_NUM_NAME:
                return COL_TITLE_GOOD_NAME;
                break;
            case COL_NUM_PRICE:
                return COL_TITLE_PRICE;
                break;
            case COL_NUM_BAR_CODES:
                return COL_TITLE_BAR_CODES;
                break;
            default:
                return QVariant();
                break;
            }
        }
    } else
        return QVariant();
}


int GoodsModel::rowCount(const QModelIndex &) const
{
    return fGoods.size();
}


int GoodsModel::columnCount(const QModelIndex &) const
{
    return COLUMN_COUNT;
}


QVariant GoodsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || ((role != Qt::DisplayRole) && (role != Qt::EditRole)))
        return QVariant();

    Goods *item = fGoods.at(index.row());
    switch (index.column()) {
    case COL_NUM_NAME:
        return item->name();
        break;
    case COL_NUM_PRICE:
        return item->price();
        break;
    case COL_NUM_BAR_CODES:
        return item->barCodes().join(", ");
        break;
    default:
        return QVariant();
        break;
    }
}


bool GoodsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        Goods *item = fGoods[index.row()];
        QRegExp splitRegExp("[^0-9a-zA-Z]+");
        switch (index.column()) {
        case COL_NUM_NAME:
            item->setName(value.toString());
            break;
        case COL_NUM_BAR_CODES:
            item->clearBarCodes();
            item->addBarCode(value.toString().trimmed().split(splitRegExp, QString::SkipEmptyParts));
            break;
        case COL_NUM_PRICE:
            item->setPrice(value.toDouble());
            break;
        default:
            return false;
        }

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}


Qt::ItemFlags GoodsModel::flags(const QModelIndex &index) const
{
    if (index.isValid()) {
        Qt::ItemFlags flg = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        switch (index.column()) {
        case COL_NUM_NAME:
            if (!isNameReadOnly())
                flg |= Qt::ItemIsEditable;
            break;
        case COL_NUM_BAR_CODES:
            if (!isBarcodesReadOnly())
                flg |= Qt::ItemIsEditable;
            break;
        case COL_NUM_PRICE:
            if (!isPriceReadOnly())
                flg |= Qt::ItemIsEditable;
            break;
        default:
            break;
        }
        return flg;
    } else
        return Qt::NoItemFlags;
}


QList<Goods *> GoodsModel::goods()
{
    return fGoods;
}


bool GoodsModel::isNameReadOnly() const
{
    return fNameReadOnly;
}


bool GoodsModel::isPriceReadOnly() const
{
    return fPriceReadOnly;
}


bool GoodsModel::isBarcodesReadOnly() const
{
    return fBarcodesReadOnly;
}


void GoodsModel::setGoods(QList<Goods*> newGoods)
{
    fGoods = newGoods;
}


void GoodsModel::addGoods(Goods *newGoods)
{
    beginInsertRows(QModelIndex(), fGoods.size(), fGoods.size());
    fGoods.append(newGoods);
    endInsertRows();
}


void GoodsModel::setNameReadOnly(const bool &value)
{
    fNameReadOnly = value;
}


void GoodsModel::setPriceReadOnly(const bool &value)
{
    fPriceReadOnly = value;
}


void GoodsModel::setBarcodesReadOnly(const bool &value)
{
    fBarcodesReadOnly = value;
}
