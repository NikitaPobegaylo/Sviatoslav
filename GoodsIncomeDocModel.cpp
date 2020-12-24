#include "GoodsIncomeDocModel.h"


const QString GoodsIncomeDocModel::COL_TITLE_PROVIDER_NAME = QObject::tr("Поставщик");


GoodsIncomeDocModel::GoodsIncomeDocModel(QObject *parent)
    : GoodsDocumentModel(parent)
{}


QVariant GoodsIncomeDocModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if ((orientation == Qt::Horizontal) && (section >= GoodsDocumentModel::COLUMN_COUNT))
    {
        switch (section) {
        case COL_NUM_PROVIDER_NAME:
            return COL_TITLE_PROVIDER_NAME;
            break;
        default:
            return QVariant();
            break;
        }
    }
    else
        return GoodsDocumentModel::headerData(section, orientation, role);
}


int GoodsIncomeDocModel::rowCount(const QModelIndex &parent) const
{
    return GoodsDocumentModel::rowCount(parent);
}


int GoodsIncomeDocModel::columnCount(const QModelIndex &) const
{
    return COLUMN_COUNT;
}


QVariant GoodsIncomeDocModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if ((role == Qt::DisplayRole) && (index.column() >= GoodsDocumentModel::COLUMN_COUNT))
    {
        switch (index.column()) {
        case COL_NUM_PROVIDER_NAME:
            return qobject_cast<GoodsIncomeDoc*>(fDocuments.at(index.row()))->providerName();
            break;
        default:
            return QVariant();
            break;
        }
    }
    else
        return GoodsDocumentModel::data(index, role);
}


void GoodsIncomeDocModel::setDocuments(const QList<GoodsIncomeDoc *> &newDocuments)
{
    QList<GoodsDocument *> baseDocs;
    foreach (GoodsDocument* doc, newDocuments) {
        baseDocs.append(doc);
    }
    GoodsDocumentModel::setDocuments(baseDocs);
}
