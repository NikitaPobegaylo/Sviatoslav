#ifndef GOODSDOCUMENTMODEL_H
#define GOODSDOCUMENTMODEL_H


#include <QAbstractTableModel>
#include <QList>
#include "GoodsDocument.h"


class GoodsDocumentModel : public QAbstractTableModel
{
    Q_OBJECT

protected:
    static const int COLUMN_COUNT = 6;

    QList<GoodsDocument *> fDocuments;

public:
    static const int COL_NUM_ID = 0;
    static const int COL_NUM_STATUS = 1;
    static const int COL_NUM_GOODS_COUNT = 2;
    static const int COL_NUM_TOTAL_PRICE = 3;
    static const int COL_NUM_DATE_CREATE = 4;
    static const int COL_NUM_DATE_APPLY = 5;

    static const QString COL_TITLE_ID;
    static const QString COL_TITLE_GOODS_COUNT;
    static const QString COL_TITLE_TOTAL_PRICE;
    static const QString COL_TITLE_STATUS;
    static const QString COL_TITLE_DATE_CREATE;
    static const QString COL_TITLE_DATE_APPLY;

    explicit GoodsDocumentModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QList<GoodsDocument *> documents() const;
    void setDocuments(const QList<GoodsDocument *> &newDocuments);
};


#endif // GOODSDOCUMENTMODEL_H
