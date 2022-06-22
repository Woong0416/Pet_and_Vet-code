#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QFileInfo>

#include "search.h"
#include "signup.h"

namespace Ui {
class Signin;
}

class Signin : public QDialog
{
    Q_OBJECT

public:
    explicit Signin(QWidget *parent = nullptr);
    ~Signin();

private slots:
    void on_btn_signin_clicked();

    void on_btn_signup_clicked();

private:
    Ui::Signin *ui;
    Search *search;
    QSqlDatabase mydb;

signals:
    void Send(QString iddata);
};

#endif // SIGNIN_H
