#include "mychild.h"
#include<QtWidgets>
MyCHILD::MyCHILD()
{
    setAttribute(Qt::WA_DeleteOnClose);//关闭窗口时销毁
     isUntited=true;
}
    void newFile(){//新建文件
        static int sequenceNumber =1;
        isUntitled =true;
        curFile =tr("word文档=%1").arg(sequenceNumber++);
        setWindowTitle(curFile);

    }
    bool loadFile(const QString &fileName)//导入文件
    {

        }
    bool save(){

    }
    //保存文件
    bool saveAs(){//另存为文件

    }

    bool saveFile(QString fileName){

    }
    QString userFrinrlyCurrentFile(){

    }

    void mergeFormationOnWordOrSelection(const QTextCharFormat &Format){

    }
    //格式化字体设置
    void setAligin(int align){//对齐

    }
    void setStyle(int style){

    }

    void closeEvent(QCloseEvent *event){

    }

    void documentWasModified(){

    }

    bool maybeSave(){

    }
    void setCurrentFile(const QString &fileName){

    }
    QString strippedName(const QString &fullfileName){

    }


