#ifndef MESSAGEEDITAREA_H
#define MESSAGEEDITAREA_H

#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>

class MessageEditArea : public QWidget
{
    Q_OBJECT
public:
    explicit MessageEditArea(QWidget *parent = nullptr);

    // 解决区域不生效问题
    void paintEvent(QPaintEvent *event) override;

private:
    QPushButton *sendImageBtn;
    QPushButton *sendFileBtn;
    QPushButton *sendSpeechBtn;
    QPushButton *showHistoryBtn;
    QPlainTextEdit *textEdit;
    QPushButton *sendBtn;
};

#endif // MESSAGEEDITAREA_H
