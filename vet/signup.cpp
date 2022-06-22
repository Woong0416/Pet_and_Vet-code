#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>

Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup)
{
    ui->setupUi(this);

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
        qDebug() << ("Failed to open the db in signup");
    }
    else{
        qDebug() << ("Connected.... in signup");
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT DISTINCT province FROM distin.hospital ORDER BY province ASC");
    ui->cbx_adress_province->setModel(model);
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_cbx_adress_province_currentTextChanged(const QString &arg1)
{
    QString city;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT DISTINCT city FROM distin.hospital WHERE province = '"+ arg1 +"' ORDER BY city ASC ");
    ui->cbx_adress_city->setModel(model);
    city = ui->cbx_adress_city->currentText();
}

void Signup::on_btn_signup_clicked()
{
    QString new_id, password, telephone1, telephone2, telephone3, telephone, name, adress_province, adress_city, adress_, adress;

    new_id = ui->le_id->text();
    password = ui->le_pw->text();
    name = ui->le_name->text();

    telephone1 = ui->le_telephone1->text();
    telephone2 = ui->le_telephone1->text();
    telephone3 = ui->le_telephone1->text();
    telephone = QString("%1%2%3").arg(telephone1).arg(telephone2).arg(telephone3);

    adress_province = ui->cbx_adress_province->currentText();
    adress_city = ui->cbx_adress_city->currentText();
    adress_ = ui->le_adress->text();
    adress = QString("%1%2%3%4%5").arg(adress_province).arg(" ").arg(adress_city).arg(" ").arg(adress_);

    if(!mydb.isOpen()){
        qDebug()<<"Failed to open db in signup";
        return ;
    }
    QSqlQuery qry1, qry2, qry3, qry4, qry5, qry6;

    if((int)new_id.isEmpty() + (int)password.isEmpty() + (int)name.isEmpty() + (int)telephone.isEmpty() + (int)adress.isEmpty() >= 1){
        QMessageBox::critical(this, tr("::Error::"), tr("Fill in the blank"));
        qDebug()<<"Error::Fill in the blank";
    }

    else{
        if(qry1.exec("SELECT hos_id FROM login.hos_user WHERE hos_id = '"+new_id+"'")){
            int count = 0;
            while(qry1.next()){
                count++;
            }

            if(count == 0){
                ui->lbl_check->setText("Available");
                qry2.exec("INSERT INTO login.hos_user (hos_id, hos_pw, hos_name, hos_call) VALUES ('"+new_id+"', '"+password+"', '"+name+"', '"+telephone+"')");
                qry3.exec("INSERT INTO distin.hospital (telephone, adress, name, province, city) VALUES ('"+telephone+"', '"+adress+"', '"+name+"', '"+adress_province+"', '"+adress_city+"')");
                qry4.exec("CREATE DATABASE "+new_id+" character set = 'utf8' collate = utf8_general_ci;" );
                qry5.exec("USE "+new_id+";");
                qry6.exec("CREATE TABLE "+new_id+".reservation(host_name VARCHAR(20), host_phone VARCHAR(20), pet VARCHAR(20), time_reservation DATETIME PRIMARY KEY, time_visit DATETIME, symptom VARCHAR(20));" );
                QMessageBox::about(this, tr("save"), tr("Saved"));
                mydb.close();
                mydb.removeDatabase(QSqlDatabase::defaultConnection);
                this->hide();
            }

            else{
                ui->lbl_check->setText("Already in use");
                qDebug()<<"Error::Alreay in use";
            }
        }
    }
}
