#include <QApplication>
#include <QQmlApplicationEngine>
//#include <sqlite3.h>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql>
#include <QTreeView>
#include <QtGui>
#include "databasehandler.h"
#include "lecturemodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //DataBaseHandler testhand;
    //testhand.printSubjects_and_themes();

    /*QString str_insert = "INSERT INTO my_table(number, address, age) "
                         "VALUES (%1, '%2', %3);";
    str = str_insert.arg("14")
                    .arg("hello world str.")
                    .arg("37");
    b = a_query.exec(str);
    if (!b) {
        qDebug() << "Кажется данные не вставляются, проверьте дверь, может она закрыта?";
    }*/


    /*QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));*/

    LectureModel model;
    QTreeView view;
    view.setModel(&model);
    view.setWindowTitle("Tree model");
    view.show();

    return app.exec();
}
