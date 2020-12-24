#ifndef SQLSHOPINFOSTORAGE_H
#define SQLSHOPINFOSTORAGE_H


#include <QObject>
#include <QSqlDatabase>
#include <QVariantList>
#include "ShopInfoStorage.h"


class SqlShopInfoStorage : public ShopInfoStorage
{
    Q_OBJECT

private:
    QSqlDatabase fDatabase;

    static const QString SQL_SEL_WAREHOUSE;
    static const QString SQL_SEL_ITEM_BARCODES;
    static const QString SQL_SEL_DOCS;
    static const QString SQL_SEL_DOC_GOODS;
    static const QString SQL_DEL_ALL_GOODS_BARCODES;
    static const QString SQL_ADD_GOODS_BARCODE;
    static const QString SQL_INS_GOODS;
    static const QString SQL_UPD_GOODS;
    static const QString SQL_DEL_DOC_GOODS;
    static const QString SQL_DEL_DOC;
    static const QString SQL_INS_DOC;
    static const QString SQL_UPD_DOC;
    static const QString SQL_INS_INCOME_DOC;
    static const QString SQL_UPD_INCOME_DOC;
    static const QString SQL_SEL_PROVIDER_ID_BY_NAME;
    static const QString SQL_INS_PROVIDER;
    static const QString SQL_SEL_GOODS_ID_BY_ID;
    static const QString SQL_INS_DOC_GOODS;
    static const QString SQL_SEL_GOODS_ID_BY_NAME;
    static const QString SQL_DEL_INCOME_DOC;
    static const QString SQL_SEL_INCOME_DOC_PROVIDER;
    static const QString SQL_SEL_DOC_STATUS;
    static const QString SQL_CHECK_INCOME_DOC_EXISTS;
    static const QString SQL_CHECK_DOC_EXISTS;
    static const QString SQL_INS_WAREHOUSE_GOODS;
    static const QString SQL_UPD_INC_WAREHOUSE_GOODS;
    static const QString SQL_SEL_WAREHOUSE_GOODS_COUNT;
    static const QString SQL_UPD_DOC_STATUS;
    static const QString SQL_UPD_APPLY_DOC;
    static const QString SQL_INS_PRICE_HIST;
    static const QString SQL_UPD_WAREHOUSE_PRICE;
    static const QString SQL_SEL_MONEY_INCOME;
    static const QString SQL_SEL_MONEY_OUTCOME;

protected:
    QList<CountableGoods *> getCountableGoodsByQuery(const QString &sqlQuery, QObject *parent = nullptr,
                                                     const QVariantList &bindValues = QVariantList());
    bool incomeDocExists(const int &docID);
    QString docTypeToString(const GoodsDocumentType &docType);
    void refreshIncomeDocumentProvider(GoodsIncomeDoc *doc);
    void applyDocumentToWarehouse(GoodsDocument *doc);
    void setDocumentStatus(const int &docID, const GoodsDocumentStatus &docStatus);
    void loadTypeSpecificDocumentInfo(GoodsDocument* doc, const GoodsDocumentType &docType);
    void saveTypeSpecificDocumentInfo(GoodsDocument *doc);

public:
    explicit SqlShopInfoStorage(QObject *parent = nullptr);

    QSqlDatabase database() const;

    QList<GoodsDocument *> getDocuments(const GoodsDocumentType &docType, QObject *parent = nullptr);
    QList<CountableGoods *> getWarehouse(QObject *parent = nullptr);
    QStringList getGoodsBarcodes(const int &goodsID);
    bool goodsExist(const int &goodsID);
    bool documentExists(const int &docID);
    bool isDocumentApplied(const int &docID);
    int findGoodsIDByName(const QString &goodsName);
    int getWarehouseGoodsCount(const int &goodsID);
    double getMoneyIncome(const QDateTime &dateStart, const QDateTime &dateEnd);
    double getMoneyOutcome(const QDateTime &dateStart, const QDateTime &dateEnd);

public slots:
    void setDatabase(const QSqlDatabase &newDatabase);

    void saveDocument(GoodsDocument * doc);
    void applyDocument(GoodsDocument *doc);
    void deleteDocument(const int &docID);
    void saveGoods(Goods* goodsToSave);
    void saveGoods(const QList<Goods*> goodsToSave);
    void saveGoodsBarCodes(const int &goodsID, const QStringList &barCodes);
    int saveProvider(const QString &providerName);
    void addGoodsToWarehouse(const int &goodsID, const int &goodsCount);
    void setGoodsPrice(const int &goodsID, const double &goodsPrice);
};


#endif // SQLSHOPINFOSTORAGE_H
