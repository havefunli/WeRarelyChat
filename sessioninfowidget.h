#ifndef SESSIONINFOWIDGET_H
#define SESSIONINFOWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QLabel>

// 头像结合昵称控件
class AvatarItem: public QWidget
{
    Q_OBJECT
public:
    AvatarItem(const QIcon &avatar, const QString &name);

    QPushButton *getAvatar();

private:
    QPushButton *avatarBtn;
    QLabel *nameLabel;
};

class SessionInfoWidget : public QDialog
{
    Q_OBJECT
public:
    SessionInfoWidget(QWidget *parent);
};

#endif // SESSIONINFOWIDGET_H
