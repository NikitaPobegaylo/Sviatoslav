#include "MainWindow.h"
#include <QApplication>
#include "AuthorizationDialog.h"
#include "Authorization/SQLAuthSystem.h"
#include "Authorization/AuthSystem.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QFile>
#include <QSqlQuery>
#include <QDebug>
#include <CountableGoodsModel.h>
#include <QList>
#include "CountableGoods.h"
#include "ShopInfoStorage/SqlShopInfoStorage.h"


const QString MSG_DB_CONNECT_ERROR_TITLE = QObject::tr("Ошибка соединения с базой данных");
const QString MSG_INIT_SCRIPT_OPEN_ERROR_TITLE = QObject::tr("Ошибка открытия скрипта для инициализации БД");
const QString MSG_INIT_SCRIPT_EXEC_ERROR_TITLE = QObject::tr("Ошибка выполнения запроса для инициализации БД");


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");

    // Устанавливаем соединение с базой данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QApplication::applicationDirPath() + "/database.db");
    if (!db.open()) {
        QMessageBox::critical(nullptr, MSG_DB_CONNECT_ERROR_TITLE, db.lastError().text());
        return 0;
    }

    // Загружаем скрипт для инициализации БД
    QFile initScript(":/Scripts/InitializeDB.sql");
    if (!initScript.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::critical(nullptr, MSG_INIT_SCRIPT_OPEN_ERROR_TITLE, initScript.errorString());
        return 0;
    }
    QStringList sqlStatements = QString::fromUtf8(initScript.readAll()).split(";", QString::SkipEmptyParts);

    // Инициализируем базу данных
    QSqlQuery query(db);
    foreach (QString sql, sqlStatements) {
        query.prepare(sql);
        if (!query.exec()) {
            QMessageBox::critical(nullptr, MSG_INIT_SCRIPT_EXEC_ERROR_TITLE, query.lastError().text());
            qDebug() << query.lastQuery();
            return 0;
        }
    }

    // Определяем систему для авторизации в приложении
    SQLAuthSystem *authSys = new SQLAuthSystem();
    authSys->setDatabase(db);
    AuthSystem::currentAuthSystem = authSys;

    // Определяем хранилище с информацией магазина
    SqlShopInfoStorage *shopStorage = new SqlShopInfoStorage();
    shopStorage->setDatabase(db);
    ShopInfoStorage::currentStorage = shopStorage;

    // Авторизуемся в приложении
    AuthorizationDialog* authDlg = new AuthorizationDialog();
    if (!authDlg->exec())
        return 0;
    delete authDlg;

    MainWindow w;
    w.show();

    return a.exec();
}
