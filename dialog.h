#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QString>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    Dialog(QSqlQuery, QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btn_add_clicked();

private:
    Ui::Dialog *ui;
    QSqlQuery query;
};

#endif // DIALOG_H
