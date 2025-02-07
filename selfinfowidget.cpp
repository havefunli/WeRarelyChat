#include "selfinfowidget.h"
#include "debug.h"

#include <QCursor>
#include <QPushButton>

SelfInfoWidget::SelfInfoWidget(QWidget *parent)
    : QDialog(parent)
{
    setFixedSize(450, 250);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setWindowTitle("个人信息");
    setAttribute(Qt::WA_DeleteOnClose); // 关闭时释放
    move(QCursor::pos()); // 初始在鼠标的位置

    // 使用网格布局管理
    layout = new QGridLayout();
    layout->setSpacing(8);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);

    // 样式设置
    QString labelStyle = "QLabel {font-size: 14px; font-weight: 800;} ";
    QString btnStyle = "QPushButton { border: none; background-color: transparent; }\
                        QPushButton:pressed { background-color:rgb(210, 210, 210); } ";
    QString editStyle = "QLineEdit { border:none; border-radius: 5px; padding-left: 2px}";

    // 高度设置
    int height = 30;

    // 头像
    avatarBtn = new QPushButton();
    avatarBtn->setFixedSize(75, 75);
    avatarBtn->setIconSize(QSize(75, 75));
    avatarBtn->setIcon(QIcon(":/image/avatar.png"));
    avatarBtn->setStyleSheet(btnStyle);

    // ID + 显示数据
    idTag = new QLabel();
    idTag->setFixedHeight(height);
    idTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    idTag->setText("ID");
    idTag->setStyleSheet(labelStyle);

    idLabel = new QLabel();
    idLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // 昵称 + 显示数据 + 编辑框
    nameTag = new QLabel();
    nameTag->setFixedHeight(height);
    nameTag->setText("昵称");
    nameTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    nameTag->setStyleSheet(labelStyle);

    nameLabel = new QLabel();
    nameLabel->setFixedHeight(height);
    nameLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    nameEdit = new QLineEdit();
    nameEdit->setFixedHeight(height);
    nameEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    nameEdit->setStyleSheet(editStyle);
    nameEdit->hide();

    nameModifyBtn = new QPushButton();
    nameModifyBtn->setFixedSize(25, 25);
    nameModifyBtn->setIcon(QIcon(":/image/modify.png"));
    nameModifyBtn->setIconSize(QSize(20, 20));
    nameModifyBtn->setStyleSheet(btnStyle);

    nameSubmitBtn = new QPushButton();
    nameSubmitBtn->setFixedSize(25, 25);
    nameSubmitBtn->setIcon(QIcon(":/image/submit.png"));
    nameSubmitBtn->setIconSize(QSize(20, 20));
    nameSubmitBtn->setStyleSheet(btnStyle);
    nameSubmitBtn->hide();

    // 添加个性签名
    descTag = new QLabel();
    descTag->setFixedHeight(height);
    descTag->setText("签名");
    descTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    descTag->setStyleSheet(labelStyle);

    descLabel = new QLabel();
    descLabel->setFixedHeight(height);
    descLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    descModifyBtn = new QPushButton();
    descModifyBtn->setFixedSize(25, 25);
    descModifyBtn->setIcon(QIcon(":/image/modify.png"));
    descModifyBtn->setIconSize(QSize(20, 20));
    descModifyBtn->setStyleSheet(btnStyle);

    descEdit = new QLineEdit();
    descEdit->setFixedHeight(height);
    descEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    descEdit->setStyleSheet(editStyle);
    descEdit->hide();

    descSubmitBtn = new QPushButton();
    descSubmitBtn->setFixedSize(25, 25);
    descSubmitBtn->setIcon(QIcon(":/image/submit.png"));
    descSubmitBtn->setIconSize(QSize(20, 20));
    descSubmitBtn->setStyleSheet(btnStyle);
    descSubmitBtn->hide();

    // 电话
    phoneTag = new QLabel();
    phoneTag->setFixedHeight(height);
    phoneTag->setText("电话");
    phoneTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    phoneTag->setStyleSheet(labelStyle);

    phoneLabel = new QLabel();
    phoneLabel->setFixedHeight(height);
    phoneLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    phoneModifyBtn = new QPushButton();
    phoneModifyBtn->setFixedSize(25, 25);
    phoneModifyBtn->setIcon(QIcon(":/image/modify.png"));
    phoneModifyBtn->setIconSize(QSize(20, 20));
    phoneModifyBtn->setStyleSheet(btnStyle);

    phoneEdit = new QLineEdit();
    phoneEdit->setFixedHeight(height);
    phoneEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    phoneEdit->setStyleSheet(editStyle);

    phoneSubmitBtn = new QPushButton();
    phoneSubmitBtn->setFixedSize(25, 25);
    phoneSubmitBtn->setIcon(QIcon(":/image/submit.png"));
    phoneSubmitBtn->setIconSize(QSize(20, 20));
    phoneSubmitBtn->setStyleSheet(btnStyle);

    // 验证码
    verifyCodeTag = new QLabel();
    verifyCodeTag->setFixedHeight(height);
    verifyCodeTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    verifyCodeTag->setText("验证码");
    verifyCodeTag->setStyleSheet(labelStyle);

    verifyCodeEdit = new QLineEdit();
    verifyCodeEdit->setFixedHeight(height);
    verifyCodeEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    verifyCodeEdit->setStyleSheet(editStyle);

    getVerifyCodeBtn = new QPushButton();
    getVerifyCodeBtn->setText("获取验证码");


