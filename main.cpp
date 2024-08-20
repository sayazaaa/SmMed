#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>

int main(int argc, char* argv[]){
    QApplication app(argc,argv);
    QWidget w;
    w.resize(400, 400);
    
    //QWidget类是所有用户界面对象的基类
    //在这里可以把它看作一个窗口，构造了一个窗口对象
    w.setWindowTitle("Hello World!");
    //将窗口的标题设为Hello World!
    QLabel textLabel;
    QButtonGroup buttonGroup;
    QPushButton button1(&w);
    buttonGroup.addButton(&button1, 1);
    button1.setText("Button1");
    button1.move(150, 150);
    button1.show();

    //构造一个标签
    textLabel.resize(100,15);
    //设定标签宽40高15
    textLabel.move(150, 170);
    //将标签移动到距离左上角水平100px垂直130px的位置
    textLabel.setText("Hello vgjhhhjvhvhjhWorld!");
    //标签的初始显示字符串NULL
    textLabel.setParent(&w);
    textLabel.show();
    w.show();
    //显示窗体
    return app.exec();
}
