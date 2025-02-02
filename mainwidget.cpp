#include "mainwidget.h"
#include "./ui_mainwidget.h"

MainWidget* MainWidget::self = nullptr;

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/wechat.png"));
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
