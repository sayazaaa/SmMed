#ifndef RICHTEXTEDIT_H
#define RICHTEXTEDIT_H

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
#include <QTemporaryDir>
#include <QTemporaryFile>
#include <QProcess>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextDocumentWriter>
#include <QInputDialog>
#include <QTextDocumentFragment>

#define FONT_SIZE 16

class RichTextEdit : public QWidget
{
    Q_OBJECT
public:
    RichTextEdit(QWidget *parent = nullptr);
    void readonly(bool b);
    bool save(QUrl url);
    bool load(QUrl url);

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
    QAction *insertTableAction;
    QAction *insertImageAction;
    QAction *saveAction;

    bool isUpdatingText = false;
    int previousTextLength = 0;

private slots:
    void onTextChanged();
    void onCursorPositionChanged();
    void onSelectionChanged();

};

#endif // RICHTEXTED