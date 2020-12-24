#include "ShopInfoStorage.h"


ShopInfoStorage *ShopInfoStorage::currentStorage = nullptr;


void ShopInfoStorage::setLastError(const QString &newLastError)
{
    fLastError = newLastError;
}


void ShopInfoStorage::clearLastError()
{
    fLastError = QString();
}


ShopInfoStorage::ShopInfoStorage(QObject *parent) : QObject(parent)
{}


QString ShopInfoStorage::lastError() const
{
    return fLastError;
}


GoodsDocument *ShopInfoStorage::createNewDocument(const GoodsDocumentType &docType, QObject *parent)
{
    switch (docType) {
    case Income:
        return new GoodsIncomeDoc(parent);
    default:
        GoodsDocument* doc = new GoodsDocument(parent);
        doc->setDocumentType(docType);
        return doc;
    }
}


void ShopInfoStorage::saveGoods(const QList<Goods *> goodsToSave)
{
    clearLastError();

    foreach (Goods* g, goodsToSave) {
        saveGoods(g);
        if (!lastError().isNull())
            return;
    }
}
