#include "home.h"
#include "ui_home.h"

#include <QMessageBox>

QString p;

Home::Home(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    mydb = QSqlDatabase::addDatabase("QMYSQL");
    mydb.setHostName("210.125.111.143");
    mydb.setUserName("root");
    mydb.setPort(3306);
    mydb.setPassword("gkswodnd00");

    if(!mydb.open()){
        qDebug() << ("Failed to open the db in home");
    }

    else{
        qDebug() << ("Connected.... in home");
    }

    QSqlQuery qry1;
    qry1.exec("USE "+p+";");

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT UPPER(name) FROM "+p+".dogs");

    ui->cbx_dogname->setModel(model);

    ui->lb_loginfo->setText(p.toUpper());
}


void Home::Receive(QString iddata)
{
    qDebug() << iddata;
    p = iddata;
}


Home::~Home()
{
    delete ui;
}


void Home::on_btn_create_new_clicked()
{
    aDD = new Add;
    connect(this, SIGNAL(Send(QString)), aDD, SLOT(Receive1(QString)));
    emit Send(p);

    Add add;
    add.setModal(true);
    add.exec();
}


void Home::on_cbx_dogname_activated()
{

    /*mydb = QSqlDatabase::addDatabase("QMYSQL");
    mydb.setHostName("210.125.111.143");
    mydb.setUserName("root");
    mydb.setPort(3306);
    mydb.setPassword("gkswodnd00");

    if(!mydb.open()){
        qDebug() << ("Failed to open the db in home, on_btn_reload");
    }

    else{
        qDebug() << ("Connected.... in home, on_btn_reload");
    }*/

    QSqlQueryModel *model = new QSqlQueryModel;
    QString name = ui->cbx_dogname->currentText();

    model->setQuery("SELECT DATE_FORMAT(dog_date,'%Y-%m-%d'), dog_diagnosis, dog_prescription, hos_name, file FROM "+p.toLower()+".records WHERE dog_name = '"+name+"'");
    model->setHeaderData(0, Qt::Horizontal, tr("Date"));
    //model->setHeaderData(1, Qt::Horizontal, tr("Symptom"));
    model->setHeaderData(1, Qt::Horizontal, tr("Diagnosis"));
    model->setHeaderData(2, Qt::Horizontal, tr("Prescription"));
    model->setHeaderData(3, Qt::Horizontal, tr("Hospital"));
    model->setHeaderData(4, Qt::Horizontal, tr("File"));
    ui->tb_record->setModel(model);

    QString DA2PPL, DHPPL, CoronaVirus, KennelCough, Rabies;
    QSqlQuery qry0, qry1, qry2, qry3, qry4;
    QDate date, today;
    int nDaysDelta, delta0, delta1, delta2;

    DA2PPL = ui->lb_da2ppl->text();
    DHPPL = ui->lb_dhppl->text();
    CoronaVirus = ui->lb_coronavirus->text();
    KennelCough = ui->lb_kennelcough->text();
    Rabies = ui->lb_rabies->text();

    qry0.prepare("SELECT DATE_FORMAT(dog_date,'%Y-%m-%d') FROM "+p+".records WHERE dog_prescription = '"+DA2PPL+"' AND dog_name = '"+name+"'");
    qry0.exec();
    qry0.last();

    if(qry0.value(0).isValid()){
        date = qry0.value(0).toDate().addYears(1);
        today = today.currentDate();
        nDaysDelta = today.daysTo( date );

        ui->lb_delta0->setText( QString::number(nDaysDelta));

        if(nDaysDelta < 14){
            ui->lb_delta0->setStyleSheet("QLabel { color : red }");
        }
    }
    else{
        ui->lb_delta0->setText("No Vaccination");
        ui->lb_dayleft0->setText("");
    }

    qry1.prepare("SELECT DATE_FORMAT(dog_date,'%Y-%m-%d') FROM "+p+".records WHERE dog_prescription = '"+DHPPL+"' AND dog_name = '"+name+"'");
    qry1.exec();
    qry1.last();

    if(qry1.value(0).isValid()){
        date = qry1.value(0).toDate().addYears(1);
        today = today.currentDate();
        nDaysDelta = today.daysTo( date );

        ui->lb_delta1->setText( QString::number(nDaysDelta));
        ui->lb_dayleft1->setText("days left");

        if(nDaysDelta < 14){
            ui->lb_delta1->setStyleSheet("QLabel { color : red }");
        }
    }
    else{
        ui->lb_delta1->setText("No Vaccination");
        ui->lb_delta1->setAlignment(Qt::AlignRight);
        ui->lb_dayleft1->setText("");
    }

    qry2.prepare("SELECT DATE_FORMAT(dog_date,'%Y-%m-%d') FROM "+p+".records WHERE dog_prescription = '"+CoronaVirus+"' AND dog_name = '"+name+"'");
    qry2.exec();
    qry2.last();

    if(qry2.value(0).isValid()){
        date = qry2.value(0).toDate().addYears(1);
        today = today.currentDate();
        nDaysDelta = today.daysTo( date );

        ui->lb_delta2->setText( QString::number(nDaysDelta));
        ui->lb_dayleft2->setText("days left");

        if(nDaysDelta < 14){
            ui->lb_delta2->setStyleSheet("QLabel { color : red }");
        }
    }
    else{
        ui->lb_delta2->setText("No Vaccination");
        ui->lb_delta2->setAlignment(Qt::AlignRight);
        ui->lb_dayleft2->setText("");
    }

    qry3.prepare("SELECT DATE_FORMAT(dog_date,'%Y-%m-%d') FROM "+p+".records WHERE dog_prescription = '"+KennelCough+"' AND dog_name = '"+name+"'");
    qry3.exec();
    qry3.last();

    if(qry3.value(0).isValid()){
        date = qry3.value(0).toDate().addYears(1);
        today = today.currentDate();
        nDaysDelta = today.daysTo( date );

        ui->lb_delta3->setText( QString::number(nDaysDelta));
        ui->lb_dayleft3->setText("days left");

        if(nDaysDelta < 14){
            ui->lb_delta3->setStyleSheet("QLabel { color : red }");
        }
    }
    else{
        ui->lb_delta3->setText("No Vaccination");
        ui->lb_delta3->setAlignment(Qt::AlignRight);
        ui->lb_dayleft3->setText("");
    }


    qry4.prepare("SELECT DATE_FORMAT(dog_date,'%Y-%m-%d') FROM "+p+".records WHERE dog_prescription = '"+Rabies+"' AND dog_name = '"+name+"'");
    qry4.exec();
    qry4.last();

    if(qry4.value(0).isValid()){
        date = qry4.value(0).toDate().addMonths(6);
        today = today.currentDate();
        nDaysDelta = today.daysTo( date );

        ui->lb_delta4->setText( QString::number(nDaysDelta));
        ui->lb_dayleft4->setText("days left");

        if(nDaysDelta < 14){
            ui->lb_delta4->setStyleSheet("QLabel { color : red }");
        }
    }
    else{
        ui->lb_delta4->setText("No Vaccination");
        ui->lb_delta4->setAlignment(Qt::AlignRight);
        ui->lb_dayleft4->setText("");
    }

    QSqlQuery qry5;
    QString height, weight, b_date, m_f;
    qry5.prepare("SELECT * FROM "+p.toLower()+".dogs WHERE name = '"+name+"'");
    qry5.exec();
    qry5.first();

    //name VARCHAR(20) PRIMARY KEY, height VARCHAR(5), weight VARCHAR(5), dog_date VARCHAR(20), male_female
    ui->lb_height->setText(qry5.value(1).toString());
    ui->lb_weight->setText(qry5.value(2).toString());
    ui->lb_date->setText(qry5.value(3).toString());
    ui->lb_male_female->setText(qry5.value(4).toString());

}


