#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,600);
    setWindowTitle("Office办公自动化编辑软件 V2.1");
}

MainWindow::~MainWindow()
{
    delete ui;
}

