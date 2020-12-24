#include "AuthorizationDialog.h"
#include "ui_AuthorizationDialog.h"
#include "Authorization/AuthSystem.h"
#include <QMessageBox>


const QString MSG_FAIL_LOGIN_TITLE = QObject::tr("Ошибка авторизации");
const QString MSG_FAIL_LOGIN_TEXT = QObject::tr("Неправильный логин или пароль!");


AuthorizationDialog::AuthorizationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationDialog)
{
    ui->setupUi(this);
    adjustSize();

    connect(ui->tbLogin, SIGNAL(pressed()), SLOT(login()));
}


AuthorizationDialog::~AuthorizationDialog()
{
    delete ui;
}


void AuthorizationDialog::login()
{
    // Пытаемся авторизоваться под именем пользователя
    AuthSystem* authSys = AuthSystem::currentAuthSystem;
    if (authSys->login(ui->edtUsername->text(), ui->edtPassword->text()))
        this->accept();
    else {
        if (authSys->lastError().isNull())
            QMessageBox::critical(this, MSG_FAIL_LOGIN_TITLE, MSG_FAIL_LOGIN_TEXT);
        else
            QMessageBox::critical(this, MSG_FAIL_LOGIN_TITLE, authSys->lastError());
    }
}
