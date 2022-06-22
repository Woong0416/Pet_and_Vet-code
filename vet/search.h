#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>

#include <QMainWindow>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QFileInfo>

#include <QFileDialog>
#include <QPixmap>

#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Search; }
QT_END_NAMESPACE

class Search : public QMainWindow
{
    Q_OBJECT

public:
    Search(QWidget *parent = nullptr);
    ~Search();

private slots:
    void on_btn_search_clicked();

    void on_cbx_dog_currentTextChanged();

    void Receive(QString iddata);

    void on_btn_reload_clicked();

    void on_btn_save_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_btn_add_clicked();

    void on_btn_choose_clicked();

    void on_tb_record_doubleClicked(const QModelIndex &index);

private:
    Ui::Search *ui;
    QSqlDatabase mydb;
    Dialog *dialog;

signals:
    void Send(QString id_filename);

};
#endif // SEARCH_H
