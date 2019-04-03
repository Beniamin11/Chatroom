#ifndef PMMODEL_H
#define PMMODEL_H


#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>
#include <QVector>

class pmModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit pmModel(QObject* parent = nullptr);

    enum RoleTypes{
        MESSAG = Qt::UserRole+1
    };

    Q_INVOKABLE bool getAlign(int index);
    Q_INVOKABLE QString getColor(int index);

    virtual int rowCount(const QModelIndex &parent = QModelIndex() ) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    void append(const QString &message);
    void clear();
    void addProperties(bool self);

signals:
    void otherUserChanged(QString other);
    void appendChanged();

private:
    QStringList stringList;
    QVector<QString> m_colors;
    QVector<bool> m_align;
};

#endif // PMMODEL_H
