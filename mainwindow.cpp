#include "mainwindow.h"
#include "ui_mainwindow.h"
//统一图标来源,主要目的是为了方便
const QString srcpaths=":/new/prefix1/images";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mdiArea=new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    setCentralWidget(mdiArea);

    connect(mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(updateMenus()));
    windowMapper=new QSignalMapper(this);
    connect(windowMapper,SIGNAL(mappped(QWidget*)),this,SLOT(setActiveSubWindow(QWidget*)));

    createActions();//创建菜单操作(动作)

    ui->setupUi(this);
    move(500,500);
    resize(900,600);
    setWindowTitle("Office办公自动化编辑软件 V2.1");
    setUnifiedTitleAndToolBarOnMac(true);
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
    //<文件>菜单动作
    //新建
    newAct=new QAction(QIcon(srcpaths+"/filenew.pgn"),tr("新建(&N)"),this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setToolTip("新建");//设置工具栏按扭的提示文本信息
    newAct->setStatusTip(tr("创建一个新的word文档"));//设置装填栏提示文本信息
    connect(newAct,SIGNAL(triggered()),this,SLOT(fileNew()));

    //打开
    openAct=new QAction(QIcon(srcpaths+"fileopen.pgn"),tr("打开(&O)"),this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setToolTip("打开");
    openAct->setStatusTip(tr("打开已经存在的word文档"));
    connect(openAct,&QAction::triggered,this,&MainWindow::fileOpen);

    //保存
    saveAct=new QAction(QIcon(srcpaths+"filesave.pgn"),tr("保存(&S)"),this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setToolTip("保存");
    saveAct->setStatusTip(tr("将当前word文档存盘"));
    connect(saveAct,&QAction::triggered,this,&MainWindow::fileSave);

    //另存为
    saveAsAct=new QAction(tr("另存为(&A)..."),this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    saveAsAct->setStatusTip("将此文件以另一种文件名称保存");
    connect(saveAsAct,&QAction::trigger,this,&MainWindow::fileSaveAS);

    //打印
    printAct=new QAction(QIcon(srcpaths+"fileprint.pgn"),tr("保存(&P)"),this);
    printAct->setShortcut(QKeySequence::Print);
    printAct->setToolTip("打印");
    printAct->setStatusTip(tr("打印一个word文档"));
    connect(printAct,&QAction::triggered,this,&MainWindow::filePrint);

    //打印预览
    printPreviewAct=new QAction(tr("打印预览..."),this);
    printPreviewAct->setStatusTip(tr("打印预览当前word文档效果"));
    connect(printPreviewAct,&QAction::triggered,this,&MainWindow::filePrintPreview);

    //<编辑>菜单动作
    //撤销
    undoAct=new QAction(QIcon(srcpaths+"editundo.png"),tr("撤销(&Z)"),this);
    undoAct->setShortcut(QKeySequence::Undo);
    undoAct->setToolTip("撤销");
    undoAct->setStatusTip(tr("撤销此前动作"));
    connect(undoAct,&QAction::triggered,this,&MainWindow::undo);

    //复制
    copyAct=new QAction(QIcon(srcpaths+"editcopy.png"),tr("复制(&C)"),this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setToolTip("复制");
    copyAct->setStatusTip(tr("复制当前选中字段"));
    connect(copyAct,&QAction::triggered,this,&MainWindow::copy);

    //剪切
    cutAct=new QAction(QIcon(srcpaths+"editcut.png"),tr("剪切(&X)"),this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setToolTip("剪切");
    cutAct->setStatusTip(tr("剪切当前选中字段"));
    connect(cutAct,&QAction::triggered,this,&MainWindow::cut);

    //粘贴
    pasteAct=new QAction(QIcon(srcpaths+"editpaste.png"),tr("粘贴(&V)"),this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setToolTip("粘贴");
    pasteAct->setStatusTip(tr("粘贴所选中的字段"));
    connect(pasteAct,&QAction::triggered,this,&MainWindow::paste);

    //重做
    redoAct=new QAction(QIcon(srcpaths+"eidtredo.png"),tr("重做(&Y)"),this);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setToolTip("重做");
    redoAct->setStatusTip(tr("重做此前动作"));
    connect(redoAct,&QAction::triggered,this,&MainWindow::redo);

    //<格式>-->字体菜单动作
    //加粗
    boldAct=new QAction(QIcon(srcpaths+"textbold,png"),tr("加粗(&B)"),this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(Qt::CTRL +Qt::Key_B);
    boldAct->setToolTip("加粗");
    boldAct->setStatusTip(tr("加粗选中文本字体"));
    QFont bold;
    bold.setBold(true);
    boldAct->setFont(bold);
    connect(boldAct,&QAction::triggered,this,&MainWindow::textBold);

    //倾斜
    italicAct=new QAction(QIcon(srcpaths+"textitalic.png"),tr("倾斜(&I)"),this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(Qt::CTRL +Qt::Key_I);
    italicAct->setToolTip("倾斜");
    italicAct->setStatusTip(tr("倾斜所选中文本字体"));
    QFont italic;
    italic.setItalic(true);
    italicAct->setFont(italic);
    connect(italicAct,&QAction::triggered,this,&MainWindow::textItalic);

    //下划线
    underlineAct=new QAction(QIcon(srcpaths+"textunder.png"),tr("下划线(&U)"),this);
    underlineAct->setCheckable(true);
    underlineAct->setShortcut(Qt::CTRL +Qt::Key_U);
    underlineAct->setToolTip("下划线");
    underlineAct->setStatusTip(tr("添加下划线所选中文本字体"));
    QFont underline;
    underline.setUnderline(true);
    underlineAct->setFont(underline);
    connect(underlineAct,&QAction::triggered,this,&MainWindow::textUnderline);

    //<格式>-->段落菜单动作
    //居中
    centerAct=new QAction(QIcon(srcpaths+"textcenter.png"),tr("水平居中"),this);
    centerAct;
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
