#include "lecturemodel.h"

LectureModel::LectureModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    root = new DataWrapper;
    root->id = 0;
    root->count = 0;
    IData *iData = new IData;
    iData->name = "Root";
    root->data = iData;
    root->number = 0;
    root->type = ROOT;
    //root->parent = qobject_cast<DataWrapper*>(parent);
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
            dw = new DataWrapper;
            iData = new IData;
            type = query.value(rec.indexOf("Type")).toInt();
            if(type == 1)
            {
                dw->type = TERM;
                dw->id = query.value(rec.indexOf("Id_subj")).toInt();
                dw->number = query.value(rec.indexOf("Serial_number")).toInt();
                iData->name = query.value(rec.indexOf("Term")).toString();
                dw->data = iData;
                dw->parent = root;
                root->children.append(dw);
            }
        }
        query.first();
        while (query.next())
        {

            type = query.value(rec.indexOf("Type")).toInt();
            if(type == 2)
            {
                dw = new DataWrapper;
                iData = new IData;
                dw->type = COURSE;
                dw->id = query.value(rec.indexOf("Id_subj")).toInt();
                dw->number = query.value(rec.indexOf("Serial_number")).toInt();
                iData->name = query.value(rec.indexOf("Name_subj")).toString();
                dw->data = iData;
                id = query.value(rec.indexOf("Id_parent")).toInt();
                foreach (DataWrapper* dw_term, root->children) {
                    if(dw_term->id == id)
                    {
                        dw->parent = dw_term;
                        dw_term->children.append(dw);
                    }
                }
            }
        }
        query.first();
        while (query.next())
        {

            type = query.value(rec.indexOf("Type")).toInt();
            if(type == 3)
            {
                dw = new DataWrapper;
                iData = new IData;
                dw->type = THEME;
                dw->id = query.value(rec.indexOf("Id_subj")).toInt();
                dw->number = query.value(rec.indexOf("Serial_number")).toInt();
                iData->name = query.value(rec.indexOf("Name_subj")).toString();
                dw->data = iData;
                id = query.value(rec.indexOf("Id_parent")).toInt();
                foreach (DataWrapper* dw_term, root->children) {
                    foreach (DataWrapper* dw_sub, dw_term->children) {
                        if(dw_sub->id == id)
                        {
                            dw->parent = dw_sub;
                            dw_sub->children.append(dw);
                            int hght = 0;
                        }
                    }
                }
            }
        }
    }
}

LectureModel::~LectureModel()
{
    //Need implement!!!
    delete root;
}

QVariant LectureModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    return QVariant();
}

QModelIndex LectureModel::index(int row, int column, const QModelIndex &parent) const
{
    //createIndex()
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    DataWrapper *parentItem;

    if(!parent.isValid())
    {
        parentItem = root;
    }
    else
    {
        parentItem = static_cast<DataWrapper*>(parent.internalPointer());
    }

    DataWrapper *childItem = parentItem->children.value(row);
    if(childItem)
    {
        return createIndex(row,column,childItem);
    }
    else
    {
        return QModelIndex();
    }

    /*if(!parent.isValid()){
        return createIndex(row, column, const_cast<DataWrapper*>(root->children.value(row)));
    }

    DataWrapper* parentItem = static_cast<DataWrapper*>(parent.internalPointer());
    return createIndex(row, column, parentItem->children.value(row));*/

}

QModelIndex LectureModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
    if(!index.isValid())
    {
        return QModelIndex();
    }
    DataWrapper *childItem = static_cast<DataWrapper*>(index.internalPointer());
    DataWrapper *parentItem = childItem->parent;

    if(parentItem == root)
    {
        return QModelIndex();
    }

    if(parentItem->parent)
    {
        return createIndex(parentItem->number, 0, parentItem);
    }
    else
    {
        return createIndex(0, 0, parentItem);
    }
}

int LectureModel::rowCount(const QModelIndex &parent) const
{
    DataWrapper *parentItem;
    /*if(parent.column() > 0)
    {
        return 0;
    }*/
    if (!parent.isValid())
    {
        parentItem = root;
    }
    else
    {
        parentItem = static_cast<DataWrapper*>(parent.internalPointer());
    }

    return parentItem->children.count();
}

int LectureModel::columnCount(const QModelIndex &parent) const
{

    return 1;
}

QVariant LectureModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }
    DataWrapper *item = static_cast<DataWrapper*>(index.internalPointer());
    return (item->data->name);
    // FIXME: Implement me!
    //return QVariant();
}

