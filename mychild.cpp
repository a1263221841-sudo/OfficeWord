#include "mychild.h"
#include<QtWidgets>
#include <QMessageBox>
MyChild::MyChild(QWidget *parent)
     : QTextEdit(parent)
{
    textEdit = new QTextEdit(this);
        //setCentralWidget(textEdit);

        // 【核心步骤】当内部编辑器说“可以复制”时，MyChild 也对外喊一声“可以复制”
        connect(textEdit, &QTextEdit::copyAvailable, this, &MyChild::copyAvailable);
    setAttribute(Qt::WA_DeleteOnClose);//关闭窗口时销毁
     isUntitled=true;
     textEdit = new QTextEdit(this);
        // setCentralWidget(textEdit);
}
    void MyChild:: newFile(){//新建文件
        static int sequenceNumber =1;
        isUntitled =true;
        curFile =tr("word文档=%1").arg(sequenceNumber++);
        setWindowTitle(curFile);

    }
    bool MyChild::loadFile(const QString &fileName)//导入文件
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
    bool MyChild:: save(){
        if(isUntitled){
            return saveAs();
        }else{
            return saveFile(curFile);
        }
    }
    //保存文件
    bool MyChild::saveAs(){//另存为文件
    QString fileName=QFileDialog::getSaveFileName(this,
    tr("另存为"),curFile,
    tr("HTML 文档(*.html);;所有文件(*.*)"));
   if(fileName.isEmpty())
       return false;
   return saveFile(fileName);
    }

    bool MyChild::saveFile(QString fileName){
    if(!(fileName.endsWith(".htm",
      Qt::CaseInsensitive)||fileName.endsWith(".html",Qt::CaseInsensitive)))
    {
            //默认保存文件为HTML
            fileName+=".html";
    }
            QTextDocumentWriter writer(fileName);
            bool success=writer.write(textEdit->document());
            if(success)
            setCurrentFile(fileName);
            return success;
    }
    QString MyChild::userFriendlyCurrentFile(){
    return strippedName(curFile);

    }
   //格式化字体设置

    void MyChild::mergeFormationOnWordOrSelection(const QTextCharFormat &Format){
        QTextCursor cursor=textEdit->textCursor();
        if(!cursor.hasSelection()){
            cursor.select(QTextCursor::WordUnderCursor);
            cursor.mergeCharFormat(Format);
            textEdit->mergeCurrentCharFormat(Format);
        }
    }
    //段落对齐设置
    void MyChild::setAligin(int align){
    if(align==1){
        textEdit->setAlignment(Qt::AlignLeft |Qt::AlignAbsolute);
    }else if(align==2){
        textEdit->setAlignment(Qt::AlignCenter);
    }else if(align==3){
        textEdit->setAlignment(Qt::AlignRight);
    }else if(align==4){
        textEdit->setAlignment(Qt::AlignJustify);
    }

    }
    //断落编号
    void MyChild::setStyle(int style){
    //多行文本框文本光标插入文本
         QTextCursor cursor = textEdit->textCursor();
        if(style!=0){
            QTextListFormat::Style stylename=QTextListFormat::ListDisc;//圆圈
            switch(style){
            default:
                return;
            case 1:
                stylename=QTextListFormat::ListDisc;//圆圈
                break;
            case 2:
                stylename=QTextListFormat::ListCircle;//空心圆
                break;
            case 3:
                stylename=QTextListFormat::ListSquare;//方块
                break;
            case 4:
                stylename=QTextListFormat::ListDecimal;//阿拉伯数字
                break;
            case 5:
                stylename=QTextListFormat::ListLowerAlpha;//小写拉丁字符,按字母顺序
                break;
            case 6:
               stylename=QTextListFormat::ListUpperAlpha;//大写拉丁字符,按字母顺序
                break;
            case 7:
                stylename=QTextListFormat::ListLowerRoman;//小写罗马数字
                break;
            case 8:
                stylename=QTextListFormat::ListUpperRoman;//大写罗马数字
                break;
            }
                cursor.beginEditBlock();
                QTextBlockFormat blockFmt=cursor.blockFormat();
                QTextListFormat listFmt;
                if(cursor.currentList())
                {
                    listFmt=cursor.currentList()->format();
                }else
                {
                    listFmt.setIndent(blockFmt.indent()+1);
                    blockFmt.setIndent(0);
                    cursor.setBlockFormat(blockFmt);
                }
                listFmt.setStyle(stylename);
                cursor.createList(listFmt);
                cursor.endEditBlock();
            }
            else{
                QTextBlockFormat bfmt;
                bfmt.setObjectIndex(-1);
                cursor.mergeBlockFormat(bfmt);
            }

      //  QTextCursor cursor=textEdit->textCursor();

    }

    void MyChild::closeEvent(QCloseEvent *event){
    if(maybeSave()){
        event->accept();
    }else{
        event->ignore();
    }
    }

    void MyChild::documentWasModified(){
//在设置改变时,设置窗口已经修改
        setWindowModified(textEdit->document()->isModified());
    }

    bool MyChild::maybeSave(){//判断是否修改且保存文件
    if(!textEdit->document()->isModified())
       { return true;
    }
        QMessageBox::StandardButton ret;
        ret= QMessageBox::warning(
           this,
           tr("Qt Word"),
        tr("文件'%1'已经被修改,是否保存么?")
          .arg(userFriendlyCurrentFile()),
        QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
                if(ret==QMessageBox::Save){
            return save();
        }else if(ret==QMessageBox::Cancel){
            return false;
        }return true;

    }
    void MyChild::setCurrentFile(const QString &fileName){
        curFile=QFileInfo(fileName).canonicalFilePath();
        isUntitled=false;
        textEdit->document()->setModified(false);
        setWindowModified(false);
        setWindowTitle(userFriendlyCurrentFile()+"[*]");

    }
    QString MyChild::strippedName(const QString &fullfileName){
    return QFileInfo(fullfileName).fileName();
    }

    // 1. 实现获取光标的函数
    QTextCursor MyChild::textCursor() const
    {
        // 转发给内部的 textEdit 控件
        return textEdit->textCursor();
    }

    // 2. 实现判断是否有选中文字的函数
    bool MyChild::hasSelection() const
    {
        return textEdit->textCursor().hasSelection();
    }
