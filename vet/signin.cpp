#include "signin.h"
#include "ui_signin.h"

Signin::Signin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signin)
{
    ui->setupUi(this);
}

Signin::~Signin()
{
    delete ui;
}

void Signin::on_btn_signin_clicked()
{
    mydb = QSqlDatabase::addDatabase("QMYSQL");
    mydb.setHostName("210.125.111.143");
    mydb.setUserName("root");
    mydb.setPort(3306);
    mydb.setPassword("gkswodnd00");

    /*mydb = QSqlDatabase::addDatabase("QMYSQL");
    mydb.setHostName("pet.c33ofrzkibgh.us-east-1.rds.amazonaws.com");
    mydb.setUserName("admin");
    mydb.setPassword("gkswodnd00");*/

    if(!mydb.open()){
        qDebug() << ("Failed to open the db in btn_signin");
    }
    else{
        qDebug() << ("Connected....");
    }

    QString id, pw;
    id = ui->le_id->text();
    pw = ui->le_pw->text();

    if(!mydb.isOpen()){
        qDebug()<<"Failed to open db";
        return ;
    }

    QSqlQuery qry;

    if(qry.exec("select * from login.hos_user where hos_id = '"+id+"' and hos_pw = '"+pw+"'")){
        int count = 0;
        while(qry.next()){
            count++;
        }
        if(count == 1){
            ui->lb_cor_wro->setText("Welcome back:)");
            search = new Search;
            connect(this, SIGNAL(Send(QString)), search, SLOT(Receive(QString)));
            emit Send(id);
            mydb.close();
            mydb.removeDatabase(QSqlDatabase::defaultConnection);
            this->hide();
            search = new Search(this);
            search->show();
        }
        else
            ui->lb_cor_wro->setText("Incorrect ID and PW:(");
    }
}

void Signin::on_btn_signup_clicked()
{
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
    Signup signup;
    signup.setModal(true);
    signup.exec();
}
