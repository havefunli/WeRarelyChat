#ifndef MESSAGEAREA_H
#define MESSAGEAREA_H

#include "model/data.h"

#include <QScrollArea>
#include <QWidget>
#include <QLabel>

using model::Message;

class MessageArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit MessageArea();
    // 尾插数据
    void addMessage(bool isLeft, const Message &msg);
    // 头插数据
    void addMessageFront(bool isLeft, const Message &msg);
    // 清空数据
    void clear();

private:
    QWidget *container;
};

// 消息样式设计
class MessageItem : public QWidget {
    Q_OBJECT
public:
    MessageItem(bool isLeft);

    // 通过工厂创建 MessageItem 实例
    static MessageItem *makeMessageItem(bool isLeft, const Message &msg);

    static QWidget *makeTextMessageItem(bool isLeft, const QString& content);
    static QWidget *makeImageMessageItem(bool isLeft, const QString& content);
    static QWidget *makeFileMessageItem(bool isLeft, const QString& content);
    static QWidget *makeSpeechMessageItem(bool isLeft, const QString& content);

private:
    bool isLeft;
};

// 气泡设计
class MessageContentLabel : public QWidget {
    Q_OBJECT
public:
    MessageContentLabel(bool isLeft, const QString text);

    void paintEvent(QPaintEvent *event) override;

private:
    bool isLeft;
    QLabel *label;
};

#endif // MESSAGEAREA_H
