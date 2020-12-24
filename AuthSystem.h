#ifndef AUTHSYSTEM_H
#define AUTHSYSTEM_H


#include <QObject>


class AuthSystem : public QObject
{
    Q_OBJECT    

private:
    QString fLastError;

protected:
    void setLastError(const QString &newLastError);
    void clearLastError();

public:
    static AuthSystem* currentAuthSystem;

    explicit AuthSystem(QObject *parent = nullptr);

    QString lastError() const;

public slots:
    virtual bool login(const QString &username, const QString &password) = 0;
};


#endif // AUTHSYSTEM_H
