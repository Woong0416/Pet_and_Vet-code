#include "reservation.h"

#include "ui_reservation.h"

#include <QMessageBox>

QString g_hosname, g_id, g_petname;


Reservation::Reservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reservation)
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
        qDebug() << ("Failed to open the db in reservation");
    }

    else{
        qDebug() << ("Connected.... in reservation");
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT DISTINCT province FROM distin.hospital ORDER BY province ASC");
    ui->cbx_province->setModel(model);

    model = new QSqlQueryModel;
    model->setQuery("SELECT UPPER(name) FROM "+g_id+".dogs");

    ui->cbx_petname->setModel(model);
    g_petname = ui->cbx_petname->currentText();

    ui->label_2->setText(g_id);
    ui->dateEdit->setDate(QDate().currentDate());
    ui->dateEdit->setMinimumDate(QDate().currentDate());
}


Reservation::~Reservation()
{
    delete ui;
}


void Reservation::Receive(QString iddata)
{
    qDebug() << iddata;
    g_id = iddata;
}


void Reservation::on_cbx_province_currentTextChanged(const QString &arg1)
{
    QString city;
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT DISTINCT city FROM distin.hospital WHERE province = '"+ arg1 +"' ORDER BY city ASC ");
    ui->cbx_city->setModel(model);
    city = ui->cbx_city->currentText();
}


void Reservation::on_cbx_city_currentTextChanged()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    //model->setQuery("SELECT name FROM distin.hospital WHERE province = '"+ui->cbx_province->currentText()+"' AND city = '"+ui->cbx_city->currentText()+"'");
    model->setQuery("SELECT name, adress, telephone FROM distin.hospital WHERE province = '"+ui->cbx_province->currentText()+"' AND city = '"+ui->cbx_city->currentText()+"' ORDER BY name ASC");
    model->setHeaderData(0, Qt::Horizontal, tr("Hospital"));
    model->setHeaderData(1, Qt::Horizontal, tr("Adress"));
    model->setHeaderData(2, Qt::Horizontal, tr("Telephone"));

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 150);
    ui->tableView->setColumnWidth(1, 415);
    ui->tableView->setColumnWidth(2, 100);
}

void Reservation::on_tableView_clicked(const QModelIndex &index)
{
    QString val = ui->tableView->model()->data(index).toString();
    QString hosname;

    QSqlQuery qry;
    qry.prepare("SELECT name FROM distin.hospital WHERE name = '"+val+"' OR adress = '"+val+"' ");
    qry.exec();
    qry.first();
    hosname = qry.value(0).toString();
    ui->lb_hos_name->setText(hosname);
    g_hosname = hosname;
}

void Reservation::on_btn_reservation_clicked()
{
    QString hos_name, host_name, host_id, host_phone, pet, symptom, time_visit, hos_id;
    QDateTime time_reservation;
    QSqlQuery qry1, qry2, qry3, qry4;

    hos_name = g_hosname;
    host_id = g_id;
    pet = g_petname;
    time_reservation = time_reservation.currentDateTime();
    time_visit = QString("%1%2%3").arg(ui->dateEdit->date().toString("yy.M.d")).arg(" ").arg(ui->cbx_visit_time->currentText());
    symptom = ui->le_symptom->text();

    qry1.prepare("SELECT user_name FROM login.user_info WHERE user_id = '"+g_id+"'");
    qry1.exec();
    qry1.first();
    host_name = qry1.value(0).toString();

    qry2.prepare("SELECT user_hp FROM login.user_info WHERE user_id = '"+g_id+"'");
    qry2.exec();
    qry2.first();
    host_phone = qry2.value(0).toString();

    qry4.prepare("SELECT hos_id FROM login.hos_user WHERE hos_name = '"+hos_name+"'");
    qry4.exec();
    qry4.first();
    hos_id = qry4.value(0).toString();

    if(symptom.isEmpty() == 0){
        qry3.prepare("INSERT INTO "+hos_id+".reservation (host_name, host_phone, time_reservation, time_visit, pet, symptom) VALUES ('"+host_name+"', '"+host_phone+"', '"+time_reservation.toString("yy.M.d H:mm:ss")+"', '"+time_visit+"', '"+pet+"', '"+symptom+"')");

        if(qry3.exec()){
            QMessageBox::about(this, tr("save"), tr("Saved"));
            qDebug()<<"Saved reservation data";
        }

        else
            qDebug() << "failed to save";
    }

    else
        QMessageBox::about(this, tr("error"), tr("fill the SYMPTOM"));
}
