#include "richtextedit.h"
#include "tabletoolbarpopup.h"

#include<qdebug.h>
RichTextEdit::RichTextEdit(QWidget* parent) {
    setAcceptDrops(true);

    textEdit = QSharedPointer<QTextEdit>::create(parent);
    textEdit->setAcceptDrops(false);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setStyleSheet("QTextEdit { padding: 10%; background-color: #ffffff; }");
    checkFontSize();


    toolBar = QSharedPointer<QToolBar>::create(parent);
    toolBar->setAcceptDrops(false);
    toolBar->setFloatable(false);
    toolBar->setMovable(false);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(toolBar.get());
    layout->addWidget(textEdit.get());

    acceptedFileTypes << "jpg" << "jpeg" << "png" << "bmp";

    addToolBarActions();


    connect(textEdit.get(), &QTextEdit::textChanged, this, &RichTextEdit::onTextChanged);
    connect(textEdit.get(), &QTextEdit::cursorPositionChanged, this, &RichTextEdit::onCursorPositionChanged);
    connect(textEdit.get(), &QTextEdit::selectionChanged, this, &RichTextEdit::onSelectionChanged);
}

void RichTextEdit::dragEnterEvent(QDragEnterEvent* event) {
    if (canDrop(event)) {
        event->acceptProposedAction();
    }
}

void RichTextEdit::dropEvent(QDropEvent* event) {
    dropPicture(event->mimeData());
}

void RichTextEdit::resizeEvent(QResizeEvent* event) {
    adjustSize();
}

bool RichTextEdit::canDrop(QDropEvent* event) {
    if (event->mimeData()->hasUrls() && event->mimeData()->urls().count() == 1) {
        QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
        if (acceptedFileTypes.contains(file.suffix().toLower())) {
            event->acceptProposedAction();
        }
    }
    return false;
}

void RichTextEdit::addPicture(const QImage& image) {

    QTextCursor cursor = textEdit->textCursor();
    cursor.insertImage(image);
    adjustSize();
}

