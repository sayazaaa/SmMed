#include "adjustedlistwidget.h"

adjustedListWidget::adjustedListWidget(QWidget *parent) : QListWidget(parent)
{
    //自动换行
    setWrapping(true);
    //从左到右分布
    setFlow(QListView::LeftToRight);
    //不可拖动
    setDragEnabled(false);
    //设置每个子项的大小固定
    setUniformItemSizes(false);
    //设置QLisView大小改变时，图标的调整模式为自动调整
    setResizeMode(QListView::Adjust);
    //设置每个子项之间的间距
    setSpacing(0);
}
void adjustedListWidget::resizeEvent(QResizeEvent *event)
{
    int itemWidth = event->size().width() / 3-10; // 计算每个item的宽度
    int itemHeight = event->size().height() / 3; // 计算每个item的高度
    int n=count();
    for(int i=0;i<n;i++)
    {
        QListWidgetItem* aitem = item(i);
        aitem->setSizeHint(QSize(itemWidth, itemHeight));
    }
//    setGridSize(QSize(itemWidth, itemHeight)); // 设置item的大小
    QListWidget::resizeEvent(event); // 调用基类的resizeEvent
}
