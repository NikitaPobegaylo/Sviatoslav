#include "Goods.h"


Goods::Goods(QObject *parent) : QObject(parent)
{
}


QString Goods::name() const
{
    return fName;
}


double Goods::price() const
{
    return fPrice;
}


QStringList Goods::barCodes() const
{
    return fBarCodes;
}


int Goods::id() const
{
    return fID;
}


void Goods::setId(const int &newId)
{
    fID = newId;
}


void Goods::setName(const QString &newName)
{
    fName = newName;
}


void Goods::setPrice(const double &newPrice)
{
    fPrice = newPrice;
    emit priceChanged();
}


void Goods::addBarCode(const QString &newBarCode)
{
    fBarCodes.append(newBarCode);
}


void Goods::addBarCode(const QStringList &newBarCodes)
{
    fBarCodes.append(newBarCodes);
}


void Goods::removeBarCode(const QString &delBarCode)
{
    fBarCodes.removeAll(delBarCode);
}


void Goods::clearBarCodes()
{
    fBarCodes.clear();
}
