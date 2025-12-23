#include "mychild.h"
#include<QtWidgets>
MyCHILD::MyCHILD()
{
    setAttribute(Qt::WA_DeleteOnClose);//关闭窗口时销毁
     isUntitled=true;
}
    void MyCHILD:: newFile(){//新建文件
        static int sequenceNumber =1;
        isUntitled =true;
        curFile =tr("word文档=%1").arg(sequenceNumber++);
        setWindowTitle(curFile);

    }
    bool MyCHILD::loadFile(const QString &fileName)//导入文件
    {
    if(fileName.isEmpty()){
    return false;
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))
        return false;
    QByteArray data=file.readAll();
    QTextCodec *codex =Qt::codecForHtml(data);
    QString str =codec->toUnicode(data);
    if(Qt::mightBeRichText(str)){//如果是富文件
        textEdit->setHtml(str);
    }else//否则不是富文件
    {
        str=QString::fromLocal8Bit(data);
        this->setPlainText(str);
    }
    setCurrentFile(fileName);
    connect(document(),SIGNAL(contentChanged()),this,SLOT(documentWasModified()));
}
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


