#ifndef GOODSINCOMEDOCMODEL_H
#define GOODSINCOMEDOCMODEL_H


#include <QAbstractTableModel>
#include "GoodsIncomeDoc.h"
#include "GoodsDocumentModel.h"


class GoodsIncomeDocModel : public GoodsDocumentModel
{
    Q_OBJECT

protected:
    static const int COLUMN_COUNT = GoodsDocumentModel::COLUMN_COUNT + 1;

public:
    static const int COL_NUM_PROVIDER_NAME = GoodsDocumentModel::COLUMN_COUNT;

    static const QString COL_TITLE_PROVIDER_NAME;

    explicit GoodsIncomeDocModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setDocuments(const QList<GoodsIncomeDoc *> &newDocuments);
};


#endif // GOODSINCOMEDOCMODEL_H
