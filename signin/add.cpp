#include "add.h"
#include "ui_add.h"

#include <QMessageBox>

QString g_iddata;

Add::Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);

    mydb = QSqlDatabase::addDatabase("QMYSQL");
    /*mydb.setHostName("pet.c33ofrzkibgh.us-east-1.rds.amazonaws.com");
    mydb.setUserName("admin");
    mydb.setPassword("gkswodnd00");*/
    mydb.setHostName("210.125.111.143");
    mydb.setUserName("root");
    mydb.setPort(3306);
    mydb.setPassword("gkswodnd00");

    if(!mydb.open()){
        qDebug() << ("Failed to open the db in add");
    }
    else{
        qDebug() << ("Connected.... in add");
    }
}

Add::~Add()
{
    delete ui;
}

void Add::Receive1(QString iddata)
{
    qDebug() << iddata;
    g_iddata = iddata;
}


void Add::on_btn_save_clicked()
{
    if(!mydb.isOpen()){
        qDebug()<<"Failed to open db";
        return ;
    }

    QString name, height, weight, male_female;
    QDate b_date;

    name = ui->le_name->text();
    height = ui->le_height->text();
    weight = ui->le_weight->text();
    b_date = ui->dateEdit_birth->date();
    male_female = ui->cbx_mf->currentText();

    QSqlQuery qry1, qry2;

    if((int)name.isEmpty() + (int)height.isEmpty() + (int)weight.isEmpty() >= 1){
        QMessageBox::critical(this, tr("::Error::"), tr("Fill in the blank"));
        qDebug()<<"Error::Fill in the blank";
    }

    else{
        if(qry1.exec("USE " +g_iddata+ ";")){
            if(qry2.exec("INSERT INTO "+g_iddata+".dogs (name, height, weight, dog_date, male_female) VALUES ('"+name+"', '"+height+"', '"+weight+"', '"+b_date.toString("yyyy.MM.dd")+"', '"+male_female+"')")){
                QMessageBox::about(this, tr("save"), tr("Saved"));
                mydb.close();
                mydb.removeDatabase(QSqlDatabase::defaultConnection);
            }

        else
            QMessageBox::about(this, tr("error"), tr("Error"));
        }
    }
}

