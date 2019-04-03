#ifndef CONTENTMODEL_H
#define CONTENTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>
#include <QVector>

class contentModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit contentModel(QObject* parent = nullptr);

    enum RoleTypes{
        MESSAG = Qt::UserRole+1,
        TIMESTAMP
    };    

    Q_INVOKABLE QString getColor(int index);
    Q_INVOKABLE bool getAction(int index);

    virtual int rowCount(const QModelIndex &parent = QModelIndex() ) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    void append(const QString &message, const QString timeStamp);
    void clear();
    void addProperties(bool self, bool action);

signals:
    void rowAdd();

private:
    QStringList m_messageList;
    QStringList m_timestampList;

    QVector<QString> m_colors;
    QVector<bool> m_action;

};

#endif // CONTENTMODEL_H
