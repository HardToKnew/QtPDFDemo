#ifndef HELPDLG_H
#define HELPDLG_H

#include <QDialog>

namespace Ui {
class helpDlg;
}

class helpDlg : public QDialog
{
    Q_OBJECT

public:
    explicit helpDlg(QWidget *parent = nullptr);
    ~helpDlg();

private slots:
    void on_OkBtn_clicked();

private:
    Ui::helpDlg *ui;

    void setDefaultText();
};

#endif // HELPDLG_H
