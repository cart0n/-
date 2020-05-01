#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    //ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->setHorizontalHeaderLabels(headers);  //встановлюєм заголовки таблиці
    //ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);  //забороняєм редагування таблиці

    //    ui->table->resizeColumnsToContents();           //підганяєм розміри стовпця
}

MainWindow::~MainWindow()
{
    delete ui;
}


// function if db open
bool MainWindow::db_open(){
    if (db.open())
        return true;
    else QMessageBox::warning(0, "error", "База даних не відкрита\nФайл->Відкрити базу даних");
    return false;
}

void MainWindow::on_btn_open_triggered()
{
    QString path_to_db = QFileDialog::getOpenFileName(this,tr("Open db file"), "database", tr("db files (*.db)"));

    if(db.open())
    {
        db.close();
        query.clear();
    }
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path_to_db);

    if (db_open())
    {
        query = QSqlQuery(db);

        bool needed_db = false;
        for (const QString &tableName : db.tables())
        {
            if (tableName == "pk")
            {   needed_db = true; break; }
        }
        if (!needed_db)
            QMessageBox::warning(0, "error", "db файл не містить потрібних таблиць.");
        else {
            load();
        }
    } else
    {
        QMessageBox::warning(0, "error", "db файл не було відкрито");
    }
}


void MainWindow::change_fields(int ch)
{
    QList<field>::const_iterator i;

    for (i = items.begin(); i != items.end(); ++i)
    {
        if (i->type == ch)
        {
            switch (ch) {
            case 0: {
                if (ui->c1->currentText() == i->name) {
                    ui->p1->setText(QString::number(i->cost));
                    ui->t1->setText(i->text);
                }
                break;
            }
            case 1: {
                if (ui->c2->currentText() == i->name) {
                    ui->p2->setText(QString::number(i->cost));
                    ui->t2->setText(i->text);
                }break;
            }
            case 2: {
                if (ui->c3->currentText() == i->name) {
                    ui->p3->setText(QString::number(i->cost));
                    ui->t3->setText(i->text);}
                break;
            }
            case 3: {
                if (ui->c4->currentText() == i->name) {
                    ui->p4->setText(QString::number(i->cost));
                    ui->t4->setText(i->text);}
                break;
            }
            case 4: {
                if (ui->c5->currentText() == i->name) {
                    ui->p5->setText(QString::number(i->cost));
                    ui->t5->setText(i->text);
                }
                break;
            }
            case 5: {
                if (ui->c6->currentText() == i->name) {
                    ui->p6->setText(QString::number(i->cost));
                    ui->t6->setText(i->text);
                }
                break;
            }
            case 6: {
                if (ui->c7->currentText() == i->name) {
                    ui->p7->setText(QString::number(i->cost));
                    ui->t7->setText(i->text);
                }
                break;
            }
            case 7: {
                if (ui->c8->currentText() == i->name) {
                    ui->p8->setText(QString::number(i->cost));
                    ui->t8->setText(i->text);
                }
                break;
            }
            default: qDebug() << "Error...";
            }
        }
    }
}

void MainWindow::change_table(int ch, QString sel_name)
{
    QList<field>::const_iterator i;

    for (i = items.begin(); i != items.end(); ++i)
    {
        if (i->type == ch && i->name == sel_name)
        {
            ui->table->setItem(0,ch,new QTableWidgetItem(sel_name));
            ui->table->setItem(1,ch,new QTableWidgetItem(QString::number(i->cost)));
            break;
        }
    }
    count_cost();
}

void MainWindow::count_cost(){
    int cost =   ui->table->model()->index(1,0).data().toInt() +
            ui->table->model()->index(1,1).data().toInt() +
            ui->table->model()->index(1,2).data().toInt() +
            ui->table->model()->index(1,3).data().toInt() +
            ui->table->model()->index(1,4).data().toInt() +
            ui->table->model()->index(1,5).data().toInt() +
            ui->table->model()->index(1,6).data().toInt() +
            ui->table->model()->index(1,7).data().toInt();
    ui->table->setItem(1,8,new QTableWidgetItem(QString::number(cost)));
}

