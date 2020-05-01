#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlQuery>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>

#include "dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class field {
public :
   QString name = "", text = "";
   int cost = 0, type;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase db;
    QSqlQuery query;

    bool db_open();
    void change_table(int, QString);
    void change_fields(int ch = -1);
    void count_cost();
    void load();

private slots:
    void on_btn_open_triggered();
    void on_btn_create_triggered();
    void on_btn_add_triggered();
    void on_c1_currentIndexChanged(int index);
    void on_c2_currentIndexChanged(int index);
    void on_c3_currentIndexChanged(int index);
    void on_c4_currentIndexChanged(int index);
    void on_c5_currentIndexChanged(int index);
    void on_c6_currentIndexChanged(int index);
    void on_c7_currentIndexChanged(int index);
    void on_c8_currentIndexChanged(int index);

    void on_btn_about_triggered();

    void on_btn_info_triggered();

private:
    Ui::MainWindow *ui;
    QList <field> items;
    QStringList headers = {"Материнська плата","Процесор", "Відео карта", "Модуль пам'яті", "HDD/SSD", "Блок живлення", "Охолодежння", "Корпус", "Всього"};
};
#endif // MAINWINDOW_H
