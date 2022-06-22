#include "form.h"
#include "ui_form.h"

QString g_id_filename;

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    mydb = QSqlDatabase::addDatabase("QMYSQL");
    mydb.setHostName("210.125.111.143");
    mydb.setUserName("root");
    mydb.setPort(3306);
    mydb.setPassword("gkswodnd00");

    if(!mydb.open()){
        qDebug() << ("Failed to open the db in dialog");
    }

    else{
        qDebug() << ("Connected.... in dialog");
    }


    QString id, filename;
    id = g_id_filename.split(".").value(0);
    filename = g_id_filename.split(".").value(1);

    QSqlQuery qry;

    qry.prepare("SELECT image FROM "+id+".records WHERE file = '"+filename+"'");
    qry.exec();
    QPixmap pixmap;
    while(qry.next()){
        pixmap.loadFromData(qry.value(0).toByteArray());

        ui->lb_image->setPixmap(pixmap);

        qDebug()<<pixmap;
    }
    qry.finish();
}

Form::~Form()
{
    delete ui;
}

void Form::Receive(QString id_filename)
{
    qDebug() << id_filename;
    g_id_filename = id_filename;
}
