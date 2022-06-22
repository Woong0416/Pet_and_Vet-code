#include "search.h"
#include "ui_search.h"

#include <QMessageBox>


QString g_hos_id, g_user_id, g_dog_name;

void Search::Receive(QString iddata)
{
    qDebug() << iddata;
    g_hos_id = iddata;
}

Search::Search(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Search)
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
        qDebug() << ("Failed to open the db in search");
    }
    else{
        qDebug() << ("Connected.... in search");
    }

    QDate today;
    QTime time;
    today = today.currentDate();
    time = time.currentTime();
    ui->lb_date->setText(today.toString());
    ui->lb_time->setText(time.toString());

    /*QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT hos_name FROM login.hos_user WHERE hos_id = '"+p+"'");
    ui->lb_hos_name->setText(model);*/

    QSqlQuery qry1;
    QString hosname;

    qry1.prepare("SELECT hos_name FROM login.hos_user WHERE hos_id = '"+g_hos_id+"'");
    qry1.exec();
    qry1.first();
    hosname = qry1.value(0).toString();
    ui->lb_hos_name->setText(hosname);

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT host_name, host_phone, pet, DATE_FORMAT(time_reservation, '%c.%e %H:%i'), DATE_FORMAT(time_visit, '%c.%e %H:%i'), symptom FROM "+g_hos_id+".reservation ORDER BY time_visit ASC");
    model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Cell Phone"));
    model->setHeaderData(2, Qt::Horizontal, tr("Pet"));
    model->setHeaderData(3, Qt::Horizontal, tr("Reservation"));
    model->setHeaderData(4, Qt::Horizontal, tr("Visit"));
    model->setHeaderData(5, Qt::Horizontal, tr("Symptom"));
    ui->tb_reservation->setModel(model);

    ui->tb_reservation->setColumnWidth(0, 50);
    ui->tb_reservation->setColumnWidth(1, 87);
    ui->tb_reservation->setColumnWidth(2, 50);
    ui->tb_reservation->setColumnWidth(3, 82);
    ui->tb_reservation->setColumnWidth(4, 82);
    ui->tb_reservation->setColumnWidth(5, 90);
}

Search::~Search()
{
    delete ui;
}

void Search::on_btn_search_clicked()
{
    if(!mydb.isOpen()){
        qDebug()<<"Failed to connect the db, btn_searh_clicked()";
    }
    QString id = ui->le_id->text();
    QString phone = ui->le_phone->text();

    if(id.isEmpty() != 0){
        QSqlQuery qry;
        qry.prepare("SELECT user_id FROM login.user_info WHERE user_hp = '"+phone+"'");
        qry.exec();
        qry.first();

        id = qry.value(0).toString();
    }

    g_user_id = id;

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT UPPER(name) FROM "+g_user_id+".dogs");

    ui->cbx_dog->setModel(model);
}

void Search::on_cbx_dog_currentTextChanged()
{
    QString name = ui->cbx_dog->currentText();

    QSqlQuery qry;
    qry.prepare("SELECT * FROM "+g_user_id+".dogs");
    qry.exec();
    qry.first();

    ui->lb_height->setText(qry.value(1).toString());
    ui->lb_weight->setText(qry.value(2).toString());
    ui->lb_age->setText(qry.value(3).toString());
    ui->lb_male_female->setText(qry.value(4).toString());

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT DATE_FORMAT(dog_date,'%Y-%m-%d'), dog_diagnosis, dog_prescription, hos_name, file FROM "+g_user_id+".records WHERE dog_name = '"+name+"'");
    model->setHeaderData(0, Qt::Horizontal, tr("Date"));
    //model->setHeaderData(1, Qt::Horizontal, tr("Symptom"));
    model->setHeaderData(1, Qt::Horizontal, tr("Diagnosis"));
    model->setHeaderData(2, Qt::Horizontal, tr("Prescription"));
    model->setHeaderData(3, Qt::Horizontal, tr("Hospital"));
    model->setHeaderData(4, Qt::Horizontal, tr("File"));

    ui->tb_record->setModel(model);
}


