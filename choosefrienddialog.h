#ifndef CHOOSEFRIENDDIALOG_H
#define CHOOSEFRIENDDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>

// 单个选中的联系人 Item
class  ChooseFriendItem : public QWidget{
    Q_OBJECT;
public:
    ChooseFriendItem(const QIcon &avatar, const QString &name, bool checked);
private:
    QCheckBox *checkBox;
    QPushButton *avatarBtn;
    QLabel *nameLabel;
};

class ChooseFriendDialog : public QDialog
{
    Q_OBJECT
public:
    ChooseFriendDialog(QWidget *parent);

private:
    // 初始化左右两侧窗口
    void initLeft(QHBoxLayout *layout);
    void initRight(QHBoxLayout *layout);

    // 添加一个 Item
    void addFriend(const QIcon &avatar, const QString &name, bool checked);

private:
    QWidget *totalContainer;
    QWidget *selectedContainer;
};

#endif // CHOOSEFRIENDDIALOG_H
