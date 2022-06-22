#ifndef SIGNIN_H
#define SIGNIN_H

#include <QMainWindow>

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QFileInfo>

#include "signup.h"
#include "home.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Signin; }
QT_END_NAMESPACE

class Signin : public QMainWindow
{
    Q_OBJECT

public:
    Signin(QWidget *parent = nullptr);
    ~Signin();

private slots:
    void on_btn_signin_clicked();

    void on_btn_signup_clicked();

private:
    Ui::Signin *ui;
    QSqlDatabase mydb;
    Home *home;

signals:
    void Send(QString iddata);
};
#endif // SIGNIN_H
