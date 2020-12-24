#include "SQLAuthSystem.h"
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlError>
#include <QCryptographicHash>
#include <QVariant>
#include <QDebug>


const QString SQL_PARAM_USERNAME = ":username";
const QString SQL_PARAM_PASSWORD = ":pwd";

const QString SQL_CHECK_USER_INFO = "SELECT * FROM users WHERE username = " + SQL_PARAM_USERNAME + " AND password_md5 = " + SQL_PARAM_PASSWORD;


SQLAuthSystem::SQLAuthSystem(QObject *parent) : AuthSystem(parent)
{}


QSqlDatabase SQLAuthSystem::database() const
{
    return fDatabase;
}


void SQLAuthSystem::setDatabase(QSqlDatabase &newDatabase)
{
    fDatabase = newDatabase;
}


bool SQLAuthSystem::login(const QString &username, const QString &password)
{
    clearLastError();

    // Шифруем пароль в MD5
    QString encodedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex()).toUpper();

    // Проверяем совпадение логина с паролем в БД
    QSqlQuery query(fDatabase);
    query.prepare(SQL_CHECK_USER_INFO);
    query.bindValue(SQL_PARAM_USERNAME, username);
    query.bindValue(SQL_PARAM_PASSWORD, encodedPassword);
    if (query.exec()) {
        return query.first();
    } else {
        setLastError(query.lastError().text());
        return false;
    }
}
