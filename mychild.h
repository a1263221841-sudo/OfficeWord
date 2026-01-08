#ifndef MYChild_H
#define MYChild_H
#include<QMainWindow>
#include <QTextEdit>


class MyChild: public QMainWindow
{ Q_OBJECT
public:
    explicit MyChild(QWidget *parent =nullptr);

    QTextCursor textCursor() const;
    bool hasSelection() const;

    void newFile();//新建文件
    bool loadFile(const QString &fileName);//导入文件
    bool save();//保存文件
    bool saveAs();//另存为文件
    bool saveFile(QString fileName);
    QString userFriendlyCurrentFile();
    QString currentFile(){ return curFile;}
    void mergeFormationOnWordOrSelection(const QTextCharFormat &Format);//格式化字体设置
    void setAligin(int align);//对齐
    void setStyle(int style);
signals:  // 信号声明
    void copyAvailable(bool yes);
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void documentWasModified();

private:
    QString curFile;
    bool isUntitled;//判断标题
    QTextEdit *textEdit;
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullfileName);




};

#endif // MYChild_H
