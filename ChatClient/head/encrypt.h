#ifndef ENCRYPT
#define ENCRYPT

#include <QString>

QString encryptMessage(const QString &message, int key);

QString decryptMessage(const QString &message, int key);

#endif // ENCRYPT

