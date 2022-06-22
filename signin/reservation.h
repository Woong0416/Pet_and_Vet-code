#ifndef RESERVATION_H
#define RESERVATION_H

#include <QDialog>

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QFileInfo>


namespace Ui {
class Reservation;
}

class Reservation : public QDialog
{
    Q_OBJECT

public:
    explicit Reservation(QWidget *parent = nullptr);
    ~Reservation();


private slots:

    void on_cbx_province_currentTextChanged(const QString &arg1);

    void on_cbx_city_currentTextChanged();

    void on_tableView_clicked(const QModelIndex &index);

    void on_btn_reservation_clicked();

    void Receive(QString iddata);

private:
    Ui::Reservation *ui;
    QSqlDatabase mydb;

};


#endif // RESERVATION_H
