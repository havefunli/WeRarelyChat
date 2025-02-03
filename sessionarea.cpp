#include "sessionarea.h"
#include "debug.h"
#include <QLabel>
#include <QStyleOption>
#include <QVBoxLayout>
#include <QPushButton>

SessionArea::SessionArea(QWidget *parent)
    : QScrollArea{parent}
{
    // 设置可变
    this->setWidgetResizable(true);
    container = new QWidget();
    container->setFixedWidth(310);
    this->setWidget(container);

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignTop);
    container->setLayout(layout);

    // 滚动条设置
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

#if TEST_UI
    for (int i = 0; i < 30; i++) {
        addItem(QIcon(":/image/avatar.png"), QString::number(i), "这是用例");
    }
#endif
}

void SessionArea::addItem(const QIcon &avatar, const QString &name, const QString &msg)
{
    SessionItem *item = new SessionItem(this, avatar, name, msg);
    container->layout()->addWidget(item);
}

void SessionArea::clear()
{
    QLayout *layout = container->layout();
    // 数组的元素在动态的变化；倒着删除
    for (int i = layout->count() - 1; i >= 0; i--) {
        QLayoutItem *item = layout->takeAt(i);
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}


SessionItem::SessionItem(QWidget *owner, const QIcon &avatar, const QString &name, const QString &msg)
    : owner(owner)
{
    this->setFixedHeight(70);
    this->setStyleSheet("QWidget {background-color: rgb(231, 231, 231);}");

    // 网格布局
    QGridLayout *layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    // 头像
    QPushButton *avatarBtn = new QPushButton();
    avatarBtn->setFixedSize(50, 50);
    avatarBtn->setIcon(avatar);
    avatarBtn->setIconSize(QSize(50, 50));
    avatarBtn->setStyleSheet("QPushButton {border: none;}");
    avatarBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // 名字
    QLabel *nameLabel = new QLabel();
    nameLabel->setText(name);
    nameLabel->setFixedHeight(35);
    nameLabel->setStyleSheet("QLabel {font-size: 18px; font-weight: 600;}");
    nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 最后一条信息
    QLabel *msgLabel = new QLabel();
    msgLabel->setText(msg);
    msgLabel->setFixedHeight(35);
    msgLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout->addWidget(avatarBtn, 0, 0, 2, 2);
    layout->addWidget(nameLabel, 0, 2, 1, 1);
    layout->addWidget(msgLabel, 1, 2, 1, 1);
}

void SessionItem::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