void RichTextEdit::addToolBarActions() {
    boldAction = toolBar->addAction(QIcon(":/icons/format_bold.svg"), "加粗", [this]() {
        QTextCursor cursor = textEdit->textCursor();
        if (!cursor.hasSelection()) {
            QTextCharFormat boldFormat;
            boldFormat.setFontWeight(QFont::Bold);
            QTextCharFormat normalFormat;
            normalFormat.setFontWeight(QFont::Normal);
            if (boldAction->isChecked()) {
                qDebug() << "bold";
                cursor.mergeCharFormat(boldFormat);
            }
            else {
                qDebug() << "normal";
                cursor.mergeCharFormat(normalFormat);
            }
            textEdit->setTextCursor(cursor);
            return;
        }
        QTextCharFormat format(cursor.charFormat());
        QTextCharFormat currentFormat = cursor.charFormat();
        bool isBold = this->checkBold();

        format.setFontWeight(isBold ? QFont::Normal : QFont::Bold);
        cursor.mergeCharFormat(format);
        });
    boldAction->setCheckable(true);

    italicAction = toolBar->addAction(QIcon(":/icons/format_italic.svg"), "斜体", [this]() {
        QTextCursor cursor = textEdit->textCursor();
        if (!cursor.hasSelection()) {
            QTextCharFormat italicFormat;
            italicFormat.setFontItalic(true);
            QTextCharFormat normalFormat;
            normalFormat.setFontItalic(false);
            if (italicAction->isChecked()) {
                cursor.mergeCharFormat(italicFormat);
            }
            else {
                cursor.mergeCharFormat(normalFormat);
            }
            textEdit->setTextCursor(cursor);
            return;
        }
        QTextCharFormat format(cursor.charFormat());
        QTextCharFormat currentFormat = cursor.charFormat();
        bool isItalic = this->checkItalic();

        format.setFontItalic(!isItalic);
        cursor.mergeCharFormat(format);
        });
    italicAction->setCheckable(true);

    underlineAction = toolBar->addAction(QIcon(":/icons/format_underlined.svg"), "下划线", [this]() {
        QTextCursor cursor = textEdit->textCursor();
        if (!cursor.hasSelection()) {
            QTextCharFormat underlineFormat;
            underlineFormat.setFontUnderline(true);
            QTextCharFormat normalFormat;
            normalFormat.setFontUnderline(false);
            if (underlineAction->isChecked()) {
                cursor.mergeCharFormat(underlineFormat);
            }
            else {
                cursor.mergeCharFormat(normalFormat);
            }
            textEdit->setTextCursor(cursor);
            return;
        }
        QTextCharFormat format(cursor.charFormat());
        QTextCharFormat currentFormat = cursor.charFormat();
        bool isUnderline = this->checkUnderline();

        format.setFontUnderline(!isUnderline);
        cursor.mergeCharFormat(format);
        });
    underlineAction->setCheckable(true);

    strikeOutAction = toolBar->addAction(QIcon(":/icons/format_strikethrough.svg"), "删除线", [this]() {
        QTextCursor cursor = textEdit->textCursor();
        if (!cursor.hasSelection()) {
            QTextCharFormat strikeOutFormat;
            strikeOutFormat.setFontStrikeOut(true);
            QTextCharFormat normalFormat;
            normalFormat.setFontStrikeOut(false);
            if (strikeOutAction->isChecked()) {
                cursor.mergeCharFormat(strikeOutFormat);
            }
            else {
                cursor.mergeCharFormat(normalFormat);
            }
            textEdit->setTextCursor(cursor);
            return;
        }
        QTextCharFormat format(cursor.charFormat());
        QTextCharFormat currentFormat = cursor.charFormat();
        bool isStrikeOut = this->checkStrikeOut();

        format.setFontStrikeOut(!isStrikeOut);
        cursor.mergeCharFormat(format);
        });
    strikeOutAction->setCheckable(true);

    increaseTextSizeAction = toolBar->addAction(QIcon(":/icons/text_increase.svg"), "增大字体", [this]() {
        QTextCursor cursor = textEdit->textCursor();
        QTextCursor tempCursor = cursor;
        tempCursor.setPosition(cursor.selectionEnd());
        QTextCharFormat format(tempCursor.charFormat());
        format.setFontPointSize(format.fontPointSize() + 1);
        cursor.mergeCharFormat(format);
        });

    decreaseTextSizeAction = toolBar->addAction(QIcon(":/icons/text_decrease.svg"), "减小字体", [this]() {
        QTextCursor cursor = textEdit->textCursor();
        QTextCursor tempCursor = cursor;
        tempCursor.setPosition(cursor.selectionEnd());
        QTextCharFormat format(tempCursor.charFormat());
        format.setFontPointSize((format.fontPointSize() - 1) < 1 ? 1 : format.fontPointSize() - 1);
        cursor.mergeCharFormat(format);
        });

    undoAction = toolBar->addAction(QIcon(":/icons/undo.svg"), "撤销", [this]() {
        textEdit->undo();
        });

    redoAction = toolBar->addAction(QIcon(":/icons/redo.svg"), "重做", [this]() {
        textEdit->redo();
        });

    insertTableAction = toolBar->addAction(QIcon(":/icons/table.svg"), "插入表格", [this]() {
        TableToolBarPopup* popup = new TableToolBarPopup(this);
        connect(popup, &TableToolBarPopup::accepted, [this, popup]() {
            int rows = popup->rows();
            int columns = popup->columns();
            QTextCursor cursor = textEdit->textCursor();
            cursor.insertTable(rows, columns);
            popup->deleteLater();
            });
        connect(popup, &TableToolBarPopup::rejected, [popup]() {
            popup->deleteLater();
            });

        // 显示弹出框
        popup->setWindowFlags(Qt::Popup);
        popup->setAttribute(Qt::WA_DeleteOnClose);
        popup->move(QCursor::pos());
        popup->show();

        });

    insertImageAction = toolBar->addAction(QIcon(":icons/add_photo.svg"), "插入图片", [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, "选择图片", "", "Images (*.png *.jpg *.jpeg *.bmp)");
        if (!fileName.isEmpty()) {
            QImage image(fileName);
            addPicture(image);
        }
        });

    saveAction = toolBar->addAction(QIcon(":/icons/save.svg"), "保存", [this]() {
        QUrl saveUrl = QFileDialog::getSaveFileUrl(this, "保存文件", QUrl(), "ZIP Files (*.zip)");
        qDebug() << "saveUrl: " << saveUrl;
        if (!saveUrl.isEmpty()) {
            save(saveUrl);
        }
        });
}


