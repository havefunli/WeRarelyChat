#ifndef SESSIONAREA_H
#define SESSIONAREA_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QScrollArea>
#include <QPushButton>

///////////////////////////////////////////////////

enum ItemType{
    SessionItemType,
    FriendItemType,
    ApplyItemType
};

// 一个基类，衍生出好友、群聊、申请
class SessionFriendItem : public QWidget
{
    Q_OBJECT
public:
    explicit SessionFriendItem(QWidget *owner, const QIcon &avatar, const QString &name, const QString &msg);

    // 解决区域不生效问题
    void paintEvent(QPaintEvent *event) override;

    // 页面修改 + 触发的业务逻辑处理
    void select();
    // 业务处理
    virtual void active();

    // 点击事件
    void mousePressEvent(QMouseEvent *event) override;
    // 鼠标进入
    void enterEvent(QEnterEvent *event) override;
    // 鼠标离开
    void leaveEvent(QEvent *event) override;

private:
    QWidget *owner;    // 属于一个会话区
    bool isSelected;   // 是否选取

protected:
    QPushButton *avatarBtn;
    QLabel *nameLabel;
    QLabel *msgLabel;
};


// 会话 Item 具体实现
class SessionItem : public SessionFriendItem
{
    Q_OBJECT
public:
    SessionItem(QWidget *owner, const QString &chatSessionId, const QIcon &avatar, const QString &name, const QString &msg);
private:
    void active() override;
private:
    QString chatSessionId;
};

// 好友 Item 具体实现
class FriendItem : public SessionFriendItem
{
    Q_OBJECT
public:
    FriendItem(QWidget *owner, const QString &userId, const QIcon &avatar, const QString &name, const QString &description);
private:
    void active() override;
private:
    QString userId;
};


// 申请 Item 具体实现
class ApplyItem : public SessionFriendItem
{
    Q_OBJECT
public:
    ApplyItem(QWidget *owner, const QString &userId, const QIcon &avatar, const QString &name);
private:
    void active() override;
private:
    QString userId;
};

///////////////////////////////////////////////////



class SessionArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit SessionArea(QWidget *parent = nullptr);

    // 添加 Item
    void addItem(ItemType itemType, const QString &id, const QIcon &avatar, const QString &name, const QString &msg);
    // 点击 Item
    void clickedItem(int index);

    // 清空数据
    void clear();

private:
    QWidget *container;
};

#endif // SESSIONAREA_H
