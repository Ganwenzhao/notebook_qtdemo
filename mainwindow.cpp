#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->init();  //进行初始化

    this->conn(); //连接信号与槽

    this->setShortcut();//设置快捷键

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(){
    this->setWindowTitle("untitled-*");
    setting = new QSettings("config.ini",QSettings::IniFormat);
    //初始化默认值
    autoLine = true;//是否自动换行
    statusBar = true;//是否显示状态栏
    isFirstFind = true;//是否第一次搜索 替换时用
    ui->textEdit->setAcceptDrops(false); //设置文本输入框不接受鼠标放下
    this->setAcceptDrops(true);  //设置窗口接受鼠标放下

    setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记

    QString family =setting->value("family").toString();
    if(!family.isEmpty()){//设置了字体
        QFont font;
        font.setFamily(family);
        font.setPointSize(setting->value("point_size").toInt());//点大小
        font.setItalic(setting->value("italic").toBool());//斜体
        font.setBold(setting->value("bold").toBool());//加粗
        font.setOverline(setting->value("overline").toBool());//上划线
        font.setUnderline(setting->value("underline").toBool());//下划线
        ui->textEdit->setFont(font);//设置编辑框中字体
    }
    statusBar = setting->value("status_bar").toInt() == 1?true : false;//获取存储的值
    autoLine = setting->value("auto_go_line").toInt() == 1?true : false;
    setting->endGroup();

    //设置是否显示状态栏
    ui->statusBar->setVisible(statusBar);
    //是否显示显示状态栏勾中图标
    ui->actionStatusBar->setIconVisibleInMenu(statusBar);

    //设置QTextEdit自动换行
    ui->actionAutoLine->setIconVisibleInMenu(autoLine);
    if(autoLine){
        ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
    }else{
        ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
    }
    //设置状态栏
    ui->statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}")); // 设置不显示label的边框
    ui->statusBar->setSizeGripEnabled(false); //设置是否显示右边的大小控制点
    change = new QLabel("row 1，col 1   word count 0   ", this);
    ui->statusBar->addPermanentWidget(change); //显示永久信息
    //查找、查找下一个和撤销不可用
    ui->actionFind->setEnabled(false);
    ui->actionFind_Next->setEnabled(false);
    ui->actionRevoke->setEnabled(false);

}

void MainWindow::conn(){
    //文本变化
    connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(textChange_s()));

    //文件菜单
    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newFile_s()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openFile_s()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveFile_s()));
    connect(ui->actionSave_As,SIGNAL(triggered()),this,SLOT(saveAs_s()));
    connect(ui->actionPrint,SIGNAL(triggered()),this,SLOT(print_s()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(exit_s()));
    //编辑菜单
    connect(ui->menuEdit,SIGNAL(aboutToShow()),this,SLOT(edit_s()));
    connect(ui->actionRevoke,SIGNAL(triggered()),this,SLOT(undo_s()));
    connect(ui->actionCut,SIGNAL(triggered()),this,SLOT(cut_s()));
    connect(ui->actionCopy,SIGNAL(triggered()),this,SLOT(copy_s()));
    connect(ui->actionPaste,SIGNAL(triggered()),this,SLOT(paste_s()));
    connect(ui->actionDelete,SIGNAL(triggered()),this,SLOT(delete_s()));
    connect(ui->actionFind,SIGNAL(triggered()),this,SLOT(find_s()));
    connect(ui->actionFind_Next,SIGNAL(triggered()),this,SLOT(findNext_s()));
    connect(ui->actionReplace,SIGNAL(triggered()),this,SLOT(replace_s()));
    connect(ui->actiongoto,SIGNAL(triggered()),this,SLOT(goTo_s()));
    connect(ui->actionSelect_All,SIGNAL(triggered()),this,SLOT(selectAll_s()));
    connect(ui->actionTime_Date,SIGNAL(triggered()),this,SLOT(timeAndDate_s()));
    //格式菜单
    connect(ui->actionAutoLine,SIGNAL(triggered()),this,SLOT(autoLine_s()));
    connect(ui->actionFont,SIGNAL(triggered()),this,SLOT(font_s()));
    connect(ui->textEdit,SIGNAL(cursorPositionChanged()),this,SLOT(cursorChange_s()));
    //查看菜单
    connect(ui->actionStatusBar,SIGNAL(triggered()),this,SLOT(statusBar_s()));
    //帮助菜单
    connect(ui->actionHelp,SIGNAL(triggered()),this,SLOT(help_s()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(about_s()));




    connect(&gotoD, SIGNAL(goToLine(QString)), this,SLOT(doGoToLine(QString)));
    connect(&findD, SIGNAL(find(QString,bool,bool)), this,SLOT(doFind(QString,bool,bool)));
    connect(&replaceD, SIGNAL(find(QString,bool)), this,SLOT(doFindForReplace(QString,bool)));
    connect(&replaceD, SIGNAL(replace(QString,QString,bool,bool)), this,SLOT(doReplace(QString,QString,bool,bool)));



}

void MainWindow::setShortcut(){
    //快捷键
    ui->actionNew->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    ui->actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    ui->actionSave->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    ui->actionSave_As->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    ui->actionPrint->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));

    ui->actionRevoke->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    ui->actionCut->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    ui->actionCopy->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    ui->actionPaste->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    ui->actionFind->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    ui->actionFind_Next->setShortcut(QKeySequence(Qt::Key_F3));
    ui->actionReplace->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    ui->actionDelete->setShortcut(QKeySequence(Qt::Key_Delete));
    ui->actiongoto->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
    ui->actionSelect_All->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    ui->actionTime_Date->setShortcut(QKeySequence(Qt::Key_F5));
}

