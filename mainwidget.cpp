#include "mainwidget.h"
#include "./ui_mainwidget.h"
#include "sessionarea.h"
#include "sessioninfowidget.h"
#include "selfinfowidget.h"
#include "debug.h"


#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QIcon>

MainWidget* MainWidget::self = nullptr;

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , page(ActivePage::SESSION)
{
    ui->setupUi(this);

    // 初始化主窗口
    initMainWindow();
    // 初始化左窗口
    initLeftWindow();
    // 初始化中间窗口
    initMidWindow();
    // 初始化右窗口
    initRightWindow();
    // 初始化槽函数
    initConnect();
}

void MainWidget::initMainWindow()
{
    // 窗口小图标
    setWindowTitle("聊天室");
    setWindowIcon(QIcon(":/image/wechat.png"));

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);                    // 空间之间紧挨
    layout->setContentsMargins(0, 0, 0, 0);   // 四周占满
    this->setLayout(layout);

    // 创建窗口，设置大小
    windowLeft = new QWidget();
    windowLeft->setStyleSheet("QWidget {background-color:#C5C5C7}");  // Incorrect due to extra braces
    windowLeft->setFixedWidth(70);

    windowMid = new QWidget();
    windowMid->setFixedWidth(320);

    windowRight = new QWidget();
    windowRight->setMinimumWidth(800); // 可拉长

    layout->addWidget(windowLeft);
    layout->addWidget(windowMid);
    layout->addWidget(windowRight);
}

void MainWidget::initLeftWindow()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(20);
    layout->setContentsMargins(0, 30, 0, 0);
    windowLeft->setLayout(layout);

    // 使用 lambda 函数来设置几个控件
    auto func = [](QPushButton* &btn, const QString &path){
        btn = new QPushButton();
        btn->setFixedSize(45, 45);
        btn->setIcon(QIcon(path));
        btn->setIconSize(QSize(25, 25));
        btn->setStyleSheet("QPushButton {background-color:transparent;\
                                        border-radius:none;}");
    };

    // 设置几个控件格式
    func(userAvatar, ":/image/avatar.png");
    func(sessionBtn, ":/image/session_a.png");
    func(friendsBtn, ":/image/friend_b.png");
    func(applyBtn, ":/image/add_b.png");

    layout->addWidget(userAvatar, 1, Qt::AlignTop | Qt::AlignHCenter);
    layout->addWidget(sessionBtn, 1, Qt::AlignTop | Qt::AlignHCenter);
    layout->addWidget(friendsBtn, 1, Qt::AlignTop | Qt::AlignHCenter);
    layout->addWidget(applyBtn, 1, Qt::AlignTop | Qt::AlignHCenter);
    // 加一个弹簧填充底部
    layout->addStretch(20);
}

void MainWidget::initMidWindow()
{
    QGridLayout *layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 20, 0, 0);
    windowMid->setLayout(layout);

    searchEdit = new QLineEdit();
    searchEdit->setFixedHeight(30);
    searchEdit->setPlaceholderText("搜索");
    searchEdit->setStyleSheet("QLineEdit {border-radius: 5px; \
                                        background-color:rgb(226, 226, 226);\
                                        padding-left: 10px;}");

    addBtn = new QPushButton();
    addBtn->setFixedSize(25, 25);
    addBtn->setIcon(QIcon(":/image/add.png"));
    addBtn->setStyleSheet("QPushButton {border-radius:5px; \
                                        background-color: rbg(226, 226, 226);\
                                        QPushButtn:pressed {background-color: rgb(240, 240, 240);}}");


    SessionArea *sessionArea = new SessionArea();

    // 使用 QWidget 来作为分隔符
    QWidget *spacer1 = new QWidget();
    spacer1->setFixedWidth(10);
    QWidget *spacer2 = new QWidget();
    spacer2->setFixedWidth(15);
    QWidget *spacer3 = new QWidget();
    spacer3->setFixedWidth(15);
    QWidget *spacer4 = new QWidget();
    spacer4->setFixedHeight(10);

    layout->addWidget(spacer2, 0, 0);
    layout->addWidget(searchEdit, 0, 1);
    layout->addWidget(spacer1, 0, 2);
    layout->addWidget(addBtn, 0, 3);
    layout->addWidget(spacer3, 0, 4);
    layout->addWidget(spacer4, 1, 0, 1, 5);
    layout->addWidget(sessionArea, 2, 0, 1, 5); // 踩坑了，需要占满列数
}

