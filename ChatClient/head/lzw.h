#ifndef LZW
#define LZW

#include <iostream>
#include <vector>
#include <QString>
#include <Bits.h>
#include <map>
#include <QDebug>

std::map<QString, int> initEncodeTable();
std::map<int, QString> initDecodeTable();

std::vector<int> encode(QString s1);
QString decode(std::vector<int> codeList);

QString codeList(std::vector<int> m_codeList);

QString decompress(const QString &text);
QString compress(const QString &text);

void setCharString(QString str);



#endif // LZW

