#ifndef LECTUREMODEL_H
#define LECTUREMODEL_H

#include <QAbstractItemModel>
#include <databasehandler.h>
#include <QModelIndex>
#include <QVariant>


enum h_type{ROOT, TERM = 1, COURSE, THEME, IMAGE};

struct IData
{
    QString name;
    QString comment;
    QString tags;
};

struct DataWrapper
{
    quint16 id;
    h_type type;
    IData *data;
    int number;
    DataWrapper *parent;
    QList<DataWrapper *> children;
    int count;
};

class LectureModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit LectureModel(QString dbPath, QObject *parent = 0);
    ~LectureModel();
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent);
    bool hasChildren(const QModelIndex &parent) const;

private:

    QString dbName;
    DataBaseHandler *dataBase;
    DataWrapper* root;

};

#endif // LECTUREMODEL_H
