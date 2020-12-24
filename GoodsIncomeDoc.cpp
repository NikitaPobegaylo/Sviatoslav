#include "GoodsIncomeDoc.h"


GoodsIncomeDoc::GoodsIncomeDoc(QObject *parent) : GoodsDocument(parent)
{
    setDocumentType(Income);
}


QString GoodsIncomeDoc::providerName() const
{
    return fProviderName;
}


void GoodsIncomeDoc::setProviderName(const QString &newProviderName)
{
    fProviderName = newProviderName;
}
