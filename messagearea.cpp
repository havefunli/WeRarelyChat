#include "messagearea.h"
#include "debug.h"


#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>

using model::MessageType;

MessageArea::MessageArea()
    : container(new QWidget())
{
    // 属性设置
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWidget(container);
    setWidgetResizable(true);
    setStyleSheet("QScrollArea { border:none; }");

    // 滚动条设置
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 布局管理
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    container->setLayout(layout);

    // 测试数据
#if TEST_UI
    for(int i = 0; i < 30; i++) {
        model::UserInfo usr;
        usr.nickName = "小权" + QString::number(i + 1);
        usr.avatar = QIcon(":/image/avatar_boy.png");
        Message msg = Message::makeMessage(model::TEXT, "", usr, "这是测试消息", "");
        addMessage(i % 2, msg);
    }
#endif
}

void MessageArea::addMessage(bool isLeft, const Message &msg)
{
    MessageItem *item = MessageItem::makeMessageItem(isLeft, msg);
    container->layout()->addWidget(item);
}

void MessageArea::addMessageFront(bool isLeft, const Message &msg)
{
    MessageItem *item = MessageItem::makeMessageItem(isLeft, msg);
    QVBoxLayout *layout = dynamic_cast<QVBoxLayout*>(container->layout());
    layout->insertWidget(0, item);
}

void MessageArea::clear()
{
    QLayout *layout = container->layout();
    for (int i = layout->count() - 1; i >= 0; i--) {
        QLayoutItem *item = layout->takeAt(i);
        if (item != nullptr && item->widget() != nullptr) {
            delete item->widget();
        }
    }
}

MessageItem::MessageItem(bool isLeft)
    : isLeft(isLeft)
{}

MessageItem *MessageItem::makeMessageItem(bool isLeft, const Message &msg)
{
    // 布局管理器
    MessageItem *item = new MessageItem(isLeft);
    QGridLayout *layout = new QGridLayout();
    layout->setSpacing(8);
    layout->setContentsMargins(30, 10, 30, 0);
    item->setMinimumHeight(100);
    item->setLayout(layout);

    // 设置头像
    QPushButton *avatarBtn = new QPushButton();
    avatarBtn->setFixedSize(40, 40);
    avatarBtn->setIcon(msg.sender.avatar);
    avatarBtn->setIconSize(QSize(40, 40));
    avatarBtn->setStyleSheet("QPushButton {border:none;}");
    // 根据类型布局
    if (isLeft) {
        layout->addWidget(avatarBtn, 0, 0, 2, 1, Qt::AlignLeft | Qt::AlignTop);
    } else {
        layout->addWidget(avatarBtn, 0, 1, 2, 1, Qt::AlignRight | Qt::AlignTop);
    }

    // 设置名字时间
    QLabel *nameAndTime = new QLabel();
    nameAndTime->setText(msg.sender.nickName + " | " + msg.time);
    nameAndTime->setAlignment(Qt::AlignBottom);
    nameAndTime->setStyleSheet("QLabel { font-size: 12px; color: rgb(178, 178, 178); }");
    if (isLeft) {
        layout->addWidget(nameAndTime, 0, 1, Qt::AlignLeft | Qt::AlignTop);
    } else {
        layout->addWidget(nameAndTime, 0, 0, Qt::AlignRight | Qt::AlignTop);
    }

    // 根据消息类型创建消息体
    QWidget *contentWidget = nullptr;
    switch (msg.type) {
    case MessageType::TEXT:
        contentWidget = makeTextMessageItem(isLeft, msg.content);
        break;
    case MessageType::IMAGE:
        contentWidget = makeImageMessageItem(isLeft, msg.content);
        break;
    case MessageType::FILE:
        contentWidget = makeFileMessageItem(isLeft, msg.content);
        break;
    case MessageType::SPEECH:
        contentWidget = makeSpeechMessageItem(isLeft, msg.content);
        break;
    default:
        break;
    }
    if (isLeft) {
        layout->addWidget(contentWidget, 1, 1);
    } else {
        layout->addWidget(contentWidget, 1, 0);
    }

    return item;
}

QWidget *MessageItem::makeTextMessageItem(bool isLeft, const QString &content)
{
    MessageContentLabel *label = new MessageContentLabel(isLeft, content);
    return label;
}

QWidget *MessageItem::makeImageMessageItem(bool isLeft, const QString &content)
{
    return nullptr;
}

QWidget *MessageItem::makeFileMessageItem(bool isLeft, const QString &content)
{
    return nullptr;
}

QWidget *MessageItem::makeSpeechMessageItem(bool isLeft, const QString &content)
{
    return nullptr;
}

MessageContentLabel::MessageContentLabel(bool isLeft, const QString text)
    : isLeft(isLeft)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QFont font;
    font.setFamily("微软雅黑");
    font.setPixelSize(16);

    label = new QLabel(this);
    label->setText(text);
    label->setFont(font);
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    label->setWordWrap(true);
    label->setStyleSheet("QLabel { padding: 0 10px; line-height: 1.2; background-color: transparent; } ");
}

void MessageContentLabel::paintEvent(QPaintEvent *event)
{
    // 获取父元素宽度
    QObject *obj = parent();
    if (!obj->isWidgetType()) {
        return;
    }
    QWidget *parent = dynamic_cast<QWidget*>(obj);
    int width = parent->width() * 0.6;

    // 当前文本长度
    QFontMetrics metrics(label->font());
    int totalWidth = metrics.horizontalAdvance(label->text());

    // 需要行数是多少
    int rows = (totalWidth / (width - 40)) + 1;
    if (rows == 1) {
        width = totalWidth + 40;
    }

    // 计算高度
    int height = rows * (label->font().pixelSize() * 1.2) + 20;

    // 绘制圆形箭头
    QPainter painter(this);
    QPainterPath path;
    // 锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    if (isLeft) {
        painter.setPen(QPen(QColor(255, 255, 255)));
        painter.setBrush(QColor(255, 255, 255));

        painter.drawRoundedRect(10, 0, width, height, 10, 10);
        path.moveTo(10, 15);
        path.lineTo(0, 20);
        path.lineTo(10, 25);
        path.closeSubpath();
        painter.drawPath(path);

        label->setGeometry(10, 0, width, height);
    } else {
        painter.setPen(QPen(QColor(137, 217, 97)));
        painter.setBrush(QColor(137, 217, 97));

        int leftPos = this->width() - width - 10;
        int rightPos = this->width() - 10;
        painter.drawRoundedRect(leftPos, 0, width, height, 10, 10);
        path.moveTo(rightPos, 15);
        path.lineTo(rightPos + 10, 20);
        path.lineTo(rightPos, 25);
        path.closeSubpath();
        painter.drawPath(path);

        label->setGeometry(leftPos, 0, width, height);
    }
    parent->setFixedHeight(height + 50);
}
