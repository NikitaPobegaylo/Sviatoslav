#include "SqlShopInfoStorage.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>


const QString SqlShopInfoStorage::SQL_SEL_WAREHOUSE = "SELECT i.rowid, i.name, w.price, w.item_count\n"
                                  "FROM items i, warehouse_items w\n"
                                  "WHERE i.rowid = w.item_id";
const QString SqlShopInfoStorage::SQL_SEL_ITEM_BARCODES = "SELECT barcode\n"
                                  "FROM item_barcodes\n"
                                  "WHERE item_id = :item_id";
const QString SqlShopInfoStorage::SQL_SEL_DOCS = "SELECT d.rowid, d.status, d.date_create, d.date_apply\n"
                                                 "FROM docs d\n"
                                                 "WHERE d.doc_type = :doc_type";
const QString SqlShopInfoStorage::SQL_SEL_DOC_GOODS = "SELECT i. rowid, i.name, d.price, d.item_count\n"
                                                      "FROM items i, doc_items d\n"
                                                      "WHERE i. rowid = d.item_id AND d.doc_id = ?";
const QString SqlShopInfoStorage::SQL_CHECK_DOC_EXISTS = "SELECT rowid FROM docs WHERE rowid = :doc_id";
const QString SqlShopInfoStorage::SQL_DEL_ALL_GOODS_BARCODES = "DELETE FROM item_barcodes WHERE item_id = :good_id";
const QString SqlShopInfoStorage::SQL_ADD_GOODS_BARCODE = "INSERT INTO item_barcodes(item_id, barcode)\n"
                                                          "VALUES(:good_id, :barcode)";
const QString SqlShopInfoStorage::SQL_INS_GOODS = "INSERT INTO items(name) VALUES(:name)";
const QString SqlShopInfoStorage::SQL_UPD_GOODS = "UPDATE items set name = :name WHERE rowid = :good_id";
const QString SqlShopInfoStorage::SQL_DEL_DOC_GOODS = "DELETE FROM doc_items WHERE doc_id = :doc_id";
const QString SqlShopInfoStorage::SQL_INS_DOC = "INSERT INTO docs(status, doc_type, date_create, date_apply)\n"
                                                "VALUES(:status, :doc_type, :date_create, :date_apply)";
const QString SqlShopInfoStorage::SQL_UPD_DOC = "UPDATE docs SET doc_type = :doc_type,\n"
                                                "status = :status, date_create = :date_create, date_apply = :date_apply\n"
                                                "WHERE rowid = :doc_id";
const QString SqlShopInfoStorage::SQL_INS_INCOME_DOC = "INSERT INTO income_docs(doc_id, provider_id)\n"
                                                       "VALUES(:doc_id, :provider_id)";
const QString SqlShopInfoStorage::SQL_UPD_INCOME_DOC = "UPDATE income_docs SET provider_id = :provider_id\n"
                                                       "WHERE doc_id = :doc_id";
const QString SqlShopInfoStorage::SQL_SEL_PROVIDER_ID_BY_NAME = "SELECT rowid FROM providers WHERE UPPER(name) = UPPER(:name)";
const QString SqlShopInfoStorage::SQL_INS_PROVIDER = "INSERT INTO providers(name) VALUES(:name)";
const QString SqlShopInfoStorage::SQL_SEL_GOODS_ID_BY_ID = "SELECT rowid FROM items WHERE rowid = :goods_id";
const QString SqlShopInfoStorage::SQL_INS_DOC_GOODS = "INSERT INTO doc_items(doc_id, item_id, item_count, price)\n"
                                                      "VALUES(:doc_id, :good_id, :count, :price)";
const QString SqlShopInfoStorage::SQL_SEL_GOODS_ID_BY_NAME = "SELECT rowid FROM items WHERE name = :name";
const QString SqlShopInfoStorage::SQL_DEL_INCOME_DOC = "DELETE FROM income_docs WHERE doc_id = :doc_id";
const QString SqlShopInfoStorage::SQL_SEL_INCOME_DOC_PROVIDER = "SELECT p.name FROM providers p, income_docs d\n"
                                                                "WHERE p.rowid = d.provider_id AND d.doc_id = :doc_id";
