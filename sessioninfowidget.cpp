#include "sessioninfowidget.h"
#include "choosefrienddialog.h"
#include "debug.h"

#include <QVBoxLayout>
#include <QPushButton>

AvatarItem::AvatarItem(const QIcon &avatar, const QString &name)
{
    setFixedSize(70, 80);

    // 布局管理器
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignHCenter);
    setLayout(layout);

    // 头像
    avatarBtn = new QPushButton();
    avatarBtn->setFixedSize(45, 45);
    avatarBtn->setIcon(avatar);
    avatarBtn->setIconSize(QSize(45, 45));
    avatarBtn->setStyleSheet("QPushButton { border: none;} ");

    // 昵称
    nameLabel = new QLabel();
    QFont font("微软雅黑", 8);
    nameLabel->setFont(font);
    nameLabel->setAlignment(Qt::AlignCenter);

    // 避免名字过长，截断操作
    const int MAX_WIDTH = 65;
    QFontMetrics metric(font);
    // 计算初始字段长度
    int totalWidth = metric.horizontalAdvance(name);
    // 过长
    if (totalWidth > MAX_WIDTH) {
        QString tail = "..."; // 截断符号
        int tailWidth = metric.horizontalAdvance(tail);
        int availableWidth = MAX_WIDTH - tailWidth;   // 计算可用长度
        int newSize = (availableWidth / (double)totalWidth) * name.size();
        // 截取为指定长度字符串
        QString newName = name.left(newSize);
        newName += tail;
        // 设置
        nameLabel->setText(newName);
    } else {
        nameLabel->setText(name);
    }

    layout->addWidget(avatarBtn);
    layout->addWidget(nameLabel);
}

QPushButton *AvatarItem::getAvatar()
{
    return avatarBtn;
}

SessionInfoWidget::SessionInfoWidget(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("会话详情");
    setFixedSize(300, 300);
    setAttribute(Qt::WA_DeleteOnClose);

    QGridLayout *layout = new QGridLayout();
    layout->setSpacing(10);
    layout->setContentsMargins(40, 0, 40, 0);
    setLayout(layout);

    // 创建群聊图标
    AvatarItem *createGroupBtn = new AvatarItem(QIcon(":/image/add.png"), "添加");

#if TEST_UI
    // 好友图标
    AvatarItem *friendBtn = new AvatarItem(QIcon(":/image/avatar_boy.png"), "小菲");
#endif

    // 删除好友按键
    QPushButton *delFrindBtn = new QPushButton();
    delFrindBtn->setFixedHeight(50);
    delFrindBtn->setText("删除好友");
    QString btnStyle = "QPushButton { border: 1px solid rgb(90, 90, 90); border-radius: 5px;} \
        QPushButton:pressed { background-color: rgb(235, 235, 235); }";
    delFrindBtn->setStyleSheet(btnStyle);

    layout->addWidget(createGroupBtn, 0, 0, 1, 1);
    layout->addWidget(friendBtn, 0, 1, 1, 1);
    layout->addWidget(delFrindBtn, 1, 0, 1, 3);

    connect(createGroupBtn->getAvatar(), &QPushButton::clicked, this, [this](){
        ChooseFriendDialog *chooseDialog = new ChooseFriendDialog(this);
        chooseDialog->exec();
    });
}
