#ifndef SQLAUTHSYSTEM_H
#define SQLAUTHSYSTEM_H


#include "AuthSystem.h"
#include <QSqlDatabase>


class SQLAuthSystem : public AuthSystem
{
    Q_OBJECT

private:
    QSqlDatabase fDatabase;

public:
    explicit SQLAuthSystem(QObject *parent = nullptr);

    QSqlDatabase database() const;

    bool login(const QString &username, const QString &password);

public slots:
    void setDatabase(QSqlDatabase &newDatabase);
};


#endif // SQLAUTHSYSTEM_H
