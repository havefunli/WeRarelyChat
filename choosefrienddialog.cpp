#include "choosefrienddialog.h"
#include "debug.h"

#include <QIcon>
#include <QScrollArea>
#include <QScrollBar>
#include <QGridLayout>

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
    // 创建滚动区域
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea{ border: none; }");
    layout->addWidget(scrollArea);
    // 创建对应的 QWidget
    totalContainer = new QWidget();
    scrollArea->setWidget(totalContainer);
    // 内部使用垂直管理器
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(10);
    vLayout->setContentsMargins(20, 20, 0, 10);
    vLayout->setAlignment(Qt::AlignTop);
    totalContainer->setLayout(vLayout);

#if TEST_UI
    QIcon avatar(":/image/avatar.png");
    for (int i = 0; i < 30; i++) {
        addFriend(avatar, "小菲" + QString::number(i + 1), i % 2);
    }
#endif
}

void ChooseFriendDialog::initRight(QHBoxLayout *layout)
{
    // 使用网格布局
    QGridLayout *gLayout = new QGridLayout();
    gLayout->setSpacing(0);
    gLayout->setContentsMargins(0, 0, 0, 0);
    layout->addLayout(gLayout);

    // 提示 Label
    QLabel *tipLabel = new QLabel();
    tipLabel->setText("选择联系人");
    tipLabel->setFixedHeight(30);
    tipLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    tipLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    tipLabel->setStyleSheet("QLabel {font-size: 16px; font-weight: 700; }");

    // 滚动区
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea{ border: none; }");

    // 创建对应的 QWidget
    selectedContainer = new QScrollArea();
    scrollArea->setWidget(selectedContainer);


}

void ChooseFriendDialog::addFriend(const QIcon &avatar, const QString &name, bool checked)
{
    ChooseFriendItem *item = new ChooseFriendItem(avatar, name, checked);
    totalContainer->layout()->addWidget(item);
}

ChooseFriendItem::ChooseFriendItem(const QIcon &avatar, const QString &name, bool checked)
{
    setFixedHeight(50);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 水平布局
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // 复选框
    checkBox = new QCheckBox();
    checkBox->setChecked(checked);
    checkBox->setFixedSize(25, 25);
    checkBox->setStyleSheet("QCheckBox::indicator { width: 20px; height: 20px; image: url(:/image/unchecked.png); } \
                            QCheckBox::indicator:checked { image: url(:/image/checked.png); }");

    // 头像
    avatarBtn = new QPushButton();
    avatarBtn->setFixedSize(40, 40);
    avatarBtn->setIcon(avatar);
    avatarBtn->setIconSize(QSize(40, 40));
    avatarBtn->setStyleSheet("QPushButtom { border: none;}");

    // 名字
    nameLabel = new QLabel();
    nameLabel->setText(name);

    layout->addWidget(checkBox);
    layout->addWidget(avatarBtn);
    layout->addWidget(nameLabel);
}
