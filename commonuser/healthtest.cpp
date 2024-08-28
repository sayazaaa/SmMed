#include "healthtest.h"
#include "ui_healthtest.h"

HealthTest::HealthTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HealthTest)
{
    ui->setupUi(this);
}

HealthTest::~HealthTest()
{
    delete ui;
}

void HealthTest::on_pushButton_clicked()
{
    int age = ui->age->text().toInt();
    double height = ui->height->text().toDouble();
    double weight = ui->weight->text().toDouble();
    int systolicBP = ui->s_pressure->text().toInt();
    int diastolicBP = ui->d_pressure->text().toInt();
    double glucose = ui->blood_sugar->text().toDouble();
    double lungCapacity = ui->vc->text().toDouble();

    // 评估健康状况
    bool healthyAge = true; // 假设年龄不是评估因素
    bool healthyHeight ;
    // 判断身高是否健康
           if (age < 18) { // 儿童和青少年
               healthyHeight = (height >= 120 && height <= 180);
           } else if (age >= 18 && age <= 65) { // 成人
               healthyHeight = (height >= 140 && height <= 220);
           } else { // 老年人
               healthyHeight = (height >= 140 && height <= 200);
           }

    bool healthySystolicBP = (systolicBP >= 90 && systolicBP <= 120);
    bool healthyDiastolicBP = (diastolicBP >= 60 && diastolicBP <= 80);
    bool healthyGlucose = (glucose >= 3.9 && glucose <= 6.1); // 空腹血糖正常范围
    bool healthyLungCapacity = (lungCapacity >= 3000 && lungCapacity <= 5000); // 成人肺活量范围

    // BMI 计算
    double bmi = weight / ((height / 100) * (height / 100));
    bool healthyBMI = (bmi >= 18.5 && bmi <= 24.9);

    // 构建反馈字符串
            QString feedback;
            feedback.append("健康评估结果：\n");
            if (healthyAge && healthyHeight &&  healthyBMI && healthySystolicBP && healthyDiastolicBP && healthyGlucose && healthyLungCapacity) {
               feedback.append("您的健康状况良好。\n");
            } else {
               feedback.append("您的健康状况存在一些问题。\n");
            }

            // 年龄
            feedback.append(QString("年龄: %1 \n").arg(age));

            // 身高
            if (healthyHeight) {
                       feedback.append(QString("身高: %1 cm (健康)\n").arg(height));
                    } else if (height < (age < 18 ? 120 : (age >= 18 && age <= 65 ? 140 : 140))) {
                       feedback.append(QString("身高: %1 cm (过低)\n").arg(height));
                    } else {
                       feedback.append(QString("身高: %1 cm (过高)\n").arg(height));
                    }

            // 体重
            feedback.append(QString("体重: %1 kg \n").arg(weight));

            // BMI
            if (healthyBMI) {
               feedback.append(QString("BMI: %1 (健康)\n").arg(bmi));
            } else if (bmi < 18.5) {
               feedback.append(QString("BMI: %1 (过轻)\n").arg(bmi));
            } else {
               feedback.append(QString("BMI: %1 (过重)\n").arg(bmi));
            }

            // 血压
            if (healthySystolicBP && healthyDiastolicBP) {
               feedback.append(QString("血压: %1/%2 mmHg (健康)\n").arg(systolicBP).arg(diastolicBP));
            } else if (systolicBP < 90 || diastolicBP < 60) {
               feedback.append(QString("血压: %1/%2 mmHg (过低)\n").arg(systolicBP).arg(diastolicBP));
            } else {
               feedback.append(QString("血压: %1/%2 mmHg (过高)\n").arg(systolicBP).arg(diastolicBP));
            }

            // 血糖
            if (healthyGlucose) {
               feedback.append(QString("血糖: %1 mmol/L (健康)\n").arg(glucose));
            } else if (glucose < 3.9) {
               feedback.append(QString("血糖: %1 mmol/L (过低)\n").arg(glucose));
            } else {
               feedback.append(QString("血糖: %1 mmol/L (过高)\n").arg(glucose));
            }

            // 肺活量
            if (healthyLungCapacity) {
               feedback.append(QString("肺活量: %1 mL (健康)\n").arg(lungCapacity));
            } else if (lungCapacity < 3000) {
               feedback.append(QString("肺活量: %1 mL (过低)\n").arg(lungCapacity));
            } else {
               feedback.append(QString("肺活量: %1 mL (肺功能良好)\n").arg(lungCapacity));
            }

            // 显示评估结果
            QMessageBox msgBox;
            msgBox.setWindowTitle("评估结果");

            // 设置详细文本为反馈字符串
            msgBox.setText(feedback);

            // 显示评估结果和反馈列表
            msgBox.exec();
}

