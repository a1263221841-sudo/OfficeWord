#include "mychild.h"
#include<QtWidgets>
MyCHILD::MyCHILD(QWidget *parent)
     : QMainWindow(parent)
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
    QString str =codex->toUnicode(data);
    if(Qt::mightBeRichText(str)){//如果是富文件
        textEdit->setHtml(str);
    }else//否则不是富文件
    {
        str=QString::fromLocal8Bit(data);
        textEdit->setPlainText(str);
    }
    setCurrentFile(fileName);
    connect(textEdit->document(),SIGNAL(contentChanged()),this,SLOT(documentWasModified()));
}
    return true;
        }
    bool MyCHILD:: save(){
        if(isUntitled){
            return saveAs();
        }else{
            return saveFile(curFile);
        }
    }
    //保存文件
    bool MyCHILD::saveAs(){//另存为文件
    QString fileName=QFileDialog::getSaveFileName(this,
    tr("另存为"),curFile,
    tr("HTML 文档(*.html);;所有文件(*.*)"));
   if(fileName.isEmpty())
       return false;
   return saveFile(fileName);
    }

    bool MyCHILD::saveFile(QString fileName){
    if(!(fileName.endsWith(".htm",Qt::CaseInsensitive)||fileName.endsWith(".html",Qt::CaseInsensitive())))
    {
            //默认保存文件为HTML
            fileName+=".html";
    }
            QTextDocumentWriter writer(fileName);
            bool success=writer.write(this->document());
            if(success)
            setCurrentFile(fileName);
            return success;
    }
    QString userFrinrlyCurrentFile(){

    }

    void MyCHILD::mergeFormationOnWordOrSelection(const QTextCharFormat &Format){

    }
    //格式化字体设置
    void MyCHILD::setAligin(int align){//对齐

    }
    void MyCHILD::setStyle(int style){

    }

    void MyCHILD::closeEvent(QCloseEvent *event){

    }

    void MyCHILD::documentWasModified(){

    }

    bool MyCHILD::maybeSave(){

    }
    void MyCHILD::setCurrentFile(const QString &fileName){

    }
    QString MyCHILD::strippedName(const QString &fullfileName){

    }


