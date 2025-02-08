#ifndef CHOOSEFRIENDDIALOG_H
#define CHOOSEFRIENDDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QHBoxLayout>

class ChooseFriendDialog : public QDialog
{
    Q_OBJECT
public:
    ChooseFriendDialog(QWidget *parent);

private:
    // 初始化左右两侧窗口
    void initLeft(QHBoxLayout *layout);
    void initRight(QHBoxLayout *layout);

private:
    QWidget *totalContainer;
    QWidget *selectedContainer;
};

#endif // CHOOSEFRIENDDIALOG_H
