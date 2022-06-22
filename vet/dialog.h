#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:

    void Receive(QString id_filename);

    void on_btn_previous_clicked();

private:
    Ui::Dialog *ui;
    QSqlDatabase mydb;
};

#endif // DIALOG_H