void Search::on_btn_reload_clicked()
{

    // reservation
    mydb = QSqlDatabase::addDatabase("QMYSQL");
    mydb.setHostName("210.125.111.143");
    mydb.setUserName("root");
    mydb.setPort(3306);
    mydb.setPassword("gkswodnd00");

    if(!mydb.open()){
        qDebug() << ("Failed to open the db in search");
    }
    else{
        qDebug() << ("Connected.... in search");
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM "+g_hos_id+".reservation");
    model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    model->setHeaderData(1, Qt::Horizontal, tr("Cell Phone"));
    model->setHeaderData(2, Qt::Horizontal, tr("Pet Name"));
    model->setHeaderData(3, Qt::Horizontal, tr("Reservation"));
    model->setHeaderData(4, Qt::Horizontal, tr("Visit"));
    model->setHeaderData(5, Qt::Horizontal, tr("Symptom"));

    ui->tb_reservation->setColumnWidth(0, 50);
    ui->tb_reservation->setColumnWidth(1, 87);
    ui->tb_reservation->setColumnWidth(2, 50);
    ui->tb_reservation->setColumnWidth(3, 82);
    ui->tb_reservation->setColumnWidth(4, 82);
    ui->tb_reservation->setColumnWidth(5, 90);

    ui->tb_reservation->setModel(model);

    // records

    model = new QSqlQueryModel;
    model->setQuery("SELECT UPPER(name) FROM "+g_user_id+".dogs");

    ui->cbx_dog->setModel(model);

    QSqlQuery qry;
    qry.prepare("SELECT * FROM "+g_user_id+".dogs");
    qry.exec();
    qry.first();

    ui->lb_height->setText(qry.value(1).toString());
    ui->lb_weight->setText(qry.value(2).toString());
    ui->lb_age->setText(qry.value(3).toDate().toString());
    ui->lb_male_female->setText(qry.value(4).toString());

    model = new QSqlQueryModel;
    model->setQuery("SELECT DATE_FORMAT(dog_date,'%Y-%m-%d'), dog_diagnosis, dog_prescription, hos_name, file FROM "+g_user_id+".records WHERE dog_name = '"+g_dog_name+"'");
    model->setHeaderData(0, Qt::Horizontal, tr("Date"));
    //model->setHeaderData(1, Qt::Horizontal, tr("Symptom"));
    model->setHeaderData(1, Qt::Horizontal, tr("Diagnosis"));
    model->setHeaderData(2, Qt::Horizontal, tr("Prescription"));
    model->setHeaderData(3, Qt::Horizontal, tr("Hospital"));
    model->setHeaderData(4, Qt::Horizontal, tr("File"));

    ui->tb_record->setModel(model);
}


void Search::on_btn_save_clicked()
{
    QDateTime date;
    QString dog_name, disease, prescription, hos_name;

    dog_name = ui->cbx_dog->currentText();
    date = date.currentDateTime();
    disease = ui->le_disease->text();
    prescription = ui->le_prescription->text();
    hos_name = ui->lb_hos_name->text();


    QSqlQuery qry;
    if(qry.exec("INSERT INTO "+g_user_id+".records (dog_name, dog_date, dog_diagnosis, dog_prescription, hos_name) VALUES ('"+dog_name+"', '"+date.toString("yy.M.d hh:mm:ss")+"', '"+disease+"', '"+prescription+"', '"+hos_name+"') ")){
        QMessageBox::about(this, tr("save"), tr("Saved"));
    }
}

void Search::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 != "VACCINE"){
        ui->le_disease->setText("Vaccination");
        ui->le_prescription->setText(arg1);
    }
    else{
        ui->le_disease->setText("");
        ui->le_prescription->setText("");
    }
}

void Search::on_btn_add_clicked()
{
    QString filename = ui->lb_adress->text();
    QDateTime date;
    QString dog_name, disease, prescription, hos_name;

    dog_name = ui->cbx_dog->currentText();
    date = date.currentDateTime();
    disease = ui->le_disease->text();
    prescription = ui->le_prescription->text();
    hos_name = ui->lb_hos_name->text();

    QByteArray byte;
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly))
    {
        byte = file.readAll();
        file.close();
    }

    QSqlQuery query;
    query.prepare("INSERT INTO "+g_user_id+".records (dog_name, dog_date, dog_diagnosis, dog_prescription, hos_name, image, file) VALUES (:dog_name, :dog_date, :dog_diagnosis, :dog_prescription, :hos_name, :image, :file_name)");
    query.bindValue(":dog_name",dog_name);
    query.bindValue(":dog_date",date.toString("yy.M.d hh:mm:ss"));
    query.bindValue(":dog_diagnosis",disease);
    query.bindValue(":dog_prescription",prescription);
    query.bindValue(":hos_name",hos_name);
    query.bindValue(":image", byte, QSql::In | QSql::Binary);
    query.bindValue(":file_name", QDateTime::currentDateTime().toString("yyMMdd-hhmmss"));
    if(query.exec())
    {
         QMessageBox :: information(this,"Save","Data Inserted successfully", QMessageBox ::Ok);
    }
    else
    {
         QMessageBox :: critical(this,"Error","Couldn't insert data");
    }
}


void Search::on_btn_choose_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "JPG File (*.jpg);;JPGE File (*.jpge);;PNG File (*.png)"

                );

    ui->lb_adress->setText(filename);
}


void Search::on_tb_record_doubleClicked(const QModelIndex &index)
{
    QString val = ui->tb_record->model()->data(index).toString();
    if(val.length() == 13){
        QString id_filename = g_user_id.append(".").append(val);

        g_dog_name = ui->cbx_dog->currentText();

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
