#include "choosefrienddialog.h"

ChooseFriendDialog::ChooseFriendDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("选择好友");
    setFixedSize(750, 750);
    setStyleSheet("QDialog { background-color: rgb(225, 225, 225); }");
    setAttribute(Qt::WA_DeleteOnClose);

    // 设置布局
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    initLeft(layout);
    initRight(layout);
}

void ChooseFriendDialog::initLeft(QHBoxLayout *layout)
{

}

void ChooseFriendDialog::initRight(QHBoxLayout *layout)
{

}
