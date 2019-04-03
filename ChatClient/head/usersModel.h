#ifndef USERSMODEL_H
#define USERSMODEL_H


#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>

class usersModel : public QAbstractListModel
{
    Q_OBJECT    

public:
    explicit usersModel(QObject* parent = nullptr);

    enum RoleTypes{
        USER = Qt::UserRole+1
    };

    virtual int rowCount(const QModelIndex &parent = QModelIndex() ) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    void append(const QString &nickname);
    void remove(const QString &nickname);
    void clear();
    void addOnTop(const QString &nickname);

signals:    


private:
    QStringList stringList;    
};

#endif // USERSMODEL_H