bool RichTextEdit::checkBold() {
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection()) {
        return false;
    }
    QTextCursor tempCursor = cursor;
    tempCursor.setPosition(cursor.selectionStart());
    while (tempCursor.position() < cursor.selectionEnd()) {
        tempCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        if (tempCursor.charFormat().fontWeight() != QFont::Bold) {
            return false;
        }
    }
    return true;
}

bool RichTextEdit::checkItalic() {
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection()) {
        return false;
    }

    QTextCursor tempCursor = cursor;
    tempCursor.setPosition(cursor.selectionStart());
    while (tempCursor.position() < cursor.selectionEnd()) {
        tempCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        if (!tempCursor.charFormat().fontItalic()) {
            return false;
        }
    }
    return true;
}

bool RichTextEdit::checkUnderline() {
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection()) {
        return false;
    }

    QTextCursor tempCursor = cursor;
    tempCursor.setPosition(cursor.selectionStart());
    while (tempCursor.position() < cursor.selectionEnd()) {
        tempCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        if (!tempCursor.charFormat().fontUnderline()) {
            return false;
        }
    }
    return true;
}

bool RichTextEdit::checkStrikeOut() {
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection()) {
        return false;
    }

    QTextCursor tempCursor = cursor;
    tempCursor.setPosition(cursor.selectionStart());
    while (tempCursor.position() < cursor.selectionEnd()) {
        tempCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        if (!tempCursor.charFormat().fontStrikeOut()) {
            return false;
        }
    }
    return true;
}

void RichTextEdit::checkFontSize() {
    QTextCursor cursor = textEdit->textCursor();
    if (cursor.charFormat().fontPointSize() == 0) {
        QTextCharFormat format = cursor.charFormat();
        format.setFontPointSize(FONT_SIZE);
        cursor.setCharFormat(format);
        textEdit->setTextCursor(cursor);
    }
}

void RichTextEdit::dropPicture(const QMimeData* source) {
    QImage image(source->urls().at(0).toLocalFile());
    if (image.isNull()) {
        qDebug() << "image is null";
        return;
    }
    addPicture(image);
}

QImage RichTextEdit::fitImage(const QImage& image) {
    int maxWidth = textEdit->width() * 0.9;
    if (image.width() > maxWidth) {
        return image.scaledToWidth(maxWidth, Qt::SmoothTransformation);
    }
    return image;
}

void RichTextEdit::adjustSize() {
    QTextDocument* document = textEdit->document();
    QTextBlock block = document->begin();
    while (block.isValid()) {
        for (auto i = block.begin(); i != block.end(); ++i) {
            QTextFragment fragment = i.fragment();
            QTextFormat format = i.fragment().charFormat();
            if (format.isImageFormat()) {
                QTextImageFormat imageFormat = format.toImageFormat();
                QImage image = document->resource(QTextDocument::ImageResource, imageFormat.name()).value<QImage>();
                QImage scaledImage = fitImage(image);
                imageFormat.setWidth(scaledImage.width());
                imageFormat.setHeight(scaledImage.height());

                QTextCursor cursor = textEdit->textCursor();
                cursor.setPosition(fragment.position());
                cursor.setPosition(fragment.position() + fragment.length(), QTextCursor::KeepAnchor);
                cursor.setCharFormat(imageFormat);
            }
        }
        block = block.next();
    }
}

