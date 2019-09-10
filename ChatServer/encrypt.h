#ifndef ENCRYPT
#define ENCRYPT

#include <QString>
#include <vector>
#include <map>
#include <string>

QString encryptMessage(const QString &message);

QString decryptMessage(const QString &codeList);

std::map<QString, int> initEncryptTable();

std::map<int, QString> initDecryptTable();

#endif // ENCRYPT