const QString SqlShopInfoStorage::SQL_DEL_DOC = "DELETE FROM docs WHERE rowid = :doc_id";
const QString SqlShopInfoStorage::SQL_SEL_DOC_STATUS = "SELECT status FROM docs WHERE rowid = :doc_id";
const QString SqlShopInfoStorage::SQL_CHECK_INCOME_DOC_EXISTS = "SELECT doc_id FROM income_docs WHERE doc_id = :doc_id";
const QString SqlShopInfoStorage::SQL_INS_WAREHOUSE_GOODS = "INSERT INTO warehouse_items(item_id, item_count)\n"
                                                            "VALUES(:good_id, :good_count)";
const QString SqlShopInfoStorage::SQL_UPD_INC_WAREHOUSE_GOODS = "UPDATE warehouse_items SET item_count = item_count + :good_count\n"
                                                                "WHERE item_id = :good_id";
const QString SqlShopInfoStorage::SQL_SEL_WAREHOUSE_GOODS_COUNT = "SELECT item_count FROM warehouse_items WHERE item_id = :good_id";
const QString SqlShopInfoStorage::SQL_UPD_DOC_STATUS = "UPDATE docs SET status = :status WHERE rowid = :doc_id";
const QString SqlShopInfoStorage::SQL_UPD_APPLY_DOC = "UPDATE docs SET status = \"A\", date_apply = :apply_date WHERE rowid = :doc_id";
const QString SqlShopInfoStorage::SQL_INS_PRICE_HIST = "INSERT INTO item_price(item_id, date_start, price)\n"
                                                       "VALUES(:good_id, :date_start, :price)";
const QString SqlShopInfoStorage::SQL_UPD_WAREHOUSE_PRICE = "UPDATE warehouse_items SET price = :price WHERE item_id = :good_id";
const QString SqlShopInfoStorage::SQL_SEL_MONEY_INCOME = "SELECT SUM(i.item_count * i.price) FROM doc_items i, docs d\n"
                                                         "WHERE d.rowid = i.doc_id AND d.doc_type = \"CASH_VOUCHER\"\n"
                                                         "AND date_apply BETWEEN :date_start AND :date_end";
const QString SqlShopInfoStorage::SQL_SEL_MONEY_OUTCOME = "SELECT SUM(i.item_count * i.price) FROM doc_items i, docs d\n"
                                                         "WHERE d.rowid = i.doc_id AND d.doc_type = \"INCOME\"\n"
                                                         "AND date_apply BETWEEN :date_start AND :date_end";


QList<CountableGoods *> SqlShopInfoStorage::getCountableGoodsByQuery(const QString &sqlQuery, QObject *parent,
                                                                     const QVariantList &bindValues)
{
    clearLastError();

    QSqlQuery queryGoods(fDatabase);
    queryGoods.prepare(sqlQuery);
    for (int bindValNum = 0; bindValNum < bindValues.size(); ++bindValNum) {
        queryGoods.bindValue(bindValNum, bindValues.at(bindValNum));
    }

    if (!queryGoods.exec()) {
        setLastError(tr("Ошибка получения перечня товаров:\n") + queryGoods.lastError().text());
        return QList<CountableGoods *>();
    }

    // Переносим данные запроса в экземпляры класса
    QList<CountableGoods *> result;
    while (queryGoods.next())
    {
        CountableGoods* item = new CountableGoods(parent);

        // Загружаем общие сведения о товаре
        item->setId(queryGoods.value(0).toInt());
        item->setName(queryGoods.value(1).toString());
        item->setPrice(queryGoods.value(2).toDouble());
        item->setCount(queryGoods.value(3).toInt());

        // Загружаем штрихкоды товара
        item->addBarCode(getGoodsBarcodes(item->id()));
        if (!lastError().isNull())
            return QList<CountableGoods *>();

        result.append(item);
    }

    return result;
}


