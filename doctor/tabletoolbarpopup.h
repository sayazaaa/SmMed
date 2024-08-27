#ifndef TABLETOOLBARPOPUP_H
#define TABLETOOLBARPOPUP_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class TableToolBarPopup : public QWidget
{
    Q_OBJECT

public:
    TableToolBarPopup(QWidget *parent = nullptr);
    int rows() const;
    int columns() const;

signals:
    void accepted();
    void rejected();

private:
    QLineEdit *rowsEdit;
    QLineEdit *columnsEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // TABLETOOLBARPOPUP_H