#ifndef RICHTEXTEDIT_H
#define RICHTEXTEDIT_H
/**
 * 拖拽: 1. 拖拽文件到文本框中，显示图片
 * 
 */

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QMimeData>
#include <QSharedPointer>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QFileInfo>
#include <QToolBar>
#include <QVBoxLayout>
#include <QTextDocument>
#include <QPair>
#include <QTextBlock>
#include <QAction>
#include <QMenu>
#include <QFileDialog>

#define FONT_SIZE 16

class RichTextEdit : public QWidget
{
    Q_OBJECT
public:
    RichTextEdit(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    bool canDrop(QDropEvent *event);
    void addPicture(const QImage &image);
    void dropPicture(const QMimeData *source);
    void addToolBarActions();
    bool checkBold();
    bool checkItalic();
    bool checkUnderline();
    bool checkStrikeOut();
    void adjustSize();
    void checkFontSize();
    QImage fitImage(const QImage &image);


    QSharedPointer<QTextEdit> textEdit;
    QSharedPointer<QToolBar> toolBar;
    QStringList acceptedFileTypes;
    QAction *boldAction;
    QAction *italicAction;
    QAction *underlineAction;
    QAction *strikeOutAction;
    QAction *increaseTextSizeAction;
    QAction *decreaseTextSizeAction;
    QAction *undoAction;
    QAction *redoAction;
    QAction *insertImageAction;

    bool isUpdatingText = false;
    int previousTextLength = 0;

private slots:
    void onTextChanged();
    void onCursorPositionChanged();
    void onSelectionChanged();

};

#endif // RICHTEXTEDIT_H