void SqlShopInfoStorage::saveDocument(GoodsDocument *doc)
{
    clearLastError();

    // Запрещено изменять примененный документ
    if (isDocumentApplied(doc->id())) {
        setLastError(tr("Изменять примененный документ нельзя!"));
        return;
    }

    // Открываем транзакцию в БД
    bool transStarted = fDatabase.transaction();

    // Сохранение товаров, перечисленных в документе
    if (lastError().isNull()) {
        foreach (Goods* g, doc->goods()) {
            saveGoods(g);
            if (!lastError().isNull())
                return;
        }
    }

    // Обнуляем идентификатор, если документ не найден в БД
    if (lastError().isNull() && !documentExists(doc->id()))
        doc->setID(-1);

    // Удаление информации о товарах, привязанных к документу ранее
    if (lastError().isNull() && (doc->id() > 0)) {
        QSqlQuery *queryDelDocGoods = new QSqlQuery(fDatabase);
        queryDelDocGoods->prepare(SQL_DEL_DOC_GOODS);
        queryDelDocGoods->bindValue(":doc_id", doc->id());
        if (!queryDelDocGoods->exec())
            setLastError(tr("Ошибка удаления старых товаров из документа:\n") + queryDelDocGoods->lastError().text());
        delete queryDelDocGoods;
    }

    // Сохранение основной информации о документе
    if (lastError().isNull()) {
        QSqlQuery *querySaveDoc = new QSqlQuery(fDatabase);
        if (doc->id() > 0) {
            querySaveDoc->prepare(SQL_UPD_DOC);
            querySaveDoc->bindValue(":doc_id", doc->id());
            querySaveDoc->bindValue(":doc_type", docTypeToString(doc->documentType()));
            querySaveDoc->bindValue(":status", (doc->status() == Applied)?"A":"N");
            querySaveDoc->bindValue(":date_create", doc->createDate());
            querySaveDoc->bindValue(":date_apply", doc->applyDate());
            if (!querySaveDoc->exec())
                setLastError(tr("Ошибка обновления документа:\n") + querySaveDoc->lastError().text());
        } else {
            querySaveDoc->prepare(SQL_INS_DOC);
            querySaveDoc->bindValue(":doc_type", docTypeToString(doc->documentType()));
            querySaveDoc->bindValue(":status", (doc->status() == Applied)?"A":"N");
            querySaveDoc->bindValue(":date_create", doc->createDate());
            querySaveDoc->bindValue(":date_apply", doc->applyDate());
            if (!querySaveDoc->exec())
                setLastError(tr("Ошибка создания документа:\n") + querySaveDoc->lastError().text());

            doc->setID(querySaveDoc->lastInsertId().toInt());
        }
        delete querySaveDoc;

    }

    // Привязка товаров к документу
    if (lastError().isNull()) {
        QSqlQuery *querySaveDocGoods = new QSqlQuery(fDatabase);
        querySaveDocGoods->prepare(SQL_INS_DOC_GOODS);
        querySaveDocGoods->bindValue(":doc_id", doc->id());
        foreach (CountableGoods* g, doc->goods()) {
            querySaveDocGoods->bindValue(":good_id", g->id());
            querySaveDocGoods->bindValue(":count", g->count());
            querySaveDocGoods->bindValue(":price", g->price());
            if (!querySaveDocGoods->exec()) {
                setLastError(tr("Ошибка добавления товаров к документу:\n") + querySaveDocGoods->lastError().text());
                break;
            }
        }
        delete querySaveDocGoods;
    }

    // Сохранение информации, специфической для данного типа документов
    saveTypeSpecificDocumentInfo(doc);

    // Закрываем транзакцию в БД
    if (transStarted) {
        if (lastError().isNull())
            fDatabase.commit();
        else
            fDatabase.rollback();
    }
}


void SqlShopInfoStorage::applyDocument(GoodsDocument *doc)
{
    clearLastError();

    // Повторно применять документ нельзя
    if (isDocumentApplied(doc->id())) {
        setLastError(tr("Повторно применять документ нельзя!"));
        return;
    }

    // Открываем транзакцию в БД
    bool transStarted = fDatabase.transaction();

    // Сохраняем информацию о приходном документе
    saveDocument(doc);

    // Вносим изменения документа на склад
    applyDocumentToWarehouse(doc);

    // Изменяем статус документа на "Применен"
    doc->setStatus(Applied);
    doc->setApplyDate(QDateTime::currentDateTime());
    QSqlQuery *queryApplyDoc = new QSqlQuery(fDatabase);
    queryApplyDoc->prepare(SQL_UPD_APPLY_DOC);
    queryApplyDoc->bindValue(":apply_date", doc->applyDate());
    queryApplyDoc->bindValue(":doc_id", doc->id());
    if (!queryApplyDoc->exec())
        setLastError(tr("Ошибка установки признака применения документа:\n") + queryApplyDoc->lastError().text());
    delete queryApplyDoc;

    // Закрываем транзакцию в БД
    if (transStarted) {
        if (lastError().isNull())
            fDatabase.commit();
        else
            fDatabase.rollback();
    }
}


