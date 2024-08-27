#ifndef ZHIHULISTWIDGET_H
#define ZHIHULISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QResizeEvent>

class zhihuListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit zhihuListWidget(QWidget *parent = nullptr);



protected:
    void resizeEvent(QResizeEvent *event) override;


signals:
};

#endif // ZHIHULISTWIDGET_H
