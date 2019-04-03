#include "encrypt.h"
#include <QDebug>
#include <string>

QString encryptMessage(const QString &message, int key)
{
    std::string stdMessage = message.toStdString();

    for(size_t i = 0; i < stdMessage.length(); i++)
    {        
        if(stdMessage[i] != '\n')
            i % 2 == 0 ? stdMessage[i] = stdMessage[i] - 7 : stdMessage[i] = stdMessage[i] - 11;
    }

    QString encMess = QString::fromStdString(stdMessage);    
    return encMess;
}


QString decryptMessage(const QString &message, int key)
{    
    std::string stdMessage = message.toStdString();

    for(size_t i = 0; i < stdMessage.length(); i++)
    {        
        if(stdMessage[i] != '\n')
            i % 2 == 0 ? stdMessage[i] = stdMessage[i] + 7 : stdMessage[i] = stdMessage[i] + 11;
    }

    QString decMess = QString::fromStdString(stdMessage);    
    return decMess;
}
