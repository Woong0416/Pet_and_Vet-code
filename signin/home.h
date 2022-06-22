#ifndef HOME_H
#define HOME_H

#include <QDialog>

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QFileInfo>

#include "add.h"
#include "reservation.h"
#include "signup.h"
#include "dialog.h"

namespace Ui {
class Home;
}

class Home : public QDialog
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();


private slots:
    void on_btn_create_new_clicked();

    void on_cbx_dogname_activated();

    void on_btn_reload_clicked();

    void on_btn_reservation_clicked();

    void Receive(QString iddata);

    void on_tb_record_doubleClicked(const QModelIndex &index);

private:
    Ui::Home *ui;
    QSqlDatabase mydb;
    Reservation *reseVatioin;
    Add *aDD;
    Dialog *dialog;

signals:
    void Send(QString iddata);

};

#endif // HOME_H
