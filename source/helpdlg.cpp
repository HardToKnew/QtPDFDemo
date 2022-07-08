#include "helpdlg.h"
#include "ui_helpdlg.h"
#include <QFile>
#include <QTextStream>

helpDlg::helpDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpDlg)
{
    ui->setupUi(this);
    QFile file(QCoreApplication::applicationDirPath()+"/config/help.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        setDefaultText();
         return;
    }
     QTextStream in(&file);
     in.setCodec("utf-8");
     QString helpText = in.readAll();
     if(!helpText.isNull()) {
         ui->textBrowser->setText(helpText);
     }
     else
     {
         setDefaultText();
     }
}

helpDlg::~helpDlg()
{
    delete ui;
}

void helpDlg::on_OkBtn_clicked()
{
    this->close();
}

void helpDlg::setDefaultText()
{
    QString helpText = "PDFProDemo Version 0.0.1\n";
    helpText.append("2022/06/11");
    ui->textBrowser->setText(helpText);
}
