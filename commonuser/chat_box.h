#ifndef CHAT_BOX_H
#define CHAT_BOX_H

#include<QPainter>
#include<QFileDialog>
#include<QImageReader>
#include <QListWidgetItem>
#include <QWidget>
#include<qnchatmessage.h>

namespace Ui {
class chat_box;
}

class chat_box : public QWidget
{
    Q_OBJECT

public:
    explicit chat_box(QWidget *parent = nullptr);
    ~chat_box();
    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    Ui::chat_box *ui;
};

#endif // CHAT_BOX_H
