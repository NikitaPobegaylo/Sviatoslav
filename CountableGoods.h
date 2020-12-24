#ifndef COUNTABLEGOODS_H
#define COUNTABLEGOODS_H


#include "Goods.h"


class CountableGoods : public Goods
{
    Q_OBJECT

private:
    uint fCount = 0;
    double fTotalPrice = 0.0;

public:
    explicit CountableGoods(QObject *parent = nullptr);

    uint count() const;
    double totalPrice() const;

public slots:
    void setPrice(const double &newPrice);
    void setCount(const uint &newCount);
    void setTotalPrice(const double &newTotalPrice);
};


#endif // COUNTABLEGOODS_H
