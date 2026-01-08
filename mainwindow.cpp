#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mychild.h"
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

   //@ connect(mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(updateMenus()));
    connect(mdiArea, &QMdiArea::subWindowActivated,
            this, [this](QMdiSubWindow *) {
                updateMenus();
            });
    windowMapper=new QSignalMapper(this);
    connect(windowMapper,SIGNAL(mapped(QWidget*)),this,SLOT(setActiveSubWindow(QWidget*)));
    //connect(windowMapper,&QSignalMapper::mapped,this,&MainWindow::setActiveSubWindow);
    createActions();//创建菜单栏,工具栏,状态栏,等相关操作(动作集合)

    createMenus();//调用创建菜单实现

    createToolBars();//调用创建工具栏


    ui->setupUi(this);
   // move(500,500);
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
    mdiArea->closeAllSubWindows();
    if(mdiArea->currentSubWindow()){
        event->ignore();
    }else{
        event->accept();
    }
}

void MainWindow::updateMenus()//更新菜单
{
    bool hasmychild=(activeMyChild()!=0);

    saveAct->setEnabled(hasmychild);
    saveAsAct->setEnabled(hasmychild);
    printAct->setEnabled(hasmychild);
    printPreviewAct->setEnabled(hasmychild);
    pasteAct->setEnabled(hasmychild);

    closeAct->setEnabled(hasmychild);
    closeAllAct->setEnabled(hasmychild);
    tileAct->setEnabled(hasmychild);
    cascadeAct->setEnabled(hasmychild);
    nextAct->setEnabled(hasmychild);
    previousAct->setEnabled(hasmychild);
    separatorAct->setEnabled(hasmychild);

    bool hasSelection=(activeMyChild()&& activeMyChild()->textCursor().hasSelection());
    cutAct->setEnabled(hasmychild);
    copyAct->setEnabled(hasmychild);
    boldAct->setEnabled(hasmychild);
    italicAct->setEnabled(hasmychild);
    underlineAct->setEnabled(hasmychild);
    leftAlignAct->setEnabled(hasmychild);
    centerAct->setEnabled(hasmychild);
    rightAlignAct->setEnabled(hasmychild);
    justifyAct->setEnabled(hasmychild);
    colorAct->setEnabled(hasmychild);
}

void MainWindow::updateWindowMenu()//更新窗口菜单
{
    windowMenu->clear();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
    windowMenu->addSeparator();

    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();

    windowMenu->addAction(nextAct);
    windowMenu->addAction(previousAct);
    windowMenu->addAction(separatorAct);

    QList<QMdiSubWindow*>windows=mdiArea->subWindowList();
    separatorAct->setVisible(!windows.isEmpty());

    //显示当前打开着的文档子窗口项
    for(int i=0;i<windows.size();++i)
    {
        MyChild*child=qobject_cast<MyChild*>(windows.at(i)->widget());

        QString text;
        if(i<9){
            text=tr("&%1 %2").arg(i+1).arg(child->userFriendlyCurrentFile());
        }
    else {
        text=tr("&%1 %2").arg(i+1).arg(child->userFriendlyCurrentFile());
    }
        QAction *action=windowMenu->addAction(text);
        action->setCheckable(true);
        action->setChecked(child == activeMyChild());
        //connect(action,&QAction::triggered,this,&windowMapper::map);
        //connect(action, SIGNAL(triggered()),windowMapper, SLOT(map()));//@
        //windowMapper->setMapping(action,windows.at(i));//@
        connect(action, &QAction::triggered, this, [=]() {
            mdiArea->setActiveSubWindow(windows.at(i));

        });


}
}

