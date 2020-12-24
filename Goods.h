#ifndef ITEM_H
#define ITEM_H


#include <QObject>
#include <QList>


class Goods : public QObject
{
    Q_OBJECT

private:
    QString fName;
    double fPrice = 0.0;
    QStringList fBarCodes;
    int fID = -1;

public:
    explicit Goods(QObject *parent = nullptr);

    QString name() const;
    double price() const;
    QStringList barCodes() const;
    int id() const;

public slots:
    void setId(const int &newId);
    void setName(const QString &newName);
    virtual void setPrice(const double &newPrice);
    void addBarCode(const QString &newBarCode);
    void addBarCode(const QStringList &newBarCodes);
    void removeBarCode(const QString &delBarCode);
    void clearBarCodes();

signals:
    void priceChanged();
};


#endif // ITEM_H
