#include "encrypt.h"
#include <QDebug>
#include <QChar>

QString encryptMessage(const QString &message)
{
    QString code_list;
    std::map<QString, int> table = initEncryptTable();

    QString c = "";
    c = message[0]; int i_code = table[c]; i_code = i_code + 11;
    QString code; code.setNum(i_code); code_list = code_list +  code;
    qDebug() << code_list;

    for(int i = 1; i < message.length(); ++i)
    {
        c = message[i];
        int i_code;
        if(table.find(c) != table.end())
            i_code = table[c];
        else
            i_code = 717;

        if(i%2)
            i_code = i_code + 7;
        else
            i_code = i_code + 11;

        code.setNum(i_code);
        code_list = code_list + code;
    }

    qDebug () <<"Code list: "<<code_list;
    return code_list;
}


QString decryptMessage(const QString &codeList)
{
    QString decMessage;
    std::map<int, QString> table = initDecryptTable();
//    QStringList code_list = codeList.split('*');
    int code;

    for(int i = 0; i < codeList.length(); i = i+3)
    {
        QString q_code = codeList.mid(i,3);
        code = q_code.toInt();

        qDebug() << "code: "<< code;
        if(i%2)
            code = code - 7;
        else
            code = code - 11;

        decMessage = decMessage + table[code];
        qDebug() << "decMessage: "<<decMessage ;
    }

    return decMessage;
}


std::map<QString, int> initEncryptTable()
{
    std::map<QString, int> table;
    int j;
    for(int i = 0; i < 257; ++i)
    {
        j = i + 107;
        QChar ch;
        ch = char(i);
        table[ch] = j;
    }
    table["\n"] = 364;
    table["Ă"] = 365;
    table["Â"] = 366;
    table["Î"] = 367;
    table["Ș"] = 368;
    table["Ț"] = 369;
    table["ă"] = 370;
    table["â"] = 371;
    table["î"] = 372;
    table["ș"] = 373;
    table["ț"] = 374;
    table[""] = 717;

    return table;
}


std::map<int, QString> initDecryptTable()
{

    std::map<int, QString> table;
    int j;
    for(int i = 32; i < 129; ++i)
    {
        j = i + 107;
        QChar ch;
        ch = char(i);
        table[j] = ch;
    }

    table[364] = "\n";
    table[365] = "Ă";
    table[366] = "Â";
    table[367] = "Î";
    table[368] = "Ș";
    table[369] = "Ț";
    table[370] = "ă";
    table[371] = "â";
    table[372] = "î";
    table[373] = "ș";
    table[374] = "ț";
    table[717] = "";

    return table;
}
