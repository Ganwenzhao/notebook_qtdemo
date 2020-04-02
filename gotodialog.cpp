#include "gotodialog.h"
#include "ui_gotodialog.h"

gotoDialog::gotoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gotoDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    setWindowTitle("Go to specify row");
}

gotoDialog::~gotoDialog()
{
    delete ui;
}

void gotoDialog::showMessage(QString title){
    QMessageBox box(QMessageBox::Question,"Notebook - Jump row",title);
    box.setIcon(QMessageBox::NoIcon);
    box.setStandardButtons (QMessageBox::Ok);
    box.setButtonText (QMessageBox::Ok,QString("Ok"));
    box.setWindowFlags( Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint );
    box.exec();
}

void gotoDialog::on_pushButtonCancel_clicked()
{
    this->close();
}


void gotoDialog::on_pushButtonOk_clicked()
{
    QString value = ui->lineEdit->text().trimmed();
    if(value.isEmpty()){
        this->showMessage("Please input the row");
        return;
    }

    QRegExp rx("(\\d+)");
    if(!rx.exactMatch(value)){
        this->showMessage("Please input positive integer");
        return;
    }
    emit goToLine(value);
}
