#include "sessionarea.h"
#include "debug.h"
#include <QDebug>
#include <QStyleOption>
#include <QVBoxLayout>


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
        addItem(ApplyItemType, QString::number(i + 1), QIcon(":/image/avatar.png"), QString::number(i), "这是用例");
    }
#endif
}

void SessionArea::addItem(ItemType itemType, const QString &id, const QIcon &avatar, const QString &name, const QString &msg)
{
    // 根据类型来初始化不同的对象
    SessionFriendItem *item = nullptr;
    switch (itemType) {
    case SessionItemType:
        item = new SessionItem(this, id, avatar, name, msg);
        break;
    case FriendItemType:
        item = new FriendItem(this, id, avatar, name, msg);
        break;
    case ApplyItemType:
        item = new ApplyItem(this, id, avatar, name);
        break;
    default:
        break;
    }
    container->layout()->addWidget(item);
}

void SessionArea::clickedItem(int index)
{
    if (index < 0 || index >= container->layout()->count()) {
        qDebug() << "clickedItem()::下标越界了";
        return;
    }
    QLayoutItem *layoutItem = container->layout()->takeAt(index);
    if (layoutItem == nullptr || layoutItem->widget() == nullptr) {
        qDebug() << "clickedItem()::数据不存在";
        return;
    }

    SessionFriendItem *item = dynamic_cast<SessionFriendItem*>(layoutItem->widget());
    item->select();
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


SessionFriendItem::SessionFriendItem(QWidget *owner, const QIcon &avatar, const QString &name, const QString &msg)
    : owner(owner)
    , isSelected(false)
{
    this->setFixedHeight(70);
    this->setStyleSheet("QWidget {background-color: rgb(231, 231, 231);}");

    // 网格布局
    QGridLayout *layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    // 头像
    avatarBtn = new QPushButton();
    avatarBtn->setFixedSize(50, 50);
    avatarBtn->setIcon(avatar);
    avatarBtn->setIconSize(QSize(50, 50));
    avatarBtn->setStyleSheet("QPushButton {border: none;}");
    avatarBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // 名字
    nameLabel = new QLabel();
    nameLabel->setText(name);
    nameLabel->setFixedHeight(35);
    nameLabel->setStyleSheet("QLabel {font-size: 18px; font-weight: 600;}");
    nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 信息
    msgLabel = new QLabel();
    msgLabel->setText(msg);
    msgLabel->setFixedHeight(35);
    msgLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout->addWidget(avatarBtn, 0, 0, 2, 2);
    layout->addWidget(nameLabel, 0, 2, 1, 8);
    layout->addWidget(msgLabel, 1, 2, 1, 8);
}

void SessionFriendItem::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SessionFriendItem::select()
{
    this->setStyleSheet("QWidget {background-color: rgb(210, 210, 210);}");
    isSelected = true;
    // 去除其他控件颜色
    QList<SessionFriendItem*> items = parentWidget()->findChildren<SessionFriendItem*>();
    for (auto &item : items) {
        if (!item->isSelected || this != item) {
            item->isSelected = false;
            item->setStyleSheet("QWidget {background-color: rgb(231, 231, 231);}");
        }
    }

    // 业务函数
    active();
}

void SessionFriendItem::active()
{}

void SessionFriendItem::mousePressEvent(QMouseEvent *event)
{
    if (isSelected) {
        return;
    }
    select();
}

void SessionFriendItem::enterEvent(QEnterEvent *event)
{
    if (isSelected) {
        return;
    }
    this->setStyleSheet("QWidget {background-color: rgb(215, 215, 215);}");
}

void SessionFriendItem::leaveEvent(QEvent *event)
{
    // 避免颜色被刷新
    if (isSelected) {
        return;
    }
    this->setStyleSheet("QWidget {background-color: rgb(231, 231, 231);}");
}


SessionItem::SessionItem(QWidget *owner, const QString &chatSessionId, const QIcon &avatar, const QString &name, const QString &msg)
    : SessionFriendItem(owner, avatar, name, msg)
    , chatSessionId(chatSessionId)
{}

void SessionItem::active()
{
    qDebug()<< "SessionItem";
}



FriendItem::FriendItem(QWidget *owner, const QString &userId, const QIcon &avatar, const QString &name, const QString &description)
    : SessionFriendItem(owner, avatar, name, description)
    , userId(userId)
{}

void FriendItem::active()
{
    qDebug()<< "FriendItem";
}

ApplyItem::ApplyItem(QWidget *owner, const QString &userId, const QIcon &avatar, const QString &name)
    : SessionFriendItem(owner, avatar, name, "")
    , userId(userId)
{
    QGridLayout *layout = static_cast<QGridLayout*>(this->layout());
    layout->removeWidget(msgLabel);
    delete msgLabel;

    // 同意按钮 / 拒绝按钮
    QPushButton *acceptBtn = new QPushButton();
    acceptBtn->setText("同意");
    acceptBtn->setIcon(QIcon(":/image/accept.png"));

    QPushButton *rejectBtn = new QPushButton();
    rejectBtn->setText("拒绝");
    rejectBtn->setIcon(QIcon(":/image/reject.png"));

    layout->addWidget(acceptBtn, 1, 2, 1, 1);
    layout->addWidget(rejectBtn, 1, 3, 1, 1);
}

void ApplyItem::active()
{
    qDebug()<< "ApplyItem";
}
