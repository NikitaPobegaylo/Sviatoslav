#ifndef COUNTABLEGOODSMODEL_H
#define COUNTABLEGOODSMODEL_H


#include <QAbstractTableModel>
#include <QList>
#include "CountableGoods.h"
#include "GoodsModel.h"


class CountableGoodsModel : public GoodsModel
{
    Q_OBJECT

private:
    bool fGoodsCountReadOnly = false;

protected:
    static const int COLUMN_COUNT = GoodsModel::COLUMN_COUNT + 2;

public:
    static const int COL_NUM_GOODS_COUNT = GoodsModel::COLUMN_COUNT;
    static const int COL_NUM_TOTAL_PRICE = GoodsModel::COLUMN_COUNT + 1;

    static const QString COL_TITLE_GOODS_COUNT;
    static const QString COL_TITLE_TOTAL_PRICE;

    explicit CountableGoodsModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool isGoodsCountReadOnly() const;

public slots:
    void setGoods(QList<CountableGoods *> newGoods);

    void setGoodsCountReadOnly(const bool &value);
};


#endif // COUNTABLEGOODSMODEL_H
