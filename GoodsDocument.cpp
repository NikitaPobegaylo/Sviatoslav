#include "GoodsDocument.h"


GoodsDocument::GoodsDocument(QObject *parent) : QObject(parent)
{
    fID = -1;
}


int GoodsDocument::id() const
{
    return fID;
}


GoodsDocumentType GoodsDocument::documentType() const
{
    return fDocumentType;
}


GoodsDocumentStatus GoodsDocument::status() const
{
    return fStatus;
}


QDateTime GoodsDocument::createDate() const
{
    return fCreateDate;
}


QDateTime GoodsDocument::applyDate() const
{
    return fApplyDate;
}


QList<CountableGoods *> GoodsDocument::goods() const
{
    return fGoods;
}


double GoodsDocument::price() const
{
    double totalPrice = 0.0;
    foreach (CountableGoods *g, goods())
        totalPrice += g->totalPrice();
    return totalPrice;
}


void GoodsDocument::setID(const int &newID)
{
    fID = newID;
}


void GoodsDocument::setDocumentType(const GoodsDocumentType &newDocType)
{
    fDocumentType = newDocType;
}


void GoodsDocument::setStatus(const GoodsDocumentStatus &newStatus)
{
    fStatus = newStatus;
}


void GoodsDocument::setCreateDate(const QDateTime &newCreateDate)
{
    fCreateDate = newCreateDate;
}


void GoodsDocument::setApplyDate(const QDateTime &newApplyDate)
{
    fApplyDate = newApplyDate;
}


void GoodsDocument::addGoods(CountableGoods * const &itm)
{
    fGoods.append(itm);
}


void GoodsDocument::addGoods(const QList<CountableGoods *> &newGoods)
{
    fGoods.append(newGoods);
}


void GoodsDocument::removeGoods(CountableGoods * const &itm)
{
    fGoods.removeAll(itm);
}


void GoodsDocument::clearGoods()
{
    fGoods.clear();
}
