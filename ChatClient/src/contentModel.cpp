#include "contentModel.h"

contentModel::contentModel(QObject *parent) : QAbstractListModel(parent)
{}

int contentModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_messageList.count();
}

QVariant contentModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() || index.row() > m_messageList.count())
        return QVariant();

    if(role == MESSAG)    
        return m_messageList.at(index.row());
    else if(role == TIMESTAMP)
        return m_timestampList.at(index.row());
    else
        return QVariant();
}

QHash<int, QByteArray> contentModel::roleNames() const
{
    QHash<int, QByteArray> rez;
    rez[MESSAG] = "lineMessage";    
    rez[TIMESTAMP] = "timeStamp";
    return rez;
}

void contentModel::append(const QString &message, const QString timeStamp)
{
    beginInsertRows(QModelIndex(), m_messageList.size(), m_messageList.size());
    m_messageList.push_back(message);
    m_timestampList.push_back(timeStamp);
    endInsertRows();

    emit rowAdd();
}

void contentModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_messageList.count());
    m_messageList.clear();
    endRemoveRows();

    beginRemoveRows(QModelIndex(), 0, m_timestampList.count());
    m_timestampList.clear();
    endRemoveRows();

    m_colors.clear();
    m_action.clear();
}

void contentModel::addProperties(bool self, bool action)
{
    if(self)
        m_colors.push_back("#FF0000");
    else
        m_colors.push_back("#000000");
    m_action.push_back(action);
}

QString contentModel::getColor(int index) { return m_colors[index]; }

bool contentModel::getAction(int index) {return m_action[index]; }
