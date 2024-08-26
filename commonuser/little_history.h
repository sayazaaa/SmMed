#ifndef LITTLE_HISTORY_H
#define LITTLE_HISTORY_H

#include <QWidget>

namespace Ui {
class little_history;
}

class little_history : public QWidget
{
    Q_OBJECT

public:
    void set_label_user_name(const QString &text);
    void set_label_date(const QString &text);
    void set_label_time(const QString &text);
    void set_label_doc_name(const QString &text);
    void set_label_apartment(const QString &text);
    explicit little_history(QWidget *parent = nullptr);
    ~little_history();

private:
    Ui::little_history *ui;
};

#endif // LITTLE_HISTORY_H
