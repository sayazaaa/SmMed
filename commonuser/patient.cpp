#include "patient.h"
#include "ui_patient.h"

patient::patient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::patient)
{
    int patient_number=0;
    //select sentence   "SELECT COUNT(name) as patient_number FROM patient WHERE user_id = [your_user_id];"
    for(int i=0; i< patient_number ; i++){
        //创建item
        little_appointment *w = new little_appointment;
        QListWidgetItem* pItem = new QListWidgetItem;
        //填入数据
        w->set_apartment("电话");
        w->set_name("患者");
        w->set_btn_yes("查看并编辑");
        w->btn_more_hide();

        w->set_label_doc_name("");
        w->set_label_gender("");
        w->set_label_apartment("");

    //    pItem->setBackground(QColor("green"));
        //设置item大小
        pItem->setSizeHint(QSize(ui->patient_list->width()/3-10,ui->patient_list->height()/3 ));
        //添加进QlistWidget
        ui->patient_list->addItem(pItem);
        ui->patient_list->setItemWidget(pItem, w);
        //不可被选中
        pItem->setFlags(pItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    }
    ui->setupUi(this);
}

patient::~patient()
{
    delete ui;
}