void RichTextEdit::readonly(bool b) {
    textEdit->setReadOnly(b);
}


bool RichTextEdit::save(QUrl saveUrl) {
    qDebug() << "saveurl : " << saveUrl;
    //mkdir
    qDebug() << "saveUrl.toLocalFile()" << saveUrl;
    QString tempDir = QDir::cleanPath(QApplication::applicationDirPath() + QDir::separator() + "temp");
    QDir dir(tempDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QString tempDirPath = tempDir;
    qDebug() << "tempDirPath: " << tempDirPath;
    

    QTextDocument* copyDocument = new QTextDocument();
    copyDocument->setHtml(textEdit->document()->toHtml());

    // 保存图片到临时目录
    QTextDocument* document = textEdit->document();
    QTextBlock block = document->begin();
    int imageIndex = 0;
    while (block.isValid()) {
        for (auto i = block.begin(); i != block.end(); ++i) {
            QTextFragment fragment = i.fragment();
            QTextFormat format = i.fragment().charFormat();
            if (format.isImageFormat()) {
                QTextImageFormat imageFormat = format.toImageFormat();
                QImage image = document->resource(QTextDocument::ImageResource, imageFormat.name()).value<QImage>();
                QString imagePath = tempDirPath + QString("/image%1.png").arg(imageIndex++);
                image.save(imagePath);

                // 更新图片引用
                imageFormat.setName("image" + QString::number(imageIndex - 1) + ".png");
                QTextCursor cursor(copyDocument);
                cursor.setPosition(fragment.position());
                cursor.setPosition(fragment.position() + fragment.length(), QTextCursor::KeepAnchor);
                cursor.setCharFormat(imageFormat);
            }
        }
        block = block.next();
    }

    // 保存文档为 HTML 文件
    QTextDocumentWriter writer(tempDirPath + "/main.html", "HTML");
    writer.write(copyDocument);

    // 打包 HTML 文件和图片
    QProcess process;
    process.setProgram("zip");
    QStringList arguments;
    qDebug() << "saveUrl html" << tempDirPath + "/main.html";
    arguments << "-j" << saveUrl.toLocalFile() << tempDirPath + "/main.html";
    for (int i = 0; i < imageIndex; ++i) {
        arguments << tempDirPath + QString("/image%1.png").arg(i);
    }
    process.setArguments(arguments);
    process.start();
    if(process.waitForFinished()){
        qDebug() << "savesuccess---------------------------------";
        return process.exitCode() == 0;
    }else{
        qDebug() << "savefailed---------------------------------";
        return false;
    }
}

bool RichTextEdit::load(QUrl url) {
    QTemporaryDir tempDir;
    if (!tempDir.isValid()) {
        return false;
    }

    QString tempDirPath = tempDir.path();
    qDebug() << "tempDirPath: " << tempDirPath;

    QProcess process;
    process.setProgram("unzip");
    QStringList arguments;
    arguments << "-d" << tempDirPath << url.toLocalFile();
    process.setArguments(arguments);
    process.start();
    process.waitForFinished();
    if (process.exitCode() != 0) {
        return false;
    }

    QFile file(tempDirPath + "/main.html");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextDocumentWriter writer(tempDirPath + "/main.html", "HTML");
    writer.write(textEdit->document());
    return true;
}


//slots
void RichTextEdit::onTextChanged() {
}

void RichTextEdit::onCursorPositionChanged() {
    checkFontSize();
}

void RichTextEdit::onSelectionChanged() {
    boldAction->setChecked(checkBold());
    italicAction->setChecked(checkItalic());
    underlineAction->setChecked(checkUnderline());
    strikeOutAction->setChecked(checkStrikeOut());
}