void Home::on_btn_reload_clicked()
{
    mydb = QSqlDatabase::addDatabase("QMYSQL");
    mydb.setHostName("210.125.111.143");
    mydb.setUserName("root");
    mydb.setPort(3306);
    mydb.setPassword("gkswodnd00");

    if(!mydb.open()){
        qDebug() << ("Failed to open the db in home, on_btn_reload");
    }

    else{
        qDebug() << ("Connected.... in home, on_btn_reload");
    }
    p = ui->lb_loginfo->text();

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT UPPER(name) FROM "+p.toLower()+".dogs");
    ui->cbx_dogname->setModel(model);
}


void Home::on_btn_reservation_clicked()
{
    reseVatioin = new Reservation;
    connect(this, SIGNAL(Send(QString)), reseVatioin, SLOT(Receive(QString)));
    emit Send(p);
    Reservation reservation;
    reservation.setModal(true);
    reservation.exec();
}

void Home::on_tb_record_doubleClicked(const QModelIndex &index)
{
    QString val = ui->tb_record->model()->data(index).toString();
    if(val.length() == 13){
        QString id_filename = p.append(".").append(val);

        dialog = new Dialog;
        connect(this, SIGNAL(Send(QString)), dialog, SLOT(Receive(QString)));
        emit Send(id_filename);

        Dialog dialog;
        dialog.setModal(true);
        dialog.exec();
    }

    else{
        QMessageBox :: critical(this,"Error","Select file");
    }
}

