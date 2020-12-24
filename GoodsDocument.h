#ifndef GOODSDOCUMENT_H
#define GOODSDOCUMENT_H


#include <QObject>
#include <QDateTime>
#include "CountableGoods.h"


enum GoodsDocumentStatus {
    Editing,
    Applied
};


enum GoodsDocumentType {
    Unknown,
    Income,
    CashVoucher
};


class GoodsDocument : public QObject
{
    Q_OBJECT

private:
    int fID = -1;
    QDateTime fCreateDate = QDateTime::currentDateTime();
    QDateTime fApplyDate;
    QList<CountableGoods*> fGoods;
    GoodsDocumentStatus fStatus = Editing;
    GoodsDocumentType fDocumentType = Unknown;

public:
    explicit GoodsDocument(QObject *parent = nullptr);

    int id() const;
    GoodsDocumentType documentType() const;
    GoodsDocumentStatus status() const;
    QDateTime createDate() const;
    QDateTime applyDate() const;
    QList<CountableGoods *> goods() const;
    double price() const;

public slots:
    void setID(const int &newID);
    void setDocumentType(const GoodsDocumentType &newDocType);
    void setStatus(const GoodsDocumentStatus &newStatus);
    void setCreateDate(const QDateTime &newCreateDate);
    void setApplyDate(const QDateTime &newApplyDate);
    void addGoods(CountableGoods * const &itm);
    void addGoods(const QList<CountableGoods *> &newGoods);
    void removeGoods(CountableGoods * const &itm);
    void clearGoods();
};


#endif // GOODSDOCUMENT_H
