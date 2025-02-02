#pragma once

#include <QString>
#include <QDebug>
#include <QIcon>
#include <QFile>
#include <QUuid>
#include <QDateTime>

namespace model{

// 工具类
class Util{
public:
    // 将时间戳转化为时间字符串
    static inline QString formatTime() {
        QDateTime dateTime = QDateTime::currentDateTime();
        return dateTime.toString("MM-dd HH:mm:ss");
    }

    // 将 QByteArray 转化为 QIcon
    static inline QIcon makeIcon(const QByteArray& byteArray) {
        QPixmap pixmap;
        pixmap.loadFromData(byteArray);
        return QIcon(pixmap);
    }

    // 加载文件
    static inline QByteArray loadFileToByteArray(const QString& path) {
        QFile file(path);
        if (!file.open(QFile::ReadOnly)) {
            qDebug() << "Open file = " << path << " failed";
            return "";
        }
        QByteArray content(file.readAll());
        file.close();
        return content;
    }

    // 写入文件
    static inline void writeByteArrayToFile(const QString& path, const QByteArray& byteArray) {
        QFile file(path);
        if (!file.open(QFile::WriteOnly)) {
            qDebug() << "Open file = " << path << " failed";
            return;
        }

        if (file.write(byteArray) < 0) {
            qDebug() << "write file = " << path << " failed";
            return;
        }
        file.flush();
        file.close();
        return;
    }
};


// 用户字段
class UserInfo {
public:
    QString userId;       // 用户编号
    QString nickName;     // 用户昵称
    QString description;  // 个性签名
    QString phoneNum;     // 电话号码
    QIcon avatar;         // 用户头像
};

// 消息类型
enum MessageType {
    TEXT,   // 文本
    IMAGE,  // 图片
    SPEECH, // 语音
    FILE    // 文件
};


// 消息字段
class Message {
public:
    QString messageId;     // 消息编号
    QString chatSessionID; // 所属的会话
    QString time;          // 发送时间
    UserInfo sender;       // 发送者
    MessageType type;      // 信息类型
    QByteArray content;    // 消息内容
    QString fileId;        // 文件标识符
    QString fileName;      // 文件名称（文件有效）

    // 使用工厂模式构造对象
    static Message makeMessage(MessageType type, const QString& chatSessionId, const UserInfo& sender,
                               const QByteArray& content, const QString& extraInfo) {
        switch (type) {
        case TEXT:
            return makeTextMessage(chatSessionId, sender, content);
        case IMAGE:
            return makeImageMessage(chatSessionId, sender, content);
        case FILE:
            return makeFileMessage(chatSessionId, sender, content, extraInfo);
        case SPEECH:
            return makeSpeechMessage(chatSessionId, sender, content);
        default:
            return Message();
        }
    }

    static QString makeId() {
        // 截取一部分作为标识符，头部加上 M 代表信息
        return "M" + QUuid::createUuid().toString().sliced(25, 12);
    }

    static Message makeTextMessage(const QString& chatSessionId, const UserInfo& sender, const QByteArray& content) {
        Message msg;
        // 填充内部字段
        msg.messageId = makeId();
        msg.chatSessionID = chatSessionId;
        msg.sender = sender;
        msg.content = content;
        msg.time = Util::formatTime();
        msg.type = TEXT;

        return msg;
    }

    static Message makeImageMessage(const QString& chatSessionId, const UserInfo& sender, const QByteArray& content) {
        Message msg;
        // 填充内部字段
        msg.messageId = makeId();
        msg.chatSessionID = chatSessionId;
        msg.sender = sender;
        msg.content = content;
        msg.time = Util::formatTime();
        msg.type = IMAGE;

        return msg;
    }

    static Message makeFileMessage(const QString& chatSessionId, const UserInfo& sender, const QByteArray& content, const QString& extraInfo) {
        Message msg;
        // 填充内部字段
        msg.messageId = makeId();
        msg.chatSessionID = chatSessionId;
        msg.sender = sender;
        msg.content = content;
        msg.time = Util::formatTime();
        msg.type = FILE;
        msg.fileName = extraInfo;

        return msg;
    }

    static Message makeSpeechMessage(const QString& chatSessionId, const UserInfo& sender, const QByteArray& content) {
        Message msg;
        // 填充内部字段
        msg.messageId = makeId();
        msg.chatSessionID = chatSessionId;
        msg.sender = sender;
        msg.content = content;
        msg.time = Util::formatTime();
        msg.type = SPEECH;

        return msg;
    }
};
} // model end
