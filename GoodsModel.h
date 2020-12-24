#ifndef GOODSMODEL_H
#define GOODSMODEL_H


#include <QAbstractTableModel>
#include "Goods.h"
#include <QList>


class GoodsModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    bool fNameReadOnly = false;
    bool fPriceReadOnly = false;
    bool fBarcodesReadOnly = false;

protected:
    static const int COLUMN_COUNT = 3;

    QList<Goods*> fGoods;

public:
    explicit GoodsModel(QObject *parent = nullptr);

    static const QString COL_TITLE_GOOD_NAME;
    static const QString COL_TITLE_PRICE;
    static const QString COL_TITLE_BAR_CODES;

    static const int COL_NUM_NAME = 0;
    static const int COL_NUM_PRICE = 1;
    static const int COL_NUM_BAR_CODES = 2;

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QList<Goods *> goods();

    bool isNameReadOnly() const;
    bool isPriceReadOnly() const;
    bool isBarcodesReadOnly() const;

public slots:
    void setGoods(QList<Goods *> newGoods);
    void addGoods(Goods *newGoods);

    void setNameReadOnly(const bool &value);
    void setPriceReadOnly(const bool &value);
    void setBarcodesReadOnly(const bool &value);
};


#endif // GOODSMODEL_H
