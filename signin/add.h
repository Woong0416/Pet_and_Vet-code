#ifndef ADD_H
#define ADD_H

#include <QDialog>

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class Add;
}

class Add : public QDialog
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = nullptr);
    ~Add();

private slots:

    void on_btn_save_clicked();

    void Receive1(QString iddata);

private:
    Ui::Add *ui;
    QSqlDatabase mydb;
};

#endif // ADD_H
