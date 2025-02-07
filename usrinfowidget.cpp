#include "usrinfowidget.h"
#include <qgridlayout.h>

UsrInfoWidget::UsrInfoWidget(QWidget *parent, const UserInfo &user)
    : QDialog(parent)
    , usr(user)
{
    // 属性
    setFixedSize(400, 200);
    setWindowTitle("用户信息");
    setAttribute(Qt::WA_DeleteOnClose);
    move(QCursor().pos());

    QGridLayout *layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    // 头像
    avatarBtn = new QPushButton();
    avatarBtn->setFixedSize(75, 75);
    avatarBtn->setIcon(QIcon(usr.avatar));
    avatarBtn->setIconSize(QSize(75, 75));

    // ID
    idTag = new QLabel();
    idTag->setText("ID");

}
