#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//添加相关的头文件
#include <QPrintDialog>
#include <QtWidgets>
//#include <mychild.h>
#include<QPrinter>
#include<QPrintPreviewDialog>
#include<QSignalMapper>

class MyChild;
class QAction;//被创建后必须添加到菜单和工具栏,然后将它链接到实现的Action功能的槽函数
class QMenu;//此为菜单栏,菜单QMenus是挂载在菜单栏QMenuBar(容器)上面的.
class QComboBox;//选项列表(组合框)
class QFontComboBox;//字体下拉列表框(不能被编辑,只是被用来选择字体)
class QMdiArea;//提供一个可以同时显示多个文档的区域
class QMdiSubWindow;//大多数复杂的项目软件,都是使用MDI框架
class QSignalMapper;//此类专门收集一系列无参信号



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MyChild *createMyChild();
protected:
    void closeEvent(QCloseEvent *event);//通过参数event来控制参数是否让窗口关闭

private:
    void fileNew();//新建文件
    void fileOpen();//打开
    void fileSave();//保存
    void fileSaveAS();//另存为
    void filePrint();//打印
    void filePrintPreview();//文件打印预览
    void printPreview(QPrinter *);//打印预览

    void undo();//撤销
    void redo();//重做
    void cut();//剪切
    void copy();//复制
    void paste();//粘贴
    void about();// 关于


    void textBold();
    void textItalic();
    void textUnderline();
    void textAlign(QAction *a);
    void textStyle(int styleIndex);
    void textFamily(const QFont &f);
    void textSize(const QString &p);
    void textColor();


    void updateMenus();//更新菜单
    void updateWindowMenu();//更新
    void setActiveSubWindow(QWidget *window);
    //MyChild *createMyChild();



private:
    void createActions();//创建菜单操作(动作)
    void createMenus();//创建菜单
    void createToolBars();//创建工具条
    void createStatusBars();//创建状态条
    void enableText();//可移动文本
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);//对齐改变
    MyChild *activeMyChild()const;
    QMdiSubWindow *findMyChild(const QString &filename);

    QMdiArea *mdiArea;//多文档窗口容器的容器管理器
    QSignalMapper *windowMapper;

    //定义菜单
    QMenu *fileMenu;//文件菜单
    QMenu *editMenu;//编辑菜单
    QMenu *formatMenu;//格式菜单
    QMenu *fontMenu;//字体菜单
    QMenu *alignMenu;//对齐菜单
    QMenu *windowMenu;
    QMenu *helpMenu;

    //工具栏
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *formatToolBar;
    QToolBar *comboToolBar;
    QComboBox *comboStyle; //子控件,标准组合框

    QFontComboBox *comboFont;//子控件,字体组合框
    QComboBox *comboSize;//子控件,字体大小的组合框

    //菜单动作(Action)
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *printAct;
    QAction *printPreviewAct;
    QAction *exitAct;


    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;

    QAction *boldAct;
    QAction *italicAct;
    QAction *underlineAct;
    QAction *leftAlignAct;
    QAction *centerAct;
    QAction *rightAlignAct;
    QAction *justifyAct;
    QAction *colorAct;

    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;
    QAction *separatorAct;

    QAction *aboutAct;
    QAction *aboutQtAct;






    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
