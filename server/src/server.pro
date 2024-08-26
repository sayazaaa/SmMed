TEMPLATE = app
CONFIG += qt debug
CONFIG -= app_bundle
CONFIG += c++14

# 项目信息
QT += core network
TARGET = your_project_name
DESTDIR = bin

# 编译选项
QMAKE_CXXFLAGS += -fPIC -Wall -Wno-unused-variable
QMAKE_CFLAGS += -fPIC -Wall -Wno-unused-variable

# 调试和发布配置
NODEBUG = OFF
!equals(NODEBUG, "OFF") {
    QMAKE_CXXFLAGS += -s -O3
    QMAKE_CFLAGS += -s -O3
} else {
    QMAKE_CXXFLAGS += -pg -g3
    QMAKE_CFLAGS += -pg -g3
}

# 包含目录
INCLUDEPATH += $$PWD/models \
               $$PWD/handlers \
               $$PWD/requests

# 库目录
LIBS += -L$$[QT_INSTALL_LIBS] -L$$PWD/lib

# 源文件
SOURCES += $$PWD/models/model1.cpp \
           $$PWD/handlers/handler1.cpp \
           $$PWD/requests/request1.cpp \
           $$PWD/main.cpp

# 链接库
LIBS += -lssl -lcrypto -lqhttpengine

# 安装目标
target.path = $$[QT_INSTALL_BINS]
INSTALLS += target