#if TEST_UI
    idLabel->setText("123456789");
    nameLabel->setText("小强");
    descLabel->setText("每天代码一点点！");
    phoneLabel->setText("1522803240");
#endif

    layout->addWidget(avatarBtn, 0, 0, 3, 1);

    layout->addWidget(idTag, 0, 1);
    layout->addWidget(idLabel, 0, 2);

    layout->addWidget(nameTag, 1, 1);
    layout->addWidget(nameLabel, 1, 2);
    layout->addWidget(nameModifyBtn, 1, 3);

    layout->addWidget(descTag, 2, 1);
    layout->addWidget(descLabel, 2, 2);
    layout->addWidget(descModifyBtn, 2, 3);

    layout->addWidget(phoneTag, 3, 1);
    layout->addWidget(phoneLabel, 3, 2);
    layout->addWidget(phoneModifyBtn, 3, 3);

    layout->addWidget(verifyCodeTag, 4, 1);
    layout->addWidget(verifyCodeEdit, 4, 2);
    layout->addWidget(getVerifyCodeBtn, 4, 3);

    initConnect();
}

void SelfInfoWidget::initConnect()
{
    connect(nameModifyBtn, &QPushButton::clicked, this, [=]() {
        // 移除当前的
        nameLabel->hide();
        nameModifyBtn->hide();
        // layout->removeWidget(nameLabel);
        // layout->removeWidget(nameModifyBtn);
        // 展示最新的
        nameEdit->show();
        nameEdit->setText(nameLabel->text());
        nameSubmitBtn->show();
        layout->addWidget(nameEdit, 1, 2);
        layout->addWidget(nameSubmitBtn, 1, 3);
    });

    connect(descModifyBtn, &QPushButton::clicked, this, [=]() {
        // 移除当前的
        descLabel->hide();
        descModifyBtn->hide();
        // layout->removeWidget(nameLabel);
        // layout->removeWidget(nameModifyBtn);
        // 展示最新的
        descEdit->show();
        descEdit->setText(descLabel->text());
        descSubmitBtn->show();
        layout->addWidget(descEdit, 2, 2);
        layout->addWidget(descSubmitBtn, 2, 3);
    });

    connect(phoneModifyBtn, &QPushButton::clicked, this, [=]() {
        // 移除当前的
        phoneLabel->hide();
        phoneModifyBtn->hide();
        // layout->removeWidget(nameLabel);
        // layout->removeWidget(nameModifyBtn);
        // 展示最新的
        phoneEdit->show();
        phoneEdit->setText(phoneLabel->text());
        phoneSubmitBtn->show();
        layout->addWidget(phoneEdit, 3, 2);
        layout->addWidget(phoneSubmitBtn, 3, 3);
    });
}

