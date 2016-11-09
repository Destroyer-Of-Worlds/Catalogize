#include "lecturemodel.h"

LectureModel::LectureModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    root->id = 0;
    root->count = 0;
    root->data.path = "Root";
    root->number = 0;
    root->type = ROOT;
    DataWrapper* dw;
    QSqlQuery query;
    if (!query.exec("SELECT * FROM subjects_and_themes")) {
        qDebug() << "Невозможно извлечь данные из subjects_and_themes";
    }
    else
    {
        QSqlRecord rec = query.record();
        int type = 0;
        int id = 0;
        while (query.next())
        {
            type = query.value(rec.indexOf("Type")).toInt();
            if(type == 1)
            {
                dw->type = TERM;
                dw->id = query.value(rec.indexOf("Id_subj")).toInt();
                dw->number = query.value(rec.indexOf("Serial_number")).toInt();
                dw->data.path = query.value(rec.indexOf("Term")).toString();
                dw->parent = root;
                root->children << dw;
            }
        }
        query.first();
        while (query.next())
        {
            type = query.value(rec.indexOf("Type")).toInt();
            if(type == 2)
            {
                dw->type = COURSE;
                dw->id = query.value(rec.indexOf("Id_subj")).toInt();
                dw->number = query.value(rec.indexOf("Serial_number")).toInt();
                dw->data.path = query.value(rec.indexOf("Name_subj")).toString();
                id = query.value(rec.indexOf("Id_parent")).toInt();
                foreach (DataWrapper* dw_term, root->children) {
                    if(dw_term->id == id)
                    {
                        dw->parent = dw_term;
                        dw_term->children << dw;
                    }
                }
            }
        }
        while (query.next())
        {
            type = query.value(rec.indexOf("Type")).toInt();
            if(type == 3)
            {
                dw->type = THEME;
                dw->id = query.value(rec.indexOf("Id_subj")).toInt();
                dw->number = query.value(rec.indexOf("Serial_number")).toInt();
                dw->data.path = query.value(rec.indexOf("Name_subj")).toString();
                id = query.value(rec.indexOf("Id_parent")).toInt();
                foreach (DataWrapper* dw_term, root->children) {
                    foreach (DataWrapper* dw_sub, dw_term->children) {
                        if(dw_term->id == id)
                        {
                            dw->parent = dw_sub;
                            dw_sub->children << dw;
                        }
                    }
                }
            }
        }
    }


}

QVariant LectureModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex LectureModel::index(int row, int column, const QModelIndex &parent) const
{
    //createIndex()
}

QModelIndex LectureModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int LectureModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
}

int LectureModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
    return 1;
}

QVariant LectureModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
