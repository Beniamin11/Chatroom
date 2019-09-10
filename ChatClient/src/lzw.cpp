#include "../head/lzw.h"


std::map<QString, int> initEncodeTable()
{
    std::map<QString, int> table;

    for(int i = 0; i < 257; ++i)
    {
        QChar ch;
        ch = char(i);
        table[ch] = i;
    }
    table["\n"] = 257;
    table["Ă"]  = 258;
    table["Â"]  = 259;
    table["Î"]  = 260;
    table["Ș"]  = 261;
    table["Ț"]  = 262;
    table["ă"]  = 263;
    table["â"]  = 264;
    table["î"]  = 265;
    table["ș"]  = 266;
    table["ț"]  = 267;
    table[""]   = 717;
    return table;
}

std::map<int, QString> initDecodeTable()
{

    std::map<int, QString> table;

    for(int i = 0; i < 257; ++i)
    {
        QChar ch;
        ch = char(i);
        table[i] = ch;
    }

    table[257] = "\n";
    table[258] = "Ă";
    table[259] = "Â";
    table[260] = "Î";
    table[261] = "Ș";
    table[262] = "Ț";
    table[263] = "ă";
    table[264] = "â";
    table[265] = "î";
    table[266] = "ș";
    table[267] = "ț";
    table[717] = "";

    return table;
}


std::vector<int> encode(QString dataString)
{
    qDebug ()  << "Encoding\n";
    std::map<QString, int> table = initEncodeTable();

    QString prev = "", curr = "";
    prev += dataString[0];
    int code = 268;
    std::vector<int> output_code;

    for (int i = 0; i < dataString.length(); i++) {
        if (i != dataString.length() - 1)
            curr += dataString[i + 1];
        if (table.find(prev + curr) != table.end()) {
            prev = prev + curr;
        }
        else {
            output_code.push_back(table[prev]);
            table[prev + curr] = code;
            code++;
            prev = curr;
        }
        curr = "";
    }

    output_code.push_back(table[prev]);
    return output_code;
}

QString decode(std::vector<int> codeList)
{
    qDebug ()  << "\nDecoding\n";

    std::map<int, QString> table = initDecodeTable();
    int old = codeList[0], n;
    int count = 268;
    QString decodedMessage;
    QString output = table[old];
    QString curr = "";

    decodedMessage = curr = output[0];

    for (size_t i = 0; i < codeList.size() - 1; i++) {
        n = codeList[i + 1];
        if (table.find(n) == table.end()) {
            output = table[old];
            output = output + curr;
        }
        else {
            output = table[n];
        }
        decodedMessage = decodedMessage + output;
        curr = "";
        curr += output[0];
        table[count] = table[old] + curr;
        count++;
        old = n;
    }

    return decodedMessage;
}


QString codeList(std::vector<int> m_codeList)
{
    QString returnValue = "";
    QString code;
    for( int elem : m_codeList)
    {
        code.setNum(elem);
        returnValue = returnValue + code + " ";
    }
    QString m_stringCodeList = returnValue;
    return m_stringCodeList;
}


QString compress(const QString &text)
{     
    std::vector<int> code_list = encode(text);
    QString returnValue = codeList(code_list);
    return returnValue;
}

QString decompress(const QString &text)
{
    std::vector<int> codeList;
    qDebug () << "Decompressing..." << text;
    QStringList compressed = text.split(" ");
    for(int i = 0; i < compressed.length(); ++i)
    {
        QString code = compressed[i];
        int i_code = code.toInt();
        codeList.push_back(i_code);
        qDebug () << i_code;
    }

    QString returnValue = decode(codeList);
    return returnValue;
}