MyChild *MainWindow::createMyChild()
{
    MyChild *child= new MyChild;
    mdiArea->addSubWindow(child);
    //connect(child,SIGNAL(copyAvailable(bool)),cutAct,SLOT(setEnabled(bool)));
    //connect(child,SIGNAL(copyAvailable(bool)),copyAct,SLOT(setEnabled(bool)));
    // 新语法写法：
        // connect(发送者, &发送者类::信号, 接收者, &接收者类::槽);
        connect(child, &MyChild::copyAvailable, cutAct, &QAction::setEnabled);
        connect(child, &MyChild::copyAvailable, copyAct, &QAction::setEnabled);
    // 当子窗口有文字选中时，更新主窗口的“复制/剪切”菜单状态
   //connect(child->textCursor(), &QTextCursor::selectionChanged,
                //this, &MainWindow::updateMenus);
        child->show();

    return child;
}
void MainWindow::createActions()//创建菜单操作(动作)
{
    //<文件>菜单动作
    //新建
    newAct=new QAction(QIcon(srcpaths+"/filenew.png"),tr("新建(&N)"),this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setToolTip("新建");//设置工具栏按扭的提示文本信息
    newAct->setStatusTip(tr("创建一个新的word文档"));//设置装填栏提示文本信息
    connect(newAct,&QAction::triggered,this,&MainWindow::fileNew);

    //打开
    openAct=new QAction(QIcon(srcpaths+"/fileopen.png"),tr("打开(&O)"),this);
    openAct->setShortcut(QKeySequence::Open);
    openAct->setToolTip("打开");
    openAct->setStatusTip(tr("打开已经存在的word文档"));
    connect(openAct,&QAction::triggered,this,&MainWindow::fileOpen);

    //保存
    saveAct=new QAction(QIcon(srcpaths+"/filesave.png"),tr("保存(&S)"),this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setToolTip("保存");
    saveAct->setStatusTip(tr("将当前word文档存盘"));
    connect(saveAct,&QAction::triggered,this,&MainWindow::fileSave);

    //另存为
    saveAsAct=new QAction(tr("另存为(&A)..."),this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    saveAsAct->setStatusTip("将此文件以另一种文件名称保存");
    connect(saveAsAct,&QAction::triggered,this,&MainWindow::fileSaveAS);

    //打印
    printAct=new QAction(QIcon(srcpaths+"/fileprint.png"),tr("保存(&P)"),this);
    printAct->setShortcut(QKeySequence::Print);
    printAct->setToolTip("打印");
    printAct->setStatusTip(tr("打印一个word文档"));
    connect(printAct,&QAction::triggered,this,&MainWindow::filePrint);

    //打印预览
    printPreviewAct=new QAction(tr("打印预览..."),this);
    printPreviewAct->setStatusTip(tr("打印预览当前word文档效果"));
    connect(printPreviewAct,&QAction::triggered,this,&MainWindow::filePrintPreview);

    //退出
    exitAct=new QAction(tr("退出(X)"),this);
    exitAct->setStatusTip(tr("退出当前程序"));
    connect(exitAct,&QAction::triggered,this,&MainWindow::exitAct);

    //<编辑>菜单动作
    //撤销
    undoAct=new QAction(QIcon(srcpaths+"/editundo.png"),tr("撤销(&Z)"),this);
    undoAct->setShortcut(QKeySequence::Undo);
    undoAct->setToolTip("撤销");
    undoAct->setStatusTip(tr("撤销此前动作"));
    connect(undoAct,&QAction::triggered,this,&MainWindow::undo);

    //复制
    copyAct=new QAction(QIcon(srcpaths+"/editcopy.png"),tr("复制(&C)"),this);
    copyAct->setShortcut(QKeySequence::Copy);
    copyAct->setToolTip("复制");
    copyAct->setStatusTip(tr("复制当前选中字段"));
    connect(copyAct,&QAction::triggered,this,&MainWindow::copy);

    //剪切
    cutAct=new QAction(QIcon(srcpaths+"/editcut.png"),tr("剪切(&X)"),this);
    cutAct->setShortcut(QKeySequence::Cut);
    cutAct->setToolTip("剪切");
    cutAct->setStatusTip(tr("剪切当前选中字段"));
    connect(cutAct,&QAction::triggered,this,&MainWindow::cut);

    //粘贴
    pasteAct=new QAction(QIcon(srcpaths+"/editpaste.png"),tr("粘贴(&V)"),this);
    pasteAct->setShortcut(QKeySequence::Paste);
    pasteAct->setToolTip("粘贴");
    pasteAct->setStatusTip(tr("粘贴所选中的字段"));
    connect(pasteAct,&QAction::triggered,this,&MainWindow::paste);

    //重做
    redoAct=new QAction(QIcon(srcpaths+"/editredo.png"),tr("重做(&Y)"),this);
    redoAct->setShortcut(QKeySequence::Redo);
    redoAct->setToolTip("重做");
    redoAct->setStatusTip(tr("重做此前动作"));
    connect(redoAct,&QAction::triggered,this,&MainWindow::redo);

    //<格式>-->字体菜单动作
    //加粗
    boldAct=new QAction(QIcon(srcpaths+"/textbold.png"),tr("加粗(&B)"),this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(Qt::CTRL +Qt::Key_B);
    boldAct->setToolTip("加粗");
    boldAct->setStatusTip(tr("加粗选中文本字体"));
    QFont bold;
    bold.setBold(true);
    boldAct->setFont(bold);
    connect(boldAct,&QAction::triggered,this,&MainWindow::textBold);

    //倾斜
    italicAct=new QAction(QIcon(srcpaths+"/textitalic.png"),tr("倾斜(&I)"),this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(Qt::CTRL +Qt::Key_I);
    italicAct->setToolTip("倾斜");
    italicAct->setStatusTip(tr("倾斜所选中文本字体"));
    QFont italic;
    italic.setItalic(true);
    italicAct->setFont(italic);
    connect(italicAct,&QAction::triggered,this,&MainWindow::textItalic);

    //下划线
    underlineAct=new QAction(QIcon(srcpaths+"/textunder.png"),tr("下划线(&U)"),this);
    underlineAct->setCheckable(true);
    underlineAct->setShortcut(Qt::CTRL +Qt::Key_U);
    underlineAct->setToolTip("下划线");
    underlineAct->setStatusTip(tr("添加下划线所选中文本字体"));
    QFont underline;
    underline.setUnderline(true);
    underlineAct->setFont(underline);
    connect(underlineAct,&QAction::triggered,this,&MainWindow::textUnderline);

    //<格式>-->段落菜单动作,子菜单下各项为同一个菜单项组,我们只能选择其中的一项
    //对齐
    QActionGroup *grp=new QActionGroup(this);
    //connect(grp,SINGAL(triggered(QAction*)),this,SLOT(textAlign(QAction*)));
    connect(grp,&QActionGroup::triggered,this,&MainWindow::textAlign);

    if(QApplication::isLeftToRight()){
        leftAlignAct=new QAction(QIcon(srcpaths+"/textleft.png"),tr("左对齐(&L)"),grp);
        centerAct=new QAction(QIcon(srcpaths+"/textcenter.png"),tr("居中对齐(&E)"),grp);
        rightAlignAct=new QAction(QIcon(srcpaths+"/textright.png"),tr("右对齐(&R)"),grp);
    }else
    {
       rightAlignAct=new QAction(QIcon(srcpaths+"/textright.png"),tr("右对齐(&R)"),grp);
       centerAct=new QAction(QIcon(srcpaths+"/textcenter.png"),tr("居中对齐(&E)"),grp);
       leftAlignAct=new QAction(QIcon(srcpaths+"/textleft.png"),tr("左对齐(&L)"),grp);
    }
    justifyAct=new QAction(QIcon(srcpaths+"/textjustify.png"),tr("两端对齐对齐(&J)"),grp);

    leftAlignAct->setShortcut(Qt::CTRL +Qt::Key_L);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setToolTip("左对齐");
    leftAlignAct->setStatusTip(tr("将文字进行左对齐."));

    centerAct->setShortcut(Qt::CTRL +Qt::Key_E);
    centerAct->setCheckable(true);
    centerAct->setToolTip("居中对齐");
    centerAct->setStatusTip(tr("将文字进行居中对齐."));

    rightAlignAct->setShortcut(Qt::CTRL +Qt::Key_R);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setToolTip("右对齐");
    leftAlignAct->setStatusTip(tr("将文字进行右对齐"));

    justifyAct->setShortcut(Qt::CTRL +Qt::Key_J);
    justifyAct->setCheckable(true);
    justifyAct->setToolTip("两端对齐");
    justifyAct->setStatusTip(tr("将文字进行两端对齐"));

    QPixmap pix(16,16);
    pix.fill(Qt::red);
    colorAct=new QAction(pix,tr("颜色(&C)..."),this);
    colorAct->setToolTip("颜色");
    colorAct->setStatusTip(tr("将你选择的颜色,设置成对应颜色."));
    connect(colorAct,&QAction::triggered,this,&MainWindow::textColor);

    //<窗口>菜单
    //关闭
    closeAct=new QAction(tr("关闭(&0)"),this);
    closeAct->setStatusTip(tr("关闭活动word文档子窗口."));
    connect(closeAct,&QAction::triggered,mdiArea,&QMdiArea::closeActiveSubWindow);

    closeAllAct=new QAction(tr("关闭(&A)"),this);
    closeAllAct->setStatusTip(tr("关闭所有word文档窗口"));
    connect(closeAllAct,&QAction::triggered,mdiArea,&QMdiArea::closeAllSubWindows);

    tileAct=new QAction(tr("平铺(&T)"),this);
    tileAct->setStatusTip(tr("平铺子窗口"));
    connect(tileAct,&QAction::triggered,mdiArea,&QMdiArea::tileSubWindows);

    cascadeAct=new QAction(tr("层叠(&T)"),this);
    cascadeAct->setStatusTip(tr("层叠子窗口."));
    connect(cascadeAct,&QAction::triggered,mdiArea,&QMdiArea::cascadeSubWindows);

    nextAct=new QAction(tr("下一个(&T)"),this);
    nextAct->setShortcuts(QKeySequence::NextChild);
    nextAct->setStatusTip(tr("移动焦点到下一个子窗口."));
    connect(nextAct,&QAction::triggered,mdiArea,&QMdiArea::activateNextSubWindow);

    previousAct=new QAction(tr("上一个(&T)"),this);
    previousAct->setShortcuts(QKeySequence::PreviousChild);
    previousAct->setStatusTip(tr("移动焦点到上一个子窗口."));
    connect(previousAct,&QAction::triggered,mdiArea,&QMdiArea::activatePreviousSubWindow);

    separatorAct=new QAction(this);
    separatorAct->setSeparator(true);

    //<帮助>菜单
    aboutAct=new QAction(tr("关于(&A)"),this);
    aboutAct->setStatusTip("关于Office Word相关信息.");
    connect(aboutAct,&QAction::triggered,this,&MainWindow::about);

    aboutQtAct=new QAction(tr("关于Qt(&Q)"),this);
    aboutAct->setStatusTip("关于Qt库相关信息.");
    connect(aboutQtAct,&QAction::triggered,qApp,&QApplication::aboutQt);



}
void MainWindow::createMenus()//创建菜单
{
    //文件菜单
    fileMenu=menuBar()->addMenu(tr("文件(&F)"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();//分隔符
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();//分隔符
    fileMenu->addAction(printAct);
    fileMenu->addAction(printPreviewAct);
    fileMenu->addSeparator();//分隔符

    //编辑菜单
    editMenu=menuBar()->addMenu(tr("文件(&E)"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();//分隔符
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

    //格式菜单
    formatMenu=menuBar()->addMenu(tr("格式(&O)"));
    fontMenu=menuBar()->addMenu(tr("字体(&D)"));
    fontMenu->addAction(boldAct);
    fontMenu->addAction(italicAct);
    fontMenu->addAction(underlineAct);

    alignMenu=menuBar()->addMenu(tr("段落"));//段落子菜单
    alignMenu->addAction(leftAlignAct);
    alignMenu->addAction(centerAct);
    alignMenu->addAction(rightAlignAct);
    alignMenu->addAction(justifyAct);

    formatMenu->addAction(colorAct);//颜色

    //窗口菜单
    windowMenu=menuBar()->addMenu(tr("窗口(&W)"));//窗口子菜单
    updateWindowMenu();
    connect(windowMenu,&QMenu::aboutToShow,this,&MainWindow::updateWindowMenu);
    menuBar()->addSeparator();//分隔符

    //<帮助>菜单
    helpMenu=menuBar()->addMenu(tr("帮助(&H)"));//帮助子菜单
    helpMenu->addAction(aboutAct);
    helpMenu->addSeparator();//分隔符
    helpMenu->addAction(aboutQtAct);


}
void MainWindow::createToolBars()//创建工具条
{
    // 文件
    fileToolBar=addToolBar(tr("文件"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addSeparator();//分隔符
    fileToolBar->addAction(printAct);

    // 编辑
    editToolBar=addToolBar(tr("编辑"));
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addSeparator();//分隔符
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);

    // 格式
    formatToolBar=addToolBar(tr("格式"));
    formatToolBar->addAction(boldAct);
    formatToolBar->addAction(italicAct);
    formatToolBar->addAction(underlineAct);
    formatToolBar->addSeparator();//分隔符
    formatToolBar->addAction(leftAlignAct);
    formatToolBar->addAction(centerAct);
    formatToolBar->addAction(rightAlignAct);
    formatToolBar->addAction(justifyAct);
    formatToolBar->addSeparator();//分隔符
    formatToolBar->addAction(colorAct);

    // 组合工具栏
    addToolBarBreak(Qt::TopToolBarArea);
    comboToolBar=addToolBar(tr("组合选择"));
    comboStyle=new QComboBox();
    comboToolBar->addWidget(comboStyle);
    comboStyle->addItem("标准");
    comboStyle->addItem("• 圆点");
    comboStyle->addItem("◦ 空心圆点");
    comboStyle->addItem("▪ 小方块");
    comboStyle->addItem("1. 数字");
    comboStyle->addItem("a. 字母");
    comboStyle->addItem("Ⅰ. 罗马数字");
    comboStyle->setStatusTip("段落加上标号或编号");
    connect(comboStyle,QOverload<int>::of(&QComboBox::activated),this,&MainWindow::textStyle);

    comboFont=new QFontComboBox();
    comboToolBar->addWidget(comboFont);
    comboFont->setStatusTip("更改字体");
    connect(comboFont,&QFontComboBox::currentFontChanged,this,&MainWindow::textFamily);

   comboSize= new QComboBox();
   comboToolBar->addWidget(comboSize);
   comboSize->setEditable(true);
   comboSize->setStatusTip("更改字号");

   QFontDatabase db;
   foreach(int size,db.standardSizes()){
       comboSize->addItem(QString::number(size));
   }

}
void MainWindow::createStatusBars()//创建状态条
{
 statusBar()->showMessage(tr("准备就绪状态"));
}
MyChild *MainWindow::activeMyChild()const//激活子窗口,
{
    if (QMdiSubWindow *subWindow = mdiArea->activeSubWindow())
            return qobject_cast<MyChild *>(subWindow->widget());
        return 0;
}


//打开文件使用
QMdiSubWindow *MainWindow::findMyChild(const QString &filename)
{
    QString canonicalFilePath=QFileInfo(filename).canonicalFilePath();

    foreach(QMdiSubWindow *window,mdiArea->subWindowList()){
        MyChild *myChild=qobject_cast<MyChild*>(window->widget());

        if(myChild->currentFile()==canonicalFilePath)
            return window;
    }
    return 0;
}
void MainWindow::setActiveSubWindow(QWidget *window)//设置active激活窗口
{
    if(!window)
        return;
    mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow*>(window));
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
void MainWindow::textAlign(QAction *a)
{

}
void MainWindow::textStyle(int styleIndex)
{

}
void MainWindow::textFamily(const QFont &f)
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
