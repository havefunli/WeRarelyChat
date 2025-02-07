#ifndef USRINFOWIDGET_H
#define USRINFOWIDGET_H

#include "model/data.h"

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

using model::UserInfo;

class UsrInfoWidget : public QDialog
{
    Q_OBJECT
public:
    UsrInfoWidget(QWidget *parent, const UserInfo &user);
private:
    UserInfo usr;

    QPushButton *avatarBtn;

    QLabel *idTag;
    QLabel *idLabel;

    QLabel *nameTag;
    QLabel *nameLabel;

    QLabel *phoneTag;
    QLabel *phoneLabel;

    QPushButton *applyBtn;
    QPushButton *sendMsgBtn;
    QPushButton *delFriendBtn;
};

#endif // USRINFOWIDGET_H
