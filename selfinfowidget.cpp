#include "selfinfowidget.h"
#include "debug.h"

#include <QCursor>
#include <QPushButton>
#include <QGridLayout>

SelfInfoWidget::SelfInfoWidget(QWidget *parent)
    : QDialog(parent)
{
    setFixedSize(450, 250);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setWindowTitle("个人信息");
    setAttribute(Qt::WA_DeleteOnClose); // 关闭时释放
    move(QCursor::pos()); // 初始在鼠标的位置

    // 使用网格布局管理
    QGridLayout *layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // 头像
    avatarBtn = new QPushButton();
    avatarBtn->setFixedSize(75, 75);
    avatarBtn->setIconSize(QSize(75, 75));
    avatarBtn->setIcon(QIcon(":/image/avatar.png"));
    avatarBtn->setStyleSheet("QPushButton { border: none; background-color: transparent; }");
    layout->addWidget(avatarBtn, 0, 0, 3, 1);

    // ID + 显示数据
    idTag = new QLabel();
    idTag->setFixedWidth(50);
    idTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    idTag->setText("ChatId");
    idTag->setStyleSheet("QLabel {font-size: 14px; font-weight: 800;} ");

    idLabel = new QLabel();
    idLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // 昵称 + 显示数据 + 编辑框
    nameTag = new QLabel();
    nameTag->setFixedWidth(50);
    nameTag->setText("昵称");
    nameTag->setStyleSheet("QLabel {font-size: 14px; font-weight: 800;} ");

    nameLabel = new QLabel();

    nameEdit = new QLineEdit();
    nameEdit->hide();

#if TEST_UI
    idLabel->setText("123456789");
    nameLabel->setText("小强");
#endif
    layout->addWidget(idTag, 0, 1);
    layout->addWidget(idLabel, 0, 2);
}

