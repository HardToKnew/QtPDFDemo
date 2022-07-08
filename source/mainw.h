#ifndef MAINW_H
#define MAINW_H

#include <QMainWindow>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainW; }
QT_END_NAMESPACE

class MainW : public QMainWindow
{
    Q_OBJECT

public:
    MainW(QWidget *parent = nullptr);
    ~MainW();

private slots:
    void on_readOnlyCheckBox_clicked(bool checked);

    void on_lockedCheckBox_clicked(bool checked);

    void on_addFileBtn_clicked();

    void on_removeFileBtn_clicked();

    void on_removeAllBtn_clicked();

    void on_showPasswd_clicked(bool checked);

    void on_actionLocked_triggered();

    void on_actionUnlocked_triggered();

    void on_actionSplitFile_triggered();

    void on_actionHelp_triggered();

    void on_actionAbout_triggered();

    void on_filePathInfoCliked(Qt::MouseButton);
    void on_compositeBtn_clicked();

    void on_actionSeting_triggered();

private:
    Ui::MainW *ui;
    QLabel *filePathInfo;///默认存储文件位置显示控件
    QString defaultOpenFileName;///默认读取文件路径
    QString defaultOutPath;
    QString defaultStr = "默认存储位置: ";

    QString getCmd();

protected:
    //bool eventFilter(QObject *watched, QEvent *event);///事件过滤器，此软件主要判断label控件被鼠标右键点击
signals:
    //void filePathInfoCliked(Qt::MouseButton);
};
#endif // MAINW_H
