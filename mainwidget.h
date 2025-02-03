#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

    // 记录当前的标签页
    enum ActivePage {
        SESSION,
        FRIENDS,
        APPLY
    };

public:
    ~MainWidget();

    static MainWidget *getInstance();

private:
    // 私有构造函数
    MainWidget(QWidget *parent = nullptr);

    // 初始化窗口
    void initMainWindow();
    void initLeftWindow();
    void initMidWindow();
    void initRightWindow();

    // 初始化信号槽
    void initConnect();

    // 加载对应界面的数据
    void loadSessionData();
    void loadFriendsData();
    void loadApplyData();

private slots:
    // 页面点击切换的槽函数
    void switchToSession();
    void switchToFriends();
    void switchToApply();

private:
    Ui::MainWidget *ui;
    static MainWidget *self;

    ActivePage page;        // 当前所处在的页

    QWidget *windowLeft;    // 左侧窗口
    QWidget *windowMid;     // 中间窗口
    QWidget *windowRight;   // 右侧窗口

    QPushButton *userAvatar;// 用户头像
    QPushButton *sessionBtn;// 会话按钮
    QPushButton *friendsBtn;// 好友按钮
    QPushButton *applyBtn;  // 好友申请按钮

    QLineEdit *searchEdit;  // 搜索框
    QPushButton *addBtn;    // 增加好友
};
#endif // MAINWIDGET_H
