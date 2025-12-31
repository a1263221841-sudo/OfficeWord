#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    midArea=new QMdiArea;
    midArea->setHorizontalScrollBarPolicy(Qt::BarAsNeeded);

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
MyCHILD *MainWindow::activeMyChild()const//激活子窗口
{

}


//打开文件使用
QMdiSubWindow *MainWindow::findMyChild(const QString &filename)//设置active激活窗口
{
    return 0;
}

void MainWindow::fileNew()
{

}
void MainWindow::fileOpen()
{

}
void MainWindow::fileSave()
{

}
void MainWindow::fileSaveAS()
{

}
void MainWindow::undo()
{

}
void MainWindow::redo()
{

}
void MainWindow::cut()
{

}
void MainWindow::copy()
{

}
void MainWindow::paste()
{

}
void MainWindow::enableText()
{

}
void MainWindow::textBold()
{

}
void MainWindow::textItalic()
{

}
void MainWindow::textUnderline()
{

}
void MainWindow::textAligh(QAction *a)
{

}
void MainWindow::textStyle(int styleIndex)
{

}
void MainWindow::textFamily(const QString &f)
{

}
void MainWindow::textSize(const QString &p)
{

}
void MainWindow::textColor()
{

}
void MainWindow::fontChanged(const QFont &f)
{

}
void MainWindow::colorChanged(const QColor &c)
{

}
void MainWindow::alignmentChanged(Qt::Alignment a)
{

}

void MainWindow::filePrint()
{

}
void MainWindow::filePrintPreview()
{

}
void MainWindow::printPreview(QPrinter *printer)
{

}
void MainWindow::about()
{

}
