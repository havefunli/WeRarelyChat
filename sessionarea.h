#ifndef SESSIONAREA_H
#define SESSIONAREA_H

#include <QWidget>
#include <QPainter>
#include <QScrollArea>


class SessionItem : public QWidget
{
    Q_OBJECT
public:
    explicit SessionItem(QWidget *owner, const QIcon &avatar, const QString &name, const QString &msg);

    // 解决区域不生效问题
    void paintEvent(QPaintEvent *event) override;

private:
    QWidget *owner;    // 属于一个会话区
    bool isSelected;   // 是否选取
};


class SessionArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit SessionArea(QWidget *parent = nullptr);

    // 添加 Item
    void addItem(const QIcon &avatar, const QString &name, const QString &msg);

    // 清空数据
    void clear();

private:
    QWidget *container;
};

#endif // SESSIONAREA_H
