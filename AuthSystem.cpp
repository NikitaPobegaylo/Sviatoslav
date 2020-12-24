#include "AuthSystem.h"


AuthSystem *AuthSystem::currentAuthSystem = nullptr;


void AuthSystem::setLastError(const QString &newLastError)
{
    fLastError = newLastError;
}


void AuthSystem::clearLastError()
{
    fLastError = QString();
}


AuthSystem::AuthSystem(QObject *parent) : QObject(parent)
{
}


QString AuthSystem::lastError() const
{
    return fLastError;
}
