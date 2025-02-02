#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    ~MainWidget();

    static MainWidget *getInstance();

private:
    Ui::MainWidget *ui;
    static MainWidget *self;
    // 私有构造函数
    MainWidget(QWidget *parent = nullptr);

    QWidget *windowLeft;    // 左侧窗口
    QWidget *windowMid;     // 中间窗口
    QWidget *windowRight;   // 右侧窗口

    QPushButton *userAvatar;// 用户头像
    QPushButton *sessionBtn;// 会话按钮
    QPushButton *friendsBtn;// 好友按钮
    QPushButton *applyBtn;  // 好友申请按钮
};
#endif // MAINWIDGET_H
