#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>

Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);

    mydb = QSqlDatabase::addDatabase("QMYSQL");
    /*mydb.setHostName("pet.c33ofrzkibgh.us-east-1.rds.amazonaws.com");
    mydb.setUserName("admin");
    mydb.setPassword("gkswodnd00");*/
    mydb.setHostName("210.125.111.143");
    mydb.setUserName("root");
    mydb.setPassword("gkswodnd00");

    if(!mydb.open()){
        qDebug() << ("Failed to open the db in signup");
    }

    else{
        qDebug() << ("Connected.... in signup");
    }
}


Signup::~Signup()
{
    delete ui;
}


void Signup::on_btn_save_clicked()
{
    QString new_id, password, phone, name;
    new_id = ui->led_id->text();
    password = ui->led_pw->text();
    phone = ui->led_phone->text();
    name = ui->led_name->text();

    if(!mydb.isOpen()){
        qDebug()<<"Failed to open db";
        return ;
    }

    QSqlQuery qry1, qry2, qry3, qry4, qry5, qry6;

    if((int)new_id.isEmpty() + (int)password.isEmpty() + (int)phone.isEmpty() + (int)name.isEmpty() >= 1){
        QMessageBox::critical(this, tr("::Error::"), tr("Fill in the blank"));
        qDebug()<<"Error::Fill in the blank";
    }

    else{
        if(qry1.exec("SELECT user_id FROM login.user_info WHERE user_id = '"+new_id+"'")){
        int count = 0;

        while(qry1.next()){
            count++;
        }

        if(count == 0){
            ui->lbl_check->setText("Available");
            ui->lbl_check->setStyleSheet("QLabel { color : green }");
            if(qry2.exec("insert into login.user_info (user_id, user_pw, user_hp, user_name) VALUES (LOWER('"+new_id+"'), '"+password+"', '"+phone+"', '"+name+"')")){
                if(qry3.exec("CREATE DATABASE "+new_id+" character set = 'utf8' collate = utf8_general_ci;" )){
                    qry4.exec("USE "+new_id+";");
                    qry5.exec("CREATE TABLE "+new_id+".records(dog_name VARCHAR(45), dog_date DATETIME PRIMARY KEY, dog_symptom VARCHAR(45), dog_diagnosis VARCHAR(45), dog_prescription VARCHAR(45), hos_name VARCHAR(45), image longblob, file VARCHAR(45));" );
                    qry6.exec("CREATE TABLE "+new_id+".dogs(name VARCHAR(20) PRIMARY KEY, height VARCHAR(5), weight VARCHAR(5), dog_date VARCHAR(20), male_female VARCHAR(10));" );
                }

                QMessageBox::about(this, tr("save"), tr("Saved"));
                qDebug()<<"Saved signup data";
                mydb.close();
                mydb.removeDatabase(QSqlDatabase::defaultConnection);
                this->hide();
            }

            else{
                QMessageBox::critical(this, tr("::Error::"), tr("Unexpected Error"));
                qDebug()<<"Error::Unexpected";
            }
        }

        else{
                ui->lbl_check->setText("Already in use");
                ui->lbl_check->setStyleSheet("QLabel { color : red }");
                qDebug()<<"Error::Alreay in use";
            }
        }
    }
}