SqlShopInfoStorage::SqlShopInfoStorage(QObject *parent) : ShopInfoStorage(parent)
{}


QSqlDatabase SqlShopInfoStorage::database() const
{
    return fDatabase;
}


QList<GoodsDocument *> SqlShopInfoStorage::getDocuments(const GoodsDocumentType &docType, QObject *parent)
{
    clearLastError();

    // Загружаем из БД перечень документов
    QSqlQuery queryDocs(fDatabase);
    queryDocs.prepare(SQL_SEL_DOCS);
    queryDocs.bindValue(":doc_type", docTypeToString(docType));
    if (!queryDocs.exec())
    {
        setLastError(tr("Ошибка получения перечня документов:\n") + queryDocs.lastError().text());
        return QList<GoodsDocument *>();
    }

    // Получаем документы из результатов запроса
    QList<GoodsDocument *> result;
    while (queryDocs.next()) {
        GoodsDocument* newDoc = createNewDocument(docType, parent);

        // Получаем общие сведения о приходном документе
        newDoc->setID(queryDocs.value("rowid").toInt());
        newDoc->setCreateDate(queryDocs.value("date_create").toDateTime());
        newDoc->setApplyDate(queryDocs.value("date_apply").toDateTime());
        if (queryDocs.value("status").toString() == "A")
            newDoc->setStatus(Applied);
        else
            newDoc->setStatus(Editing);

        // Получаем товары по документы
        QVariantList bindVals;
        bindVals += newDoc->id();
        newDoc->addGoods(getCountableGoodsByQuery(SQL_SEL_DOC_GOODS, newDoc, bindVals));
        if (!lastError().isNull())
            return QList<GoodsDocument *>();

        // Загружаем сведения, специфичные для данного вида документов
        loadTypeSpecificDocumentInfo(newDoc, docType);

        result.append(newDoc);
    }

    return result;
}


QList<CountableGoods *> SqlShopInfoStorage::getWarehouse(QObject *parent)
{
    return getCountableGoodsByQuery(SQL_SEL_WAREHOUSE, parent);
}


void SqlShopInfoStorage::loadTypeSpecificDocumentInfo(GoodsDocument *doc, const GoodsDocumentType &docType)
{
    clearLastError();

    if (docType == Income)
        refreshIncomeDocumentProvider(qobject_cast<GoodsIncomeDoc *>(doc));
}


QStringList SqlShopInfoStorage::getGoodsBarcodes(const int &goodsID)
{
    clearLastError();

    QSqlQuery queryBarCodes(fDatabase);
    queryBarCodes.prepare(SQL_SEL_ITEM_BARCODES);
    queryBarCodes.bindValue(":item_id", goodsID);
    if (!queryBarCodes.exec())
    {
        setLastError(tr("Ошибка получения штрихкодов товара:\n") + queryBarCodes.lastError().text());
        return QStringList();
    }

    QStringList result;
    while (queryBarCodes.next())
        result.append(queryBarCodes.value(0).toString());

    return result;
}


bool SqlShopInfoStorage::goodsExist(const int &goodsID)
{
    clearLastError();

    // Проверяем существование товара по идентификатору
    QSqlQuery queryCheckGoods(fDatabase);
    queryCheckGoods.prepare(SQL_SEL_GOODS_ID_BY_ID);
    queryCheckGoods.bindValue(":good_id", goodsID);
    if (queryCheckGoods.exec())
        return queryCheckGoods.next();
    else
        setLastError(tr("Ошибка проверки существования товара:\n") + queryCheckGoods.lastError().text());

    return false;
}