void MainWidget::initRightWindow()
{
    // 右侧整体垂直布局
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setAlignment(Qt::AlignTop);
    windowRight->setLayout(vLayout);

    // 标题栏设置
    QWidget *titleWidget = new QWidget();
    titleWidget->setFixedHeight(62);
    titleWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    titleWidget->setStyleSheet("QWidget { border-bottom: 1px solid rgb(230, 230, 230); }");             // 下边框
    vLayout->addWidget(titleWidget);

    // 内部是水平布局的包含一个 title 和 setting
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setSpacing(0);
    hLayout->setContentsMargins(15, 0, 10, 0);
    titleWidget->setLayout(hLayout);
    // 标题
    QLabel *titleLabel = new QLabel();
    titleLabel->setStyleSheet("QLabel { font-size: 22px; }");
#if TEST_UI
    titleLabel->setText("这个测试会话");
#endif
    hLayout->addWidget(titleLabel);
    // 额外设置
    extraBtn = new QPushButton();
    extraBtn->setFixedSize(20, 20);
    extraBtn->setIcon(QIcon(":/image/more.png"));
    extraBtn->setIconSize(QSize(20, 20));
    extraBtn->setStyleSheet("QPushButton { border:none; \
                                        background-color: rgb(245, 245, 245);}\
                            QPushButton:pressed {background-color: rgb(220, 220, 220);}");
    hLayout->addWidget(extraBtn);

    // 消息展示
    msgArea = new MessageArea();
    vLayout->addWidget(msgArea);

    // 消息编辑
    editArea = new MessageEditArea();
    vLayout->addWidget(editArea, 0, Qt::AlignBottom);
}

void MainWidget::initConnect()
{
    // 页面点击切换
    connect(sessionBtn, &QPushButton::clicked, this, &MainWidget::switchToSession);
    connect(friendsBtn, &QPushButton::clicked, this, &MainWidget::switchToFriends);
    connect(applyBtn, &QPushButton::clicked, this, &MainWidget::switchToApply);

    // 点击头像显示信息
    connect(userAvatar, &QPushButton::clicked, this, [this](){
        SelfInfoWidget *selfInfo = new SelfInfoWidget(this);
        selfInfo->exec();
    });

    // 消息详情按钮
    connect(extraBtn, &QPushButton::clicked, this, [this](){
        SessionInfoWidget *inforWidget = new SessionInfoWidget(this);
        inforWidget->exec();
    });
}

void MainWidget::loadSessionData()
{

}

void MainWidget::loadFriendsData()
{

}

void MainWidget::loadApplyData()
{

}

void MainWidget::switchToSession()
{
    page = SESSION;
    // 图标显示
    sessionBtn->setIcon(QIcon(":/image/session_a.png"));
    friendsBtn->setIcon(QIcon(":/image/friend_b.png"));
    applyBtn->setIcon(QIcon(":/image/add_b.png"));
    // 加载对应数据
    loadSessionData();
}

void MainWidget::switchToFriends()
{
    page = FRIENDS;
    // 图标显示
    sessionBtn->setIcon(QIcon(":/image/session_b.png"));
    friendsBtn->setIcon(QIcon(":/image/friend_a.png"));
    applyBtn->setIcon(QIcon(":/image/add_b.png"));
    // 加载对应数据
    loadFriendsData();
}

void MainWidget::switchToApply()
{
    page = APPLY;
    // 图标显示
    sessionBtn->setIcon(QIcon(":/image/session_b.png"));
    friendsBtn->setIcon(QIcon(":/image/friend_b.png"));
    applyBtn->setIcon(QIcon(":/image/add_a.png"));
    // 加载对应数据
    loadApplyData();
}


MainWidget::~MainWidget()
{
    delete ui;
}

MainWidget *MainWidget::getInstance()
{
    if (self == nullptr) {
        self = new MainWidget(nullptr);
    }
    return self;
}