void MainWindow::load()
{
    items.clear();
    ui->c1->clear();
    ui->c2->clear();
    ui->c3->clear();
    ui->c4->clear();
    ui->c5->clear();
    ui->c6->clear();
    ui->c7->clear();
    ui->c8->clear();


    query.exec("SELECT * from pk");

    field f;

    while(query.next())
    {
        f.name = query.value(1).toString();
        f.cost = query.value(2).toInt();
        f.text = query.value(4).toString();
        f.type = query.value(3).toInt();

        switch (f.type) {
        case 0: ui->c1->addItem(f.name); break;
        case 1: ui->c2->addItem(f.name); break;
        case 2: ui->c3->addItem(f.name); break;
        case 3: ui->c4->addItem(f.name); break;
        case 4: ui->c5->addItem(f.name); break;
        case 5: ui->c6->addItem(f.name); break;
        case 6: ui->c7->addItem(f.name); break;
        case 7: ui->c8->addItem(f.name); break;
        }
        items.push_back(f);
    }

    for (int i = 0; i < 8; i++)
        change_fields(i);
}

void MainWindow::on_btn_create_triggered()
{
    // save dialog
    QString path_to_db = QFileDialog::getSaveFileName(nullptr, "Crete file", ".", "Бази даних (*.db)" );

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path_to_db);

    if (db_open())
    {
        query = QSqlQuery(db);
        query.exec("CREATE TABLE pk ( id INTEGER PRIMARY KEY AUTOINCREMENT, name NVARCHAR(100), cost INTEGER, type INTEGER, text NVARCHAR(500));");
        query.exec("INSERT INTO pk (name,cost, type, text) VALUES (' ', 0 , 0 , ' '),(' ', 0 , 1 , ' '),(' ', 0 , 2 , ' '),(' ', 0 , 3 , ' '),(' ', 0 , 4 , ' '),(' ', 0 , 5 , ' '),(' ', 0 , 6 , ' '),(' ', 0 , 7 , ' ');");
    }
}

void MainWindow::on_btn_add_triggered()
{
    if (db_open())
    {
        Dialog *d = new Dialog(query);
        d->setModal(true);
        d->show();
        d->exec();

        load();
    }
}

void MainWindow::on_c1_currentIndexChanged(int index)
{
    change_fields(0);
    change_table(0, ui->c1->currentText());
}

void MainWindow::on_c2_currentIndexChanged(int index)
{
    change_fields(1);
    change_table(1, ui->c2->currentText());
}

void MainWindow::on_c3_currentIndexChanged(int index)
{
    change_fields(2);
    change_table(2, ui->c3->currentText());
}

void MainWindow::on_c4_currentIndexChanged(int index)
{
    change_fields(3);
    change_table(3, ui->c4->currentText());
}

void MainWindow::on_c5_currentIndexChanged(int index)
{
    change_fields(4);
    change_table(4, ui->c5->currentText());
}

void MainWindow::on_c6_currentIndexChanged(int index)
{
    change_fields(5);
    change_table(5, ui->c6->currentText());
}

void MainWindow::on_c7_currentIndexChanged(int index)
{
    change_fields(6);
    change_table(6, ui->c7->currentText());
}

void MainWindow::on_c8_currentIndexChanged(int index)
{
    change_fields(7);
    change_table(7, ui->c8->currentText());
}

void MainWindow::on_btn_about_triggered()
{
    QMessageBox::about(0, "Info", "Програму написав для курсового проекту\nна тему: \"Розробка програми розрахунку вартості персонального комп'ютера\"\nіз системного програмування\nстудент групи КІ-406\nЗалісковий Юрій Ігорович\n2020р");
}


void MainWindow::on_btn_info_triggered()
{
    QMessageBox::about(0, "Info", "Перед початком використання необхідно відкрити або створити файл з якого буде здійснюватись читання\n -Ctrl + O або Файл -> Відкрити файл для відкриття файлу\n -Ctrl + N або Файл -> Створити файл для створення файлу\nДля того щоб додати комплектуючий (тільки якщо файл відкрито) потрібно:\n 1) Використати меню Комплектуючі -> Додати Комплектуючі або натиснути Ctrl+ Shift + N;\n 2) Заповнити всі поля на сторінці, що з'явиться(поле Ціна повинне бути цілочисельним);\n 3) Натиснути кнопку Додати.\nДля підрахунку вартості ПК потрібно у потрібних вкладках з комплектуючими вибрати потрібний і у випадаючому меню необхідно вибрати назву деталі\n У  правому верхньому куті з'явиться ціна конкретного елемента, а в таблиці знизу програми - ціни всіх комплектуючих і їх сума. Опис кожної деталі відображений у великій панелі по середині вікна.");

}
