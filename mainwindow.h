#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QMessageBox"
#include "QtDebug"
#include "QTranslator"
#include "QFileDialog"
#include "QFile"
#include "QDir"
#include "QTextStream"
#include <QPrinter>
#include <QPrintDialog>
#include <QTextCursor>
#include <QDateTime>
#include <QFontDialog>
#include <QFont>
#include <QLabel>
#include <QDesktopServices>
#include <QTextBlock>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QSettings>
#include "aboutdialog.h"
#include "gotodialog.h"
#include "finddialog.h"
#include "replacedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void replace(QString value, bool isChecked);
private slots:
    //新建文件槽函数
    void newFile_s();
    //打开文件槽函数
    void openFile_s();
    //保存文件槽函数
    void saveFile_s();
    //另存为槽函数
    void saveAs_s();
    //打印槽函数
    void print_s();
    //编辑
    void edit_s();
    //撤销
    void undo_s();
    //退出软件槽函数
    void exit_s();
    //文本改变槽函数
    void textChange_s();
    //剪切槽函数
    void cut_s();
    //复制槽函数
    void copy_s();
    //粘贴槽函数
    void paste_s();
    //删除槽函数
    void delete_s();
    //查找槽函数
    void find_s();
    //查找下一个槽函数
    void findNext_s();

    //查找实现函数
    void doFind(QString value,bool isChecked,bool isUp);

    //替换槽函数
    void replace_s();

    //查找-替换槽函数
    void doFindForReplace(QString value,bool isChecked);
    //实现替换或者全替换槽函数
    void doReplace(QString target,QString value,bool isChecked,bool isReplaceAll);

    //转到槽函数
    void goTo_s();
    //到某一行
    void doGoToLine(QString line);
    //全选槽函数
    void selectAll_s();
    //日期时间槽函数
    void timeAndDate_s();
    //自动换行槽函数
    void autoLine_s();
    //字体选择槽函数
    void font_s();
    //光标变化槽函数
    void cursorChange_s();
    //状态栏槽函数
    void statusBar_s();
    //帮助槽函数
    void help_s();
    //关于槽函数
    void about_s();



private:
    Ui::MainWindow *ui;

    QString fileName;//文件名字
    QString fileContent;//读到的文件内容
    bool autoLine;//自动换行
    bool statusBar;//显示状态栏
    QLabel *change;//行和列
    gotoDialog gotoD;//跳转对话框
    findDialog findD;//查找
    aboutDialog aboutD;//关于
    replaceDialog replaceD;//替换
    bool isFirstFind;
    QSettings *setting;//配置文件
    //保存文本到文件
    void saveTextToFile();
    //读取文件
    void readFile();
    //显示提示消息
    void showMessage(QString);
    //拖动文件进入窗口
    void dragEnterEvent(QDragEnterEvent *e);
    //释放对方时，执行的操作
    void dropEvent(QDropEvent *e);
    //初始化一下参数
    void init();
    //关联信号和槽
    void conn();
    //设置快捷键
    void setShortcut();
    //关闭事件
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