//新建文件槽函数
void MainWindow::newFile_s(){
    //文档已经修改
    if(ui->textEdit->document()->isModified()&& !ui->textEdit->document()->isEmpty()
            && fileContent != ui->textEdit->document()->toPlainText())
    {
        QMessageBox box(QMessageBox::Question,"NoteBook","Whether to save changes to untitled?");
        box.setIcon(QMessageBox::NoIcon);
        box.setStandardButtons (QMessageBox::Ok|QMessageBox::Ignore|QMessageBox::Cancel);
        box.setButtonText (QMessageBox::Ok,QString("Save"));
        box.setButtonText (QMessageBox::Ignore,QString("Not save"));
        box.setButtonText (QMessageBox::Cancel,QString("Cancel"));
        int result = box.exec();
        if(result == QMessageBox::Ok){
            if(fileName.isEmpty())
            {//新建
                //弹出保存文件对话框
                fileName = QFileDialog::getSaveFileName(this, tr("Open file"),QDir::homePath(),tr("txt (*.*);;"));
                if(!fileName.isEmpty()){
                    //保存文件
                    this->saveTextToFile();
                }
            }
            else{//读取的文本
                this->saveTextToFile();
            }
            ui->textEdit->clear();
            setWindowTitle("untitled - NoteBook");
        }
        else  if(result == QMessageBox::Ignore){
            //不保存
            ui->textEdit->clear();
            setWindowTitle("untitled - NoteBook");
            ui->statusBar->showMessage("");
        }
    }
    else{
        //文档未修改
        ui->textEdit->clear();
        setWindowTitle("untitled - NoteBook");
    }
    //路径置空
    fileName = "";
}


//退出应用槽函数
void MainWindow::exit_s(){
    //文档已经修改
    if(ui->textEdit->document()->isModified()&& !ui->textEdit->document()->isEmpty()
            && fileContent != ui->textEdit->document()->toPlainText())
    {
        QMessageBox box(QMessageBox::Question,"NoteBook","Whether to save changes to untitled?");
        box.setIcon(QMessageBox::NoIcon);
        box.setStandardButtons (QMessageBox::Ok|QMessageBox::Ignore|QMessageBox::Cancel);
        box.setButtonText (QMessageBox::Ok,QString("Save"));
        box.setButtonText (QMessageBox::Ignore,QString("Not save"));
        box.setButtonText (QMessageBox::Cancel,QString("Cancel"));
        int result = box.exec();
        if(result == QMessageBox::Ok){
            if(fileName.isEmpty()){//新建
                //弹出保存文件对话框
                fileName = QFileDialog::getSaveFileName(this, tr("Open file"),QDir::homePath(),tr("txt (*.*);;"));
                if(!fileName.isEmpty()){
                    //保存文件
                    this->saveTextToFile();
                }
            }else{//读取的文本
                this->saveTextToFile();
            }

        }else  if(result == QMessageBox::Ignore){
            //不保存 关闭
            this->close();
        }
    }

    else{
        this->close();
    }
}