bool SqlShopInfoStorage::documentExists(const int &docID)
{
    clearLastError();

    // Проверяем существование приходного документа по идентификатору
    QSqlQuery queryCheckDoc(fDatabase);
    queryCheckDoc.prepare(SQL_CHECK_DOC_EXISTS);
    queryCheckDoc.bindValue(":doc_id", docID);
    if (queryCheckDoc.exec())
        return queryCheckDoc.next();
    else
        setLastError(tr("Ошибка проверки существования приходного документа:\n") + queryCheckDoc.lastError().text());

    return false;
}


bool SqlShopInfoStorage::isDocumentApplied(const int &docID)
{
    clearLastError();

    QSqlQuery query(fDatabase);
    query.prepare(SQL_SEL_DOC_STATUS);
    query.bindValue(":doc_id", docID);
    if (query.exec()) {
        if (query.next())
            return (query.value(0).toString() == "A");
        else
            return false;
    } else
        setLastError(tr("Ошибка проверки применения документа:\n") + query.lastError().text());

    return false;
}


int SqlShopInfoStorage::findGoodsIDByName(const QString &goodsName)
{
    clearLastError();

    // Проверяем существование приходного документа по идентификатору
    QSqlQuery queryFindGoods(fDatabase);
    queryFindGoods.prepare(SQL_SEL_GOODS_ID_BY_NAME);
    queryFindGoods.bindValue(":name", goodsName);
    if (queryFindGoods.exec()) {
        if (queryFindGoods.next())
            return queryFindGoods.value(0).toInt();
        else
            return -1;
    } else
        setLastError(tr("Ошибка получения идентификатора товара по имени:\n") + queryFindGoods.lastError().text());

    return -1;
}


int SqlShopInfoStorage::getWarehouseGoodsCount(const int &goodsID)
{
    clearLastError();

    QSqlQuery query(fDatabase);
    query.prepare(SQL_SEL_WAREHOUSE_GOODS_COUNT);
    query.bindValue(":good_id", goodsID);
    if (query.exec()) {
        if (query.next())
            return query.value(0).toInt();
        else
            return -1;
    } else
        setLastError(tr("Ошибка получения количества товара на складе:\n") + query.lastError().text());

    return -1;
}


double SqlShopInfoStorage::getMoneyIncome(const QDateTime &dateStart, const QDateTime &dateEnd)
{
    clearLastError();

    QSqlQuery query(fDatabase);
    query.prepare(SQL_SEL_MONEY_INCOME);
    query.bindValue(":date_start", dateStart);
    query.bindValue(":date_end", dateEnd);
    if (query.exec() && query.next())
        return query.value(0).toDouble();
    else
        setLastError(query.lastError().text());

    return 0.0;
}


double SqlShopInfoStorage::getMoneyOutcome(const QDateTime &dateStart, const QDateTime &dateEnd)
{
    clearLastError();

    QSqlQuery query(fDatabase);
    query.prepare(SQL_SEL_MONEY_OUTCOME);
    query.bindValue(":date_start", dateStart);
    query.bindValue(":date_end", dateEnd);
    if (query.exec() && query.next())
        return query.value(0).toDouble();
    else
        setLastError(query.lastError().text());

    return 0.0;
}


void SqlShopInfoStorage::setDatabase(const QSqlDatabase &newDatabase)
{
    fDatabase = newDatabase;
}


