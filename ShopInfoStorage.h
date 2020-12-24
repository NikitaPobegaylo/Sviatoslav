#ifndef SHOPINFOSTORAGE_H
#define SHOPINFOSTORAGE_H


#include <QObject>
#include <QList>
#include <QStringList>
#include "CountableGoods.h"
#include "GoodsIncomeDoc.h"


class ShopInfoStorage : public QObject
{
    Q_OBJECT

private:
    QString fLastError;

protected:
    void setLastError(const QString &newLastError);
    void clearLastError();

public:
    explicit ShopInfoStorage(QObject *parent = nullptr);

    static ShopInfoStorage* currentStorage;

    QString lastError() const;
    virtual QList<GoodsDocument *> getDocuments(const GoodsDocumentType &docType, QObject *parent = nullptr) = 0;
    virtual QList<CountableGoods *> getWarehouse(QObject *parent = nullptr) = 0;
    virtual QStringList getGoodsBarcodes(const int &goodsID) = 0;
    virtual bool goodsExist(const int &goodsID) = 0;
    virtual bool documentExists(const int &docID) = 0;
    virtual bool isDocumentApplied(const int &docID) = 0;
    virtual int findGoodsIDByName(const QString &goodsName) = 0;
    virtual int getWarehouseGoodsCount(const int &goodsID) = 0;
    virtual GoodsDocument *createNewDocument(const GoodsDocumentType &docType, QObject *parent = nullptr);
    virtual double getMoneyIncome(const QDateTime &dateStart, const QDateTime &dateEnd) = 0;
    virtual double getMoneyOutcome(const QDateTime &dateStart, const QDateTime &dateEnd) = 0;

public slots:
    virtual void saveDocument(GoodsDocument * doc) = 0;
    virtual void applyDocument(GoodsDocument *doc) = 0;
    virtual void deleteDocument(const int &docID) = 0;
    virtual void saveGoods(const QList<Goods*> goodsToSave);
    virtual void saveGoods(Goods* goodsToSave) = 0;
    virtual void saveGoodsBarCodes(const int &goodsID, const QStringList &barCodes) = 0;
    virtual int saveProvider(const QString &providerName) = 0;
    virtual void addGoodsToWarehouse(const int &goodsID, const int &goodsCount) = 0;
    virtual void setGoodsPrice(const int &goodsID, const double &goodsPrice) = 0;
};


#endif // SHOPINFOSTORAGE_H
