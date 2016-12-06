#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QtSql>


class DataBaseHandler
{
private:
    QSqlDatabase    dataBase;
    QString         dbName;
    bool            errorFlag;

    void        ConnectDataBase();      //подключение базы данных

public:
    DataBaseHandler(QString name);
    ~DataBaseHandler();


    bool        getErrorFlag();

    //Получение имени таблицы
    QString     getDbName();

    // Возвращает количество строк таблицы,
    // имеющих заданный parentId в соотвтствующем столбце
    int         getRowCountOfChild(int parentId, int type);

    //Печать таблиц
    void        printSubjects_and_themes();
    void        printPictures_info();

};

#endif // DATABASEHANDLER_H
