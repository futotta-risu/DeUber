#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layouts[0] = (ui->layout_map);
    layouts[1] = (ui->layout_run);
    layouts[2] = (ui->layout_algorithms);
    layouts[3] = (ui->layout_config);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btn_maps_clicked()
{
    for (int i = 0; i<4; i++)
        layouts[i]->setVisible(false);

    ui->layout_map->setVisible(true);
}

void MainWindow::on_btn_run_clicked()
{
    for (int i = 0; i<4; i++)
        layouts[i]->setVisible(false);

    ui->layout_run->setVisible(true);
}



void MainWindow::on_btn_algorithms_clicked()
{
    for (int i = 0; i<4; i++)
        layouts[i]->setVisible(false);

    ui->layout_algorithms->setVisible(true);
}

void MainWindow::on_btn_configuration_clicked()
{
    for (int i = 0; i<4; i++)
        layouts[i]->setVisible(false);

    ui->layout_config->setVisible(true);
}
