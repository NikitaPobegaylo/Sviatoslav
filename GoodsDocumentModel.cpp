#include "GoodsDocumentModel.h"


const QString GoodsDocumentModel::COL_TITLE_ID = QObject::tr("Идентификатор");
const QString GoodsDocumentModel::COL_TITLE_GOODS_COUNT = QObject::tr("Кол-во наименований");
const QString GoodsDocumentModel::COL_TITLE_STATUS = QObject::tr("Статус");
const QString GoodsDocumentModel::COL_TITLE_DATE_CREATE = QObject::tr("Дата создания");
const QString GoodsDocumentModel::COL_TITLE_DATE_APPLY = QObject::tr("Дата применения");
const QString GoodsDocumentModel::COL_TITLE_TOTAL_PRICE = QObject::tr("Итоговая стоимость");


GoodsDocumentModel::GoodsDocumentModel(QObject *parent)
    : QAbstractTableModel(parent)
{}


QVariant GoodsDocumentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Vertical)
            return section + 1;
        else {
            switch (section) {
            case COL_NUM_ID:
                return COL_TITLE_ID;
                break;
            case COL_NUM_STATUS:
                return COL_TITLE_STATUS;
                break;
            case COL_NUM_TOTAL_PRICE:
                return COL_TITLE_TOTAL_PRICE;
                break;
            case COL_NUM_GOODS_COUNT:
                return COL_TITLE_GOODS_COUNT;
                break;
            case COL_NUM_DATE_CREATE:
                return COL_TITLE_DATE_CREATE;
                break;
            case COL_NUM_DATE_APPLY:
                return COL_TITLE_DATE_APPLY;
                break;
            default:
                return QVariant();
                break;
            }
        }
    } else
        return QVariant();
}


int GoodsDocumentModel::rowCount(const QModelIndex &) const
{
    return fDocuments.size();
}


int GoodsDocumentModel::columnCount(const QModelIndex &) const
{
    return COLUMN_COUNT;
}


QVariant GoodsDocumentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || ((role != Qt::DisplayRole) && (role != Qt::EditRole)))
        return QVariant();

    GoodsDocument *doc = fDocuments.at(index.row());
    switch (index.column()) {
    case COL_NUM_ID:
        return doc->id();
        break;
    case COL_NUM_GOODS_COUNT:
        return doc->goods().size();
        break;
    case COL_NUM_STATUS:
        switch (doc->status()) {
        case Editing:
            return QObject::tr("Правка");
            break;
        case Applied:
            return QObject::tr("Применен");
            break;
        default:
            return QObject::tr("НЕИЗВЕСТНО");
            break;
        }
        break;
    case COL_NUM_TOTAL_PRICE:
        return doc->price();
    case COL_NUM_DATE_CREATE:
        return doc->createDate();
        break;
    case COL_NUM_DATE_APPLY:
        return doc->applyDate();
        break;
    default:
        return QVariant();
        break;
    }
}


QList<GoodsDocument *> GoodsDocumentModel::documents() const
{
    return fDocuments;
}


void GoodsDocumentModel::setDocuments(const QList<GoodsDocument *> &newDocuments)
{
    fDocuments = newDocuments;
}