//另存文件槽函数
void MainWindow::saveAs_s(){
    //弹出保存文件对话框
    fileName = QFileDialog::getSaveFileName(this, tr("Open file"),QDir::homePath(),tr("txt (*.*);;"));
    if(!fileName.isEmpty()){
        //保存文件
        this->saveTextToFile();
    }
}
//保存文件槽函数
void MainWindow::saveFile_s(){
    //判断是新建还是读取的文本
    if(fileName.isEmpty()){//新建
        //弹出保存文件对话框
        fileName = QFileDialog::getSaveFileName(this, tr("Open file"),QDir::homePath(),tr("txt (*.*);;"));
        if(!fileName.isEmpty()){
            //保存文件
            this->saveTextToFile();
        }
    }else{//读取的文本
        this->saveTextToFile();
    }
}
//保存文件
void MainWindow::saveTextToFile(){
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        out << ui->textEdit->document()->toPlainText();
        file.close();
        this->setWindowTitle(fileName.mid(fileName.lastIndexOf('/')+1)+" - NoteBook");
        fileContent = ui->textEdit->document()->toPlainText();
        ui->statusBar->showMessage("Save Success!",3000);
    }else{
        QMessageBox box(QMessageBox::Question,"Tip","Save Failed!");
        box.setIcon(QMessageBox::Warning);
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString("OK"));
        box.exec();
    }

}
//打开文件槽函数
void MainWindow::openFile_s(){
    //文档已经修改
    if(ui->textEdit->document()->isModified() && !ui->textEdit->document()->isEmpty()
            && fileContent != ui->textEdit->document()->toPlainText())
    {
        QMessageBox box(QMessageBox::Question,"NoteBook","Whether to save changes to untitled?");
        box.setIcon(QMessageBox::NoIcon);
        box.setStandardButtons (QMessageBox::Ok|QMessageBox::Ignore|QMessageBox::Cancel);
        box.setButtonText (QMessageBox::Ok,QString("Save"));
        box.setButtonText (QMessageBox::Ignore,QString("Not save"));
        box.setButtonText (QMessageBox::Cancel,QString("Cancel"));
        int result = box.exec();
        if(result == QMessageBox::Ok){
            //保存文件
            this->saveTextToFile();
        }else  if(result == QMessageBox::Ignore){
            //不保存
            //打开文件
            fileName = QFileDialog::getSaveFileName(this, tr("Open file"),QDir::homePath(),tr("txt (*.*);;"));
            this->readFile();
        }
    }
    else{
        fileName = QFileDialog::getSaveFileName(this, tr("Open file"),QDir::homePath(),tr("txt (*.*);;"));
        this->readFile();
    }
}
//真正打开文件
void MainWindow::readFile(){

    //得到路径不为空
    if(!fileName.isEmpty()){
        QFile *file = new QFile;
        file->setFileName(fileName);

        bool isOpen = file->open(QIODevice::ReadOnly);
        if(isOpen){
            ui->textEdit->clear();
            QTextStream in(file);

            while (!in.atEnd()) {
                ui->textEdit->append(in.readLine());
                //光标移动到开始位置
                ui->textEdit->moveCursor(QTextCursor::Start);
            }
            //已读完
            fileContent = ui->textEdit->document()->toPlainText();

            if(fileName.lastIndexOf("\\") != -1){
                //设置标题
                this->setWindowTitle(fileName.mid(fileName.lastIndexOf('\\')+1)+" - NoteBook");
            }else{
                //设置标题
                this->setWindowTitle(fileName.mid(fileName.lastIndexOf('/')+1)+" - NoteBook");
            }

            file->close();
            ui->statusBar->showMessage("");
        }else{
            QMessageBox box(QMessageBox::Question,"Tip","Open file failed！");
            box.setIcon(QMessageBox::Warning);
            box.setStandardButtons (QMessageBox::Ok);
            box.setButtonText (QMessageBox::Ok,QString("Ok"));
            box.exec();
        }
    }
}
//文本 变化槽函数
void MainWindow::textChange_s(){
    ui->statusBar->showMessage("");
    if(ui->textEdit->document()->isEmpty()){
        if(fileName.isEmpty()){//没有保存到文件
            this->setWindowTitle("untitled - NoteBook");

        }else{//有文件
            this->setWindowTitle(fileName.mid(fileName.lastIndexOf('/')+1)+" - NoteBook *");
            if( fileContent != ui->textEdit->document()->toPlainText())
                ui->statusBar->showMessage("Not save");
        }
    }else if(ui->textEdit->document()->isModified()){
        if(fileName.isEmpty()){//没有保存到文件
            this->setWindowTitle("untitled - NoteBook *");
            if( fileContent != ui->textEdit->document()->toPlainText())
                ui->statusBar->showMessage("Not save");
        }else{//有文件
            this->setWindowTitle(fileName.mid(fileName.lastIndexOf('/')+1)+" - NoteBook *");
            if( fileContent != ui->textEdit->document()->toPlainText())
                ui->statusBar->showMessage("Not save");
        }
        if(fileContent == ui->textEdit->document()->toPlainText()){
            this->setWindowTitle(fileName.mid(fileName.lastIndexOf('/')+1)+" - NoteBook");
        }
    }
    if(ui->textEdit->document()->isEmpty()){
        ui->actionFind->setEnabled(false);
        ui->actionFind_Next->setEnabled(false);
    }else{
        ui->actionFind->setEnabled(true);
        ui->actionFind_Next->setEnabled(true);
    }
    //撤销可用
    ui->actionRevoke->setEnabled(true);
}

