#include "aboutdlg.h"
#include "ui_aboutdlg.h"

aboutDlg::aboutDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("About 软件");
    //ui->textBrowser->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->textBrowser->setOpenExternalLinks(true);
}

aboutDlg::~aboutDlg()
{
    delete ui;
}



void aboutDlg::on_OkBtn_clicked()
{
    this->close();
}
