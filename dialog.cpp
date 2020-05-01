#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

//ctor with parametrs
Dialog::Dialog(QSqlQuery q, QWidget *parent ):
    QDialog(parent),
    ui(new Ui::Dialog)
{
    this->query = q;
    ui->setupUi(this);
//    query.exec("SELECT name, code, kg FROM tovar WHERE storage = '" + storage +  "';");
}


void Dialog::on_btn_add_clicked()
{
    bool ok;
    int cost = ui->cost_line->text().toInt(&ok, 10);

    if (ui->name_line->text() != "" && ui->text->toPlainText() != "" && ok)
    {
        if(query.exec("INSERT INTO pk (name,cost, type, text) VALUES ('" + ui->name_line->text() + "', " + QString::number(cost) + " , " + QString::number(ui->comboBox->currentIndex()) + " , '" + ui->text->toPlainText() + "');"))
            close();
        else QMessageBox::critical(0, "error", "Unknown error");
    } else QMessageBox::critical(0, "error", "Input error");
}
