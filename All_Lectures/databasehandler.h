#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QtSql>


class DataBaseHandler
{
private:
    QSqlDatabase    dataBase;
    QString         dbName;
    bool            errorFlag;

public:
    DataBaseHandler();
    void        ConnectDataBase(QString name);      //подключение базы данных

    bool        getErrorFlag();
    QString     getDbName();
    int         getRowCountS_and_t();//количество строк Subjects_and_themes

    void        printSubjects_and_themes();
    void        printPictures_info();

};

#endif // DATABASEHANDLER_H