void SqlShopInfoStorage::deleteDocument(const int &docID)
{
    clearLastError();

    // Запрещено удалять примененный документ
    if (isDocumentApplied(docID)) {
        setLastError(tr("Удалять примененный документ нельзя!"));
        return;
    }
    if (!lastError().isNull())
        return;

    // Открываем транзакцию в БД
    bool transStarted = fDatabase.transaction();

    // Удаляем прикрепленные товары
    QSqlQuery *queryDelDocGoods = new QSqlQuery(fDatabase);
    queryDelDocGoods->prepare(SQL_DEL_DOC_GOODS);
    queryDelDocGoods->bindValue(":doc_id", docID);
    if (!queryDelDocGoods->exec())
        setLastError(tr("Ошибка удаления всех товаров из документа:\n") + queryDelDocGoods->lastError().text());
    delete queryDelDocGoods;

    // Удаляем приходный документ
    if (lastError().isNull()) {
        QSqlQuery *queryDelIncomeDoc = new QSqlQuery(fDatabase);
        queryDelIncomeDoc->prepare(SQL_DEL_INCOME_DOC);
        queryDelIncomeDoc->bindValue(":doc_id", docID);
        if (!queryDelIncomeDoc->exec())
            setLastError(tr("Ошибка удаления приходного документа:\n") + queryDelIncomeDoc->lastError().text());
        delete queryDelIncomeDoc;
    }

    // Удаляем документ
    if (lastError().isNull()) {
        QSqlQuery *queryDelDoc = new QSqlQuery(fDatabase);
        queryDelDoc->prepare(SQL_DEL_DOC);
        queryDelDoc->bindValue(":doc_id", docID);
        if (!queryDelDoc->exec())
            setLastError(tr("Ошибка удаления документа:\n") + queryDelDoc->lastError().text());
        delete queryDelDoc;
    }

    // Закрываем транзакцию в БД
    if (transStarted) {
        if (lastError().isNull())
            fDatabase.commit();
        else
            fDatabase.rollback();
    }
}


bool SqlShopInfoStorage::incomeDocExists(const int &docID)
{
    clearLastError();

    QSqlQuery query(fDatabase);
    query.prepare(SQL_CHECK_INCOME_DOC_EXISTS);
    query.bindValue(":doc_id", docID);
    if (query.exec())
        return query.next();
    else {
        setLastError(tr("Ошибка проверки существования приходного документа:\n") + query.lastError().text());
        return false;
    }
}


QString SqlShopInfoStorage::docTypeToString(const GoodsDocumentType &docType)
{
    switch (docType) {
    case Income:
        return "INCOME";
    case CashVoucher:
        return "CASH_VOUCHER";
    default:
        return QString();
    }
}


void SqlShopInfoStorage::refreshIncomeDocumentProvider(GoodsIncomeDoc *doc)
{
    clearLastError();

    // Определяем поставщика для приходного документа
    QSqlQuery query(fDatabase);
    query.prepare(SQL_SEL_INCOME_DOC_PROVIDER);
    query.bindValue(":doc_id", doc->id());
    if (query.exec()) {
        if (query.next())
            doc->setProviderName(query.value(0).toString());
    } else
        setLastError(tr("Ошибка получения поставщика для приходного документа:\n") + query.lastError().text());
}


void SqlShopInfoStorage::applyDocumentToWarehouse(GoodsDocument *doc)
{
    clearLastError();

    // Открываем транзакцию в БД
    bool transStarted = fDatabase.transaction();

    // Добавить товары из документа на склад
    foreach (CountableGoods* g, doc->goods()) {
        if (doc->documentType() == Income)
            addGoodsToWarehouse(g->id(), g->count());
        else
            addGoodsToWarehouse(g->id(), - g->count());
    }

    // Закрываем транзакцию в БД
    if (transStarted) {
        if (lastError().isNull())
            fDatabase.commit();
        else
            fDatabase.rollback();
    }
}


void SqlShopInfoStorage::setDocumentStatus(const int &docID, const GoodsDocumentStatus &docStatus)
{
    clearLastError();

    QSqlQuery query(fDatabase);
    query.prepare(SQL_UPD_DOC_STATUS);
    query.bindValue(":doc_id", docID);
    query.bindValue(":status", (docStatus == Applied)?"A":"N");
    if (!query.exec())
        setLastError(tr("Ошибка установки статуса документа:\n") + query.lastError().text());
}


void SqlShopInfoStorage::saveTypeSpecificDocumentInfo(GoodsDocument *doc)
{
    clearLastError();

    // Сохраняем информацию о приходном документе
    GoodsIncomeDoc* incomeDoc = qobject_cast<GoodsIncomeDoc *>(doc);
    if (incomeDoc != nullptr) {
        int providerID = saveProvider(incomeDoc->providerName());

        QSqlQuery *querySaveIncomeDoc = new QSqlQuery(fDatabase);
        if (incomeDocExists(doc->id()))
            querySaveIncomeDoc->prepare(SQL_UPD_INCOME_DOC);
        else
            querySaveIncomeDoc->prepare(SQL_INS_INCOME_DOC);

        querySaveIncomeDoc->bindValue(":doc_id", doc->id());
        querySaveIncomeDoc->bindValue(":provider_id", providerID);
        if (!querySaveIncomeDoc->exec())
            setLastError(tr("Ошибка сохранения приходного документа:\n") + querySaveIncomeDoc->lastError().text());
        delete querySaveIncomeDoc;
    }
}


