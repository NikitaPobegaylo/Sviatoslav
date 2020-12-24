#ifndef AUTHORIZATIONDIALOG_H
#define AUTHORIZATIONDIALOG_H


#include <QDialog>


namespace Ui {
class AuthorizationDialog;
}

class AuthorizationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationDialog(QWidget *parent = 0);
    ~AuthorizationDialog();

private:
    Ui::AuthorizationDialog *ui;

protected slots:
    void login();
};


#endif // AUTHORIZATIONDIALOG_H
