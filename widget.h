#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_close_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_cnt_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_del_one_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