void SqlShopInfoStorage::saveGoods(Goods *goodsToSave)
{
    clearLastError();

    // Открываем транзакцию в БД
    bool transStarted = fDatabase.transaction();

    // Если у товара указан идентификатор, надо проверить наличие товара с этим идентификатором в БД, обнулить идентификатор, если товара нет
    if ((goodsToSave->id() > 0) && !goodsExist(goodsToSave->id()))
        goodsToSave->setId(-1);
    if (!lastError().isNull())
        return;

    // Если у товара некорректный идентификатор, надо найти похожее наименование
    if (lastError().isNull()) {
        if (goodsToSave->id() <= 0)
            goodsToSave->setId(findGoodsIDByName(goodsToSave->name()));
    }

    // Сохранение общей информации о товаре
    if (lastError().isNull()) {
        QSqlQuery *querySaveGoods = new QSqlQuery(fDatabase);
        if (goodsToSave->id() > 0) {
            // Обновление информации о товаре
            querySaveGoods->prepare(SQL_UPD_GOODS);
            querySaveGoods->bindValue(":good_id", goodsToSave->id());
            querySaveGoods->bindValue(":name", goodsToSave->name());
            if (!querySaveGoods->exec())
                setLastError(tr("Ошибка изменения информации о товаре:\n") + querySaveGoods->lastError().text());
        } else {
            // Добавление нового товара
            querySaveGoods->prepare(SQL_INS_GOODS);
            querySaveGoods->bindValue(":name", goodsToSave->name());
            if (!querySaveGoods->exec())
                setLastError(tr("Ошибка добавления нового товара:\n") + querySaveGoods->lastError().text());
            else
                goodsToSave->setId(querySaveGoods->lastInsertId().toInt());
        }
        delete querySaveGoods;
    }

    // Сохранение штрихкодов товара
    if (lastError().isNull())
        saveGoodsBarCodes(goodsToSave->id(), goodsToSave->barCodes());

    // Закрываем транзакцию в БД
    if (transStarted) {
        if (lastError().isNull())
            fDatabase.commit();
        else
            fDatabase.rollback();
    }
}


void SqlShopInfoStorage::saveGoods(const QList<Goods *> goodsToSave)
{
    clearLastError();

    // Открываем транзакцию в БД
    bool transStarted = fDatabase.transaction();

    // Сохраняем все товары в БД
    ShopInfoStorage::saveGoods(goodsToSave);

    // Закрываем транзакцию в БД
    if (transStarted) {
        if (lastError().isNull())
            fDatabase.commit();
        else
            fDatabase.rollback();
    }
}


void SqlShopInfoStorage::saveGoodsBarCodes(const int &goodsID, const QStringList &barCodes)
{
    clearLastError();

    // Открываем транзакцию в БД
    bool transStarted = fDatabase.transaction();

    // Удаление старых штрихкодов
    QSqlQuery *queryClearBarcodes = new QSqlQuery(fDatabase);
    queryClearBarcodes->prepare(SQL_DEL_ALL_GOODS_BARCODES);
    queryClearBarcodes->bindValue(":good_id", goodsID);
    if (!queryClearBarcodes->exec())
        setLastError(tr("Ошибка очистки старых штрихкодов товара:\n") + queryClearBarcodes->lastError().text());
    delete queryClearBarcodes;

    // Добавляем все штрихкоды к товару
    if (lastError().isNull()) {
        QSqlQuery *queryAddBarcode = new QSqlQuery(fDatabase);
        queryAddBarcode->prepare(SQL_ADD_GOODS_BARCODE);
        foreach (QString barc, barCodes) {
            queryAddBarcode->bindValue(":good_id", goodsID);
            queryAddBarcode->bindValue(":barcode", barc);
            if (!queryAddBarcode->exec()) {
                setLastError(tr("Ошибка добавления штрихкода к товару:\n") + queryAddBarcode->lastError().text());
                break;
            }
        }
        delete queryAddBarcode;
    }

    // Закрываем транзакцию в БД
    if (transStarted) {
        if (lastError().isNull())
            fDatabase.commit();
        else
            fDatabase.rollback();
    }
}


