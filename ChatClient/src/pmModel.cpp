#include "pmModel.h"

pmModel::pmModel(QObject *parent) : QAbstractListModel(parent)
{}

int pmModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return stringList.count();
}

QVariant pmModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() || index.row() > stringList.count())
        return QVariant();

    if(role == MESSAG)
        return stringList.at(index.row());
    else
        return QVariant();

}

QHash<int, QByteArray> pmModel::roleNames() const
{
    QHash<int, QByteArray> rez;
    rez[MESSAG] = "lineMessage";
    return rez;
}

void pmModel::append(const QString &message)
{
    beginInsertRows(QModelIndex(), stringList.size(), stringList.size());
    stringList.push_back(message);
    endInsertRows();
    emit appendChanged();
}

void pmModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, stringList.count());
    stringList.clear();
    endRemoveRows();
}

void pmModel::addProperties(bool self)
{
    if(self)
        m_colors.push_back("#00FF00");
    else
        m_colors.push_back("#A9D0F5");
    m_align.push_back(self);
}

bool pmModel::getAlign(int index) { return m_align[index]; }

QString pmModel::getColor(int index) { return m_colors[index]; }
