#ifndef SESSIONAREA_H
#define SESSIONAREA_H

#include <QWidget>
#include <QPainter>
#include <QScrollArea>


class SessionFriendItem : public QWidget
{
    Q_OBJECT
public:
    explicit SessionFriendItem(QWidget *owner, const QIcon &avatar, const QString &name, const QString &msg);

    // 解决区域不生效问题
    void paintEvent(QPaintEvent *event) override;

    void select();

    // 点击事件
    void mousePressEvent(QMouseEvent *event) override;
    // 鼠标进入
    void enterEvent(QEnterEvent *event) override;
    // 鼠标离开
    void leaveEvent(QEvent *event) override;

private:
    QWidget *owner;    // 属于一个会话区
    bool isSelected;   // 是否选取
};


// 会话 Item 具体实现
class SessionItem : public SessionFriendItem
{
    Q_OBJECT
public:
    SessionItem(QWidget *owner, const QString &chatSessionId, const QIcon &avatar, const QString &name, const QString &msg);
private:
    QString chatSessionId;
};


class SessionArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit SessionArea(QWidget *parent = nullptr);

    // 添加 Item
    void addItem(const QIcon &avatar, const QString &name, const QString &msg);
    // 点击 Item
    void clickedItem(int index);

    // 清空数据
    void clear();

private:
    QWidget *container;
};

#endif // SESSIONAREA_H
