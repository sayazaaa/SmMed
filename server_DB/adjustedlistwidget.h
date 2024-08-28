#ifndef ADJUSTEDLISTWIDGET_H
#define ADJUSTEDLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QResizeEvent>

class adjustedListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit adjustedListWidget(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;




signals:

};

#endif // ADJUSTEDLISTWIDGET_H