// 打印槽函数
void MainWindow::print_s()
{
    // 创建打印机对象
    QPrinter printer;
    // 创建打印对话框
    QPrintDialog dlg(&printer, this);
    //如果编辑器中有选中区域，则打印选中区域
    if (ui->textEdit->textCursor().hasSelection())
        dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    // 如果在对话框中按下了打印按钮，则执行打印操作
    if (dlg.exec() == QDialog::Accepted) {
        ui->textEdit->print(&printer);
    }
}
// 编辑槽函数
void MainWindow::edit_s()
{
    QTextCursor cursor= ui->textEdit->textCursor();
    if(cursor.hasSelection()){
        //剪切复制删除可用
        ui->actionCut->setEnabled(true);
        ui->actionCopy->setEnabled(true);
        ui->actionDelete->setEnabled(true);

    }else{
        //剪切复制删除不可用
        ui->actionCut->setEnabled(false);
        ui->actionCopy->setEnabled(false);
        ui->actionDelete->setEnabled(false);

    }
}
// 撤销槽函数
void MainWindow::undo_s()
{
    ui->textEdit->undo();
}
//剪切
void MainWindow::cut_s()
{
    ui->textEdit->cut();
}
//复制
void MainWindow::copy_s()
{
    ui->textEdit->copy();
}
//粘贴
void MainWindow::paste_s()
{
    ui->textEdit->paste();
}
//删除
void MainWindow::delete_s()
{
    QTextCursor cursor= ui->textEdit->textCursor();
    if(cursor.hasSelection()){
        cursor.deleteChar();
    }
}
//全选
void MainWindow::selectAll_s()
{
    ui->textEdit->selectAll();
}
//时间和日期
void MainWindow::timeAndDate_s()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    ui->textEdit->append(time.toString("hh:mm yyyy-MM-dd"));
}
//自动换行
void MainWindow::autoLine_s(){
    if(autoLine){
        ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
        autoLine = false;

    }else{
        ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
        autoLine = true;
    }
    ui->actionAutoLine->setIconVisibleInMenu(autoLine);

    setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    setting->setValue("auto_go_line",QVariant(autoLine?"1":"0"));
    setting->endGroup();
}
//字体选择对话框
void MainWindow::font_s(){
    QFont textFont=  ui->textEdit->font();
    bool ok;
    QFont font = QFontDialog::getFont(&ok, textFont,this,tr("Font choose"));
    if (ok) {
        ui->textEdit->setFont(font);

        setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
        setting->setValue("family",QVariant(font.family()));
        setting->setValue("point_size",QVariant(font.pointSize()));
        setting->setValue("italic",QVariant(font.italic() == true ?"1":"0"));
        setting->setValue("bold",QVariant(font.bold()== true ?"1":"0"));
        setting->setValue("overline",QVariant(font.overline()== true ?"1":"0"));
        setting->setValue("underline",QVariant(font.underline()== true ?"1":"0"));
        setting->endGroup();
    }

}
//光标变化
void MainWindow::cursorChange_s(){
    QTextCursor cursor = ui->textEdit->textCursor();
    int column = cursor.columnNumber()+1;
    int block = cursor.blockNumber()+1;
    int count = ui->textEdit->document()->toPlainText().length();
    change->setText("No "+QString::number(block)+" row，No "+QString::number(column)+" col   word "+QString::number(count)+"   ");
}
//状态栏
void MainWindow::statusBar_s(){

    statusBar = !statusBar;
    ui->actionStatusBar->setIconVisibleInMenu(statusBar);
    ui->statusBar->setVisible(statusBar);

    setting->beginGroup("config");//beginGroup与下面endGroup 相对应，“config”是标记
    setting->setValue("status_bar",QVariant(statusBar?"1":"0"));
    setting->endGroup();
}
//关于记事本
void MainWindow::about_s(){

    aboutD.exec();
}
//跳转
void MainWindow::goTo_s(){

    gotoD.exec();
}
void MainWindow::doGoToLine(QString line){
    QTextCursor cursor = ui->textEdit->textCursor();
    if(line.toInt() > cursor.blockNumber()+1){
        QMessageBox box(QMessageBox::Question,"NoteBook - Jump row","row is larger than total row.");
        box.setIcon(QMessageBox::NoIcon);
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText (QMessageBox::Ok,QString("Ok"));
        box.setWindowFlags( Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint );
        box.exec();
        return;
    }
    gotoD.close();
    int position = ui->textEdit->document()->findBlockByLineNumber(line.toInt()-1 ).position();
    cursor.setPosition(position,QTextCursor::MoveAnchor);
    ui->textEdit->setTextCursor( cursor );
}
//帮助
void MainWindow::help_s(){
    QDesktopServices::openUrl(QUrl("https://go.microsoft.com/fwlink/?LinkId=834783"));
}
//查找槽函数
void MainWindow::find_s(){
    ui->textEdit->moveCursor(QTextCursor::Start);
    findD.exec();
}
//查找槽函数
void MainWindow::findNext_s(){
    QTextCursor tc= ui->textEdit->textCursor();
    if(tc.selectedText().isEmpty()){
        findD.exec();
    }else{
        doFind(tc.selectedText(),false,false);
    }
}
//查找
void MainWindow::doFind(QString value,bool isChecked,bool isUp){
    if(isUp){
        if(!isChecked){
            if(!ui->textEdit->find(value,QTextDocument::FindBackward)){
                showMessage("Cant`t find!\""+value+"\"");
            }
        }else{
            if(!ui->textEdit->find(value,QTextDocument::FindBackward|QTextDocument::FindCaseSensitively)){
                showMessage("Cant`t find!\""+value+"\"");
            }
        }
    }else{
        if(!isChecked){
            if(!ui->textEdit->find(value)){
                showMessage("Cant`t find!\""+value+"\"");
            }
        }else{
            if(!ui->textEdit->find(value,QTextDocument::FindCaseSensitively)){
                showMessage("Cant`t find!\""+value+"\"");
            }
        }
    }
    QPalette palette =  ui->textEdit->palette();
    palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
    ui->textEdit->setPalette(palette);
}
//替换
void MainWindow::replace_s(){
    isFirstFind = true;
    replaceD.exec();
}
//进行替换
void MainWindow::replace(QString value, bool isChecked)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    //替换单个值
    cursor.insertText(value);
    //光标移动到前一位
    ui->textEdit->moveCursor(cursor.PreviousCharacter);
    //是否区分大小写 查找替换后的值高亮
    if(!isChecked){
        ui->textEdit->find(value);
    }else{
        ui->textEdit->find(value,QTextDocument::FindCaseSensitively);
    }
}

