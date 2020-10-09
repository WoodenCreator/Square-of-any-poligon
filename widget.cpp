#include "widget.h"
#include "./ui_widget.h"
#include <math.h>

Widget::Widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_close_clicked()
{
    qApp->exit();
}

void Widget::on_pushButton_start_clicked()
{
    ui->table->setRowCount(0);
    int count = ui->lineEdit_point->text().toInt();
    ui->table->setRowCount(count);
    for (int i = 0;i < count; i++)
    {
        for (int j = 0; j < 2; j++)
        {
        ui->table->setItem(i,j, new QTableWidgetItem("0")); // функия ставит текст в элементы таблицы
        }
    }
}


double side(double ax,double bx,double ay,double by)
{
return sqrt((bx-ax)*(bx-ax)+(by-ay)*(by-ay));
}


//Расчёт С помощью деления на треугольники
void Widget::on_pushButton_cnt_clicked()
{
    int colCount = ui->table->columnCount();
    int rowCount = ui->table->rowCount();
    double mass[rowCount][colCount];

    for (int c = 0; c < colCount; c++)
    {
        for (int r =0; r < rowCount; r++)
        {
            QTableWidgetItem* item =ui->table->item(r, c);
            if (!item){
                continue;
        }
            double value = item->text().toDouble();
            mass[r][c] = value;
        }
    }

    //рассчёт площади и периметра треугольника (с помощью добавления вершины)
    double a,b,c, P = 0,S = 0;
    double P_res = 0, Np_res, c_del;
    double x1 = 0,y1 = 0; // координаты для новой точки
     // запоминаем первую точку
     double Ns = 0; // площадь и периметр добавочного треугольника
     double last_x =0 , last_y = 0;  // запоминаем последнюю точку
    if (rowCount == 1)
    {
        ui->label_per->setText(QString::number(P));
        ui->label_square->setText(QString::number(S));
    }
    else if (rowCount == 2)
    {
        a = side(mass[0][0],mass[1][0],mass[0][1],mass[1][1]);
        P_res = a;
        S=0;
    }
    else if (rowCount >= 3)
    {
        if (rowCount == 3)
        {
            a = side(mass[0][0],mass[1][0],mass[0][1],mass[1][1]);
            b = side(mass[1][0],mass[2][0],mass[1][1],mass[2][1]);
            c = side(mass[2][0],mass[0][0],mass[2][1],mass[0][1]);
            P_res = (a+b+c);
            P = (a+b+c)/2;
            S=sqrt(P*(P-a)*(P-b)*(P-c));
        }
        else if (rowCount >3)
        {
             a = side(mass[0][0],mass[1][0],mass[0][1],mass[1][1]);
             b = side(mass[1][0],mass[2][0],mass[1][1],mass[2][1]);
             c = side(mass[2][0],mass[0][0],mass[2][1],mass[0][1]);
             P_res = (a+b+c);
             P = (a+b+c)/2;
             S=sqrt(P*(P-a)*(P-b)*(P-c));
             for(int i = 3; i < rowCount; i++)
             {
               c_del = c;
               last_x = mass[i-1][0];
               last_y = mass[i-1][1];
               x1 = mass[i][0]; // новая точка
               y1 = mass[i][1];
               a = side(mass[0][0],x1,mass[0][1],y1);
               b = side(x1,last_x,y1,last_y);
               c = side(last_x ,mass[0][0],last_y,mass[0][1]);
               P = (a+b+c)/2;
               Np_res = b+a;
               Ns=sqrt(P*(P-a)*(P-b)*(P-c));
               P_res+=Np_res-c_del;
               S+=Ns;
             }
        }
    }
    ui->label_per->setText(QString::number(P_res));
    ui->label_square->setText(QString::number(S));
}


//рассчёт площади и периметра треугольника (с помощью формулы Гаусса)
/*void Widget::on_pushButton_cnt_clicked()
{
    int colCount = ui->table->columnCount();
    int rowCount = ui->table->rowCount();
    int mass[rowCount][colCount];

    for (int c = 0; c < colCount; c++)
    {
        for (int r =0; r < rowCount; r++)
        {
            QTableWidgetItem* item =ui->table->item(r, c);
            if (!item){
                continue;
        }
            int value = item->text().toInt();
            mass[r][c] = value;
        }
    }
    double S = 0;
    double P = 0, PP;

    for (int i = 0; i < rowCount-1; ++i)
         S += sqrt((mass[i][0] - mass[i+1][0])*(mass[i][0] - mass[i+1][0]) + (mass[i][1] - mass[i+1][1])*(mass[i][1] - mass[i+1][1]));
    S += sqrt((mass[0][0] - mass[rowCount-1][0])*(mass[0][0] - mass[rowCount-1][0]) + (mass[0][1] - mass[rowCount-1][1])*(mass[0][1] - mass[rowCount-1][1]));
    for (int g = 0; g < rowCount-1; g++)
    {
        P += sqrt((mass[g+1][0]-mass[g][0])*(mass[g+1][0]-mass[g][0])+(mass[g+1][1]-mass[g][1])*(mass[g+1][1]-mass[g][1]));
    }
    PP= P/2;
    ui->label_square->setText(QString::number(S));
    ui->label_per->setText(QString::number(PP));
}*/

void Widget::on_pushButton_add_clicked()
{
    int count = ui->table->rowCount();
    ui->table->setRowCount(++count);
    for (int i = count-1;i < count; i++)
    {
        for (int j = 0; j < 2; j++)
        {
        ui->table->setItem(i,j, new QTableWidgetItem("0")); // функия ставит текст в элементы таблицы
        }
    }
}

void Widget::on_pushButton_del_clicked()
{
    int row = ui->table->currentRow();
    ui->table->removeRow(row);
}

void Widget::on_pushButton_del_one_clicked()
{
    int count = ui->table->rowCount();
    ui->table->model()->removeRow(count-1, ui->table->rootIndex());
}
