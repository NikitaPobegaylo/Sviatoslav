#ifndef GOODSINCOMEDOC_H
#define GOODSINCOMEDOC_H


#include <QObject>
#include "GoodsDocument.h"


class GoodsIncomeDoc : public GoodsDocument
{
    Q_OBJECT

private:
    QString fProviderName;

public:
    explicit GoodsIncomeDoc(QObject *parent = nullptr);

    QString providerName() const;

public slots:
    void setProviderName(const QString &newProviderName);
};


#endif // GOODSINCOMEDOC_H
