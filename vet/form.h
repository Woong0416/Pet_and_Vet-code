#ifndef FORM_H
#define FORM_H

#include <QWidget>

#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:

    void Receive(QString id_filename);

private:
    Ui::Form *ui;
    QSqlDatabase mydb;
};

#endif // FORM_H
