#include "messageeditarea.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MessageEditArea::MessageEditArea(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedHeight(200);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // 控件之间使用垂直布局
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    vLayout->setContentsMargins(0, 0, 20, 15);
    setLayout(vLayout);

    // 四个功能按钮使用水平布局
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setSpacing(10);
    hLayout->setContentsMargins(15, 0, 0, 0);
    hLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    vLayout->addLayout(hLayout);
    // 四个按钮设置
    QString btnStyle = "QPushButton {background-color: rgb(245, 245, 245); border: none;}\
                        QPushButton:pressed {background-color: rgb(255, 255, 255);}";
    auto initBtn = [&btnStyle](QPushButton* &btn, const QString &path){
        btn = new QPushButton();
        btn->setFixedSize(35, 35);
        btn->setIcon(QIcon(path));
        btn->setIconSize(QSize(25, 25));
        btn->setStyleSheet(btnStyle);
    };
    // 分别初始化
    initBtn(sendImageBtn, ":/image/image.png");
    hLayout->addWidget(sendImageBtn);
    initBtn(sendFileBtn, ":image/file.png");
    hLayout->addWidget(sendFileBtn);
    initBtn(sendSpeechBtn, ":/image/speech.png");
    hLayout->addWidget(sendSpeechBtn);
    initBtn(showHistoryBtn, ":/image/history.png");
    hLayout->addWidget(showHistoryBtn);

    // 编辑文本框
    textEdit = new QPlainTextEdit();
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    textEdit->setStyleSheet("QPlainTextEdit {border: none; background-color: transparent; font-size: 18px; padding: 15px; } ");
    vLayout->addWidget(textEdit);

    sendBtn = new QPushButton();
    sendBtn->setText("发送");
    sendBtn->setFixedSize(120, 40);
    sendBtn->setStyleSheet("QPushButton {font-size: 16px; color: rgb(7, 193, 96); \
                                        border: none; border-radius: 10px; background-color: rgb(233, 233, 233);}\
                            QPushButton:hover {background-color: rgb(210, 210, 210); }\
                            QPushButton:pressed {background-color: rgb(190, 190, 190); }");
    vLayout->addWidget(sendBtn, 0, Qt::AlignRight);
}