void MainWindow::doReplace(QString target,QString value,bool isChecked,bool isReplaceAll){
    if(isFirstFind){
        ui->textEdit->moveCursor(QTextCursor::Start);
        isFirstFind = false;
    }
    if(!isChecked){
        if(!ui->textEdit->find(target)){
            showMessage("Cant`t find!\""+target+"\"");
            return;
        }
    }else{
        if(!ui->textEdit->find(target,QTextDocument::FindCaseSensitively)){
            showMessage("Cant`t find!\""+target+"\"");
            return;
        }
    }
    //选中高亮
    QPalette palette =  ui->textEdit->palette();
    palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
    ui->textEdit->setPalette(palette);
    //替换
    if(isReplaceAll){
        if(!ui->textEdit->textCursor().atEnd()){
            doFindForReplace(value,isChecked);
            doReplace(target,value,isChecked,isReplaceAll);
        }
    }else{
        doFindForReplace(value, isChecked);
    }
}
//查找
void MainWindow::doFindForReplace(QString value,bool isChecked){
    if(isFirstFind){
        ui->textEdit->moveCursor(QTextCursor::Start);
        isFirstFind = false;
    }

    this->doFind(value,isChecked,false);
}
void MainWindow::showMessage(QString title){
    QMessageBox box(QMessageBox::Question,"NoteBook - Find",title);
    box.setIcon(QMessageBox::NoIcon);
    box.setStandardButtons (QMessageBox::Ok);
    box.setButtonText (QMessageBox::Ok,QString("Ok"));
    box.setWindowFlags( Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint );
    box.exec();
}
//拖动文件进入窗口
void MainWindow::dragEnterEvent(QDragEnterEvent *even)
{
        even->acceptProposedAction(); //可以在这个窗口部件上拖放对象
}
//释放对方时，执行的操作
void MainWindow::dropEvent(QDropEvent *even)
{
    QList<QUrl> urls = even->mimeData()->urls();
    if(!urls.isEmpty()){
        this->fileName = urls.last().toLocalFile();
        if(!this->fileName.isEmpty()){
             this->readFile();//读文件
        }
    }
}
//关闭事件
void MainWindow::closeEvent(QCloseEvent *event){
    //文档已经修改
    if(ui->textEdit->document()->isModified() && !ui->textEdit->document()->isEmpty()
            && fileContent != ui->textEdit->document()->toPlainText()){
        QMessageBox box(QMessageBox::Question,"NoteBook","Whether to save changes to untitled?");
        box.setIcon(QMessageBox::NoIcon);
        box.setStandardButtons (QMessageBox::Ok|QMessageBox::Ignore|QMessageBox::Cancel);
        box.setButtonText (QMessageBox::Ok,QString("Save"));
        box.setButtonText (QMessageBox::Ignore,QString("Not save"));
        box.setButtonText (QMessageBox::Cancel,QString("Cancel"));
        int result = box.exec();
        if(result == QMessageBox::Ok){
            //保存文件
            if(fileName.isEmpty()){//新建
                //弹出保存文件对话框
                fileName = QFileDialog::getSaveFileName(this, tr("打开文件"),QDir::homePath(),tr("文本文件 (*.*);;"));
                if(!fileName.isEmpty()){
                    //保存文件
                    this->saveTextToFile();
                }
            }else{//读取的文本
                this->saveTextToFile();
            }
             event->accept();
        }else  if(result == QMessageBox::Ignore){
             event->accept();
        }else{
            event->ignore();
        }
    }else{
        event->accept();
    }
}















