#include "databasehandler.h"
#include <QDebug>

DataBaseHandler::DataBaseHandler()
{
    errorFlag = true;
    ConnectDataBase("LecturesDB");
}

DataBaseHandler::~DataBaseHandler()
{
    dataBase.close();
}


void DataBaseHandler::ConnectDataBase(QString name)
{
    dbName = name;
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
    dataBase.setDatabaseName("../LecturesDB");

    if (!dataBase.open()) {
          qDebug() << "Всё очень плохо";
          errorFlag = false;
    }
}





QString DataBaseHandler::getDbName()
{
    return dbName;
}

bool DataBaseHandler::getErrorFlag()
{
    return errorFlag;
}

int DataBaseHandler::getRowCountS_and_t()
{
    QSqlQuery quary;
    if(!quary.exec("SELECT count(*) FROM subjects_and_themes")){
        return -1;
    }
    int row_count = -2;
    if(quary.next())
        row_count = quary.value(0).toInt();
    return row_count;
}



void DataBaseHandler::printSubjects_and_themes()
{
    QSqlQuery queryOfSubjects_and_themes;
    if (!queryOfSubjects_and_themes.exec("SELECT * FROM subjects_and_themes")) {
        qDebug() << "Невозможно извлечь данные из subjects_and_themes";
        errorFlag = false;
    }
    if(errorFlag)
    {
        QSqlRecord rec = queryOfSubjects_and_themes.record();
        int id_subj = 0,
                term = 0,
                type = 0,
                serial_number = 0,
                id_parent = 0;
        QString nameSubj = "";

        qDebug() << "Id_subj"
                 << "\tTerm"
                 << "\tType"
                 << "\tName_subj"
                 << "\tSerial_number"
                 << "\tId_parent\n";
        while (queryOfSubjects_and_themes.next()) {
            id_subj = queryOfSubjects_and_themes.value(rec.indexOf("Id_subj")).toInt();
            term = queryOfSubjects_and_themes.value(rec.indexOf("Term")).toInt();
            type = queryOfSubjects_and_themes.value(rec.indexOf("Type")).toInt();
            serial_number = queryOfSubjects_and_themes.value(rec.indexOf("Serial_number")).toInt();
            id_parent = queryOfSubjects_and_themes.value(rec.indexOf("Id_parent")).toInt();
            nameSubj = queryOfSubjects_and_themes.value(rec.indexOf("Name_subj")).toString();
            qDebug() << id_subj
                     << "\t" << term
                     << "\t" << type
                     << "\t" << nameSubj
                     << "\t" << serial_number
                     << "\t\t" << id_parent<<"\n";
        }
    }
}

void DataBaseHandler::printPictures_info()
{
    QSqlQuery queryOfPictures_info;
    if (!queryOfPictures_info.exec("SELECT * FROM pictures_info")) {
        qDebug() << "Невозможно извлечь данные из pictures_info";
        errorFlag = false;
    }

    if(errorFlag)
    {
        QSqlRecord rec = queryOfPictures_info.record();
        int id_image = 0,
                type = 0;
        QString tags = "",
                comment = "",
                image_path = "";

        qDebug() << "Id_image"
                 << "\tTags"
                 << "\tComment"
                 << "\tImage_path"
                 << "\tType\n";
        while (queryOfPictures_info.next()) {
            id_image = queryOfPictures_info.value(rec.indexOf("Id_image")).toInt();
            type = queryOfPictures_info.value(rec.indexOf("Type")).toInt();
            tags = queryOfPictures_info.value(rec.indexOf("Tags")).toString();
            comment = queryOfPictures_info.value(rec.indexOf("Comment")).toString();
            image_path = queryOfPictures_info.value(rec.indexOf("Image_path")).toString();
            qDebug() << id_image
                     << "\t" << tags
                     << "\t" << comment
                     << "\t" << image_path
                     << "\t\t" << type <<"\n";
        }
    }
}
