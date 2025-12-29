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
void MainWindow::closeEvent(QCloseEvent *event)//通过参数event来控制参数是否让窗口关闭
{

}

void MainWindow::updateMenus()//更新菜单
{

}

void MainWindow::updateWindowMenus()//更新窗口菜单
{

}

MyCHILD *MainWindow::createMyCHILD()
{
    MyCHILD *child= new MyCHILD;
    return child;
}
void MainWindow::createActions()//创建菜单操作(动作)
{

}
void MainWindow::createMenus()//创建菜单
{

}
void MainWindow::createToolBars()//创建工具条
{

}
void MainWindow::createStatusBars()//创建状态条
{

}
