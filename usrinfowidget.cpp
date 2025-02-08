#include "usrinfowidget.h"
#include <qgridlayout.h>

UsrInfoWidget::UsrInfoWidget(QWidget *parent, const UserInfo &user)
    : QDialog(parent)
    , usr(user)
{
    // 属性
    setFixedSize(400, 160);
    setWindowTitle("用户信息");
    setAttribute(Qt::WA_DeleteOnClose);
    move(QCursor().pos());

    QGridLayout *layout = new QGridLayout();
    layout->setHorizontalSpacing(20);
    layout->setContentsMargins(20, 10, 20, 10);
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);

    // 样式设计
    QString labelStyle = "QLabel { font-weight: 800; padding-left: 20px; } ";
    QString btnStyle = "QPushButton { border-radius: 5px; background-color: rgb(240, 240, 240); } \
                        QPushButton:pressed {background-color: rgb(205, 205, 205); } ";

    int height = 30;
    int width = 120;

    // 头像
    avatarBtn = new QPushButton();
    avatarBtn->setFixedSize(75, 75);
    avatarBtn->setIcon(QIcon(usr.avatar));
    avatarBtn->setIconSize(QSize(75, 75));
    avatarBtn->setStyleSheet("QPushButton { border: none; } ");

    // ID
    idTag = new QLabel();
    idTag->setText("ID");
    idTag->setStyleSheet(labelStyle);
    idTag->setFixedSize(width, height);
    idTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    idLabel = new QLabel();
    idLabel->setText(usr.userId);
    idLabel->setFixedSize(width, height);
    idLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // 用户昵称
    nameTag = new QLabel();
    nameTag->setText("昵称");
    nameTag->setStyleSheet(labelStyle);
    nameTag->setFixedSize(width, height);
    nameTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    nameLabel = new QLabel();
    nameLabel->setText(usr.nickName);
    nameLabel->setFixedSize(width, height);
    nameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // 电话
    phoneTag = new QLabel();
    phoneTag->setText("电话");
    phoneTag->setStyleSheet(labelStyle);
    phoneTag->setFixedSize(width, height);
    phoneTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    phoneLabel = new QLabel();
    phoneLabel->setText(usr.phoneNum);
    phoneLabel->setFixedSize(width, height);
    phoneLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // 申请好友
    applyBtn = new QPushButton();
    applyBtn->setText("申请好友");
    applyBtn->setFixedSize(width, 30);
    applyBtn->setStyleSheet(btnStyle);

    // 发送消息
    sendMsgBtn = new QPushButton();
    sendMsgBtn->setText("发送消息");
    sendMsgBtn->setFixedSize(width, 30);
    sendMsgBtn->setStyleSheet(btnStyle);

    // 删除好友
    delFriendBtn = new QPushButton();
    delFriendBtn->setText("删除好友");
    delFriendBtn->setFixedSize(width, 30);
    delFriendBtn->setStyleSheet(btnStyle);

    layout->addWidget(avatarBtn, 0, 0, 3, 1);

    layout->addWidget(idTag, 0, 1, 1, 1);
    layout->addWidget(idLabel, 0, 2, 1, 1);

    layout->addWidget(nameTag, 1, 1, 1, 1);
    layout->addWidget(nameLabel, 1, 2, 1, 1);

    layout->addWidget(phoneTag, 2, 1, 1, 1);
    layout->addWidget(phoneLabel, 2, 2, 1, 1);

    layout->addWidget(applyBtn, 3, 0, 1, 1);
    layout->addWidget(sendMsgBtn, 3, 1, 1, 1);
    layout->addWidget(delFriendBtn, 3, 2, 1, 1);
}
