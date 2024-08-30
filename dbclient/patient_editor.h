#ifndef PATIENT_EDITOR_H
#define PATIENT_EDITOR_H

#include <QWidget>

namespace Ui {
class patient_editor;
}

class patient_editor : public QWidget
{
    Q_OBJECT

public:
    explicit patient_editor(QWidget *parent = nullptr);
    ~patient_editor();
    void set_name(const QString &text);
    void set_gender(const QString &text);
    void set_id(const QString &text);
    void set_phone(const QString &text);

private:
    Ui::patient_editor *ui;
};

#endif // PATIENT_EDITOR_H
