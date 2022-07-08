#ifndef ABOUTDLD_H
#define ABOUTDLD_H

#include <QDialog>

namespace Ui {
class aboutDlg;
}

class aboutDlg : public QDialog
{
    Q_OBJECT

public:
    explicit aboutDlg(QWidget *parent = nullptr);
    ~aboutDlg();

private slots:
    void on_OkBtn_clicked();

private:
    Ui::aboutDlg *ui;
};

#endif // ABOUTDLD_H