int SqlShopInfoStorage::saveProvider(const QString &providerName)
{
    clearLastError();

    // Если поставщик уже существует, то вернем его идентификатор
    QSqlQuery queryProvider(fDatabase);
    queryProvider.prepare(SQL_SEL_PROVIDER_ID_BY_NAME);
    queryProvider.bindValue(":name", providerName);
    if (!queryProvider.exec())
        setLastError(tr("Ошибка проверки наличия поставщика:\n") + queryProvider.lastError().text());
    else if (queryProvider.next())
        return queryProvider.value(0).toInt();

    // Иначе сохраняем нового поставщика
    if (lastError().isNull()) {
        QSqlQuery queryAddProvider(fDatabase);
        queryAddProvider.prepare(SQL_INS_PROVIDER);
        queryAddProvider.bindValue(":name", providerName);
        if (queryAddProvider.exec())
            return queryAddProvider.lastInsertId().toInt();
        else
            setLastError(tr("Ошибка сохранения поставщика:\n") + queryAddProvider.lastError().text());
    }

    return -1;
}


void SqlShopInfoStorage::addGoodsToWarehouse(const int &goodsID, const int &goodsCount)
{
    clearLastError();

    // Проверяем возможность добавление/удаления товара
    int whGoodsCount = getWarehouseGoodsCount(goodsID);
    if (whGoodsCount + goodsCount < 0)
        setLastError(tr("На складе не хватает товара для списания!"));

    // Вносим/удаляем товар на склад
    if (lastError().isNull()) {
        QSqlQuery *queryAddGoodsToWH = new QSqlQuery(fDatabase);
        if (whGoodsCount < 0)
            queryAddGoodsToWH->prepare(SQL_INS_WAREHOUSE_GOODS);
        else
            queryAddGoodsToWH->prepare(SQL_UPD_INC_WAREHOUSE_GOODS);

        queryAddGoodsToWH->bindValue(":good_id", goodsID);
        queryAddGoodsToWH->bindValue(":good_count", goodsCount);
        if (!queryAddGoodsToWH->exec())
            setLastError(queryAddGoodsToWH->lastError().text());
        delete queryAddGoodsToWH;
    }
}


void SqlShopInfoStorage::setGoodsPrice(const int &goodsID, const double &goodsPrice)
{
    clearLastError();

    // Открываем транзакцию в БД
    bool transStarted = fDatabase.transaction();

    // Сохраняем цену товара в истории цен
    QSqlQuery *querySavePriceHistory = new QSqlQuery(fDatabase);
    querySavePriceHistory->prepare(SQL_INS_PRICE_HIST);
    querySavePriceHistory->bindValue(":good_id", goodsID);
    querySavePriceHistory->bindValue(":date_start", QDateTime::currentDateTime());
    querySavePriceHistory->bindValue(":price", goodsPrice);
    if (!querySavePriceHistory->exec())
        setLastError(tr("Ошибка изменения истории цен:\n") + querySavePriceHistory->lastError().text());
    delete querySavePriceHistory;

    // Устанавливаем цену на складе
    if (lastError().isNull()) {
        QSqlQuery *queryUpdWarehousePrice = new QSqlQuery(fDatabase);
        queryUpdWarehousePrice->prepare(SQL_UPD_WAREHOUSE_PRICE);
        queryUpdWarehousePrice->bindValue(":good_id", goodsID);
        queryUpdWarehousePrice->bindValue(":price", goodsPrice);
        if (!queryUpdWarehousePrice->exec())
            setLastError(tr("Ошибка изменения цены на складе:\n") + queryUpdWarehousePrice->lastError().text());
        delete queryUpdWarehousePrice;
    }

    // Закрываем транзакцию в БД
    if (transStarted) {
        if (lastError().isNull())
            fDatabase.commit();
        else
            fDatabase.rollback();
    }
}
