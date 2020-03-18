#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget* layouts[4];


private slots:

    void on_btn_maps_clicked();

    void on_btn_run_clicked();

    void on_btn_algorithms_clicked();

    void on_btn_configuration_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
