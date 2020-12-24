#include "CountableGoods.h"


CountableGoods::CountableGoods(QObject *parent) : Goods(parent)
{
}


uint CountableGoods::count() const
{
    return fCount;
}


double CountableGoods::totalPrice() const
{
    return fTotalPrice;
}


void CountableGoods::setPrice(const double &newPrice)
{
    Goods::setPrice(newPrice);
    fTotalPrice = count() * price();
}


void CountableGoods::setCount(const uint &newCount)
{
    fCount = newCount;
    fTotalPrice = count() * price();
}


void CountableGoods::setTotalPrice(const double &newTotalPrice)
{
    fTotalPrice = newTotalPrice;
    int itemCount = count();
    if (itemCount > 0)
        setPrice(totalPrice() / (double)itemCount);
    else
        setPrice(0.0);
}
