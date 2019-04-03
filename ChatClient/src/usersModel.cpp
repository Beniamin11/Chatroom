#include "usersModel.h"


usersModel::usersModel(QObject *parent) : QAbstractListModel(parent)
{}

int usersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return stringList.count();
}

QVariant usersModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() || index.row() > stringList.count())
        return QVariant();

    if(role == USER)
        return stringList.at(index.row());
    else
        return QVariant();

}

QHash<int, QByteArray> usersModel::roleNames() const
{
    QHash<int, QByteArray> rez;
    rez[USER] = "userName";
    return rez;
}

void usersModel::append(const QString &nickname)
{   
    beginInsertRows(QModelIndex(), stringList.count(), stringList.count());
    stringList.insert(stringList.count(), nickname);
    endInsertRows();
}

void usersModel::remove(const QString &nickname)
{
    quint16 index = 0;
    for ( auto n : stringList)
    {
        if(n.compare(nickname) == 0)
            break;
        index++;

    }
    beginRemoveRows(QModelIndex(), index, index);
    stringList.removeAt(index);
    endRemoveRows();
}

void usersModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, stringList.count());
    stringList.clear();
    endRemoveRows();
}

void usersModel::addOnTop( const QString &nickname)
{    
    beginInsertRows(QModelIndex(),0,0);
    stringList.insert(0, nickname);
    endInsertRows();
}

