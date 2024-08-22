#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QDir>
#include <QDebug>

class SimpleHttpServer : public QTcpServer
{
    Q_OBJECT

public:
    SimpleHttpServer(QObject *parent = nullptr) : QTcpServer(parent) {}

protected:
    void incomingConnection(qintptr socketDescriptor) override
    {
        QTcpSocket *socket = new QTcpSocket(this);
        connect(socket, &QTcpSocket::readyRead, this, &SimpleHttpServer::handleRequest);
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

        socket->setSocketDescriptor(socketDescriptor);
    }

private slots:
    void handleRequest()
    {
        QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
        if (!socket)
            return;

        QByteArray request = socket->readAll();
        qDebug() << ""

        // 解析HTTP请求头部
        if (request.startsWith("POST"))
        {
            int headerEndIndex = request.indexOf("\r\n\r\n");
            if (headerEndIndex != -1)
            {
                QByteArray headers = request.left(headerEndIndex);
                QByteArray body = request.mid(headerEndIndex + 4);

                // 查找Content-Type以解析multipart/form-data
                if (headers.contains("Content-Type: multipart/form-data"))
                {
                    int boundaryIndex = headers.indexOf("boundary=");
                    if (boundaryIndex != -1)
                    {
                        QString boundary = headers.mid(boundaryIndex + 9).split("\r\n").first();
                        boundary.prepend("--");

                        QList<QByteArray> parts = body.split(boundary.toUtf8());

                        for (const QByteArray &part : parts)
                        {
                            if (part.contains("Content-Disposition: form-data"))
                            {
                                if (part.contains("filename=\""))
                                {
                                    // 提取并保存文件
                                    int fileStart = part.indexOf("\r\n\r\n") + 4;
                                    int fileEnd = part.lastIndexOf("\r\n--");

                                    QByteArray fileData = part.mid(fileStart, fileEnd - fileStart);

                                    QString filename = "uploads/uploaded_file.jpg"; // 保存的文件名
                                    QFile file(filename);
                                    if (file.open(QIODevice::WriteOnly))
                                    {
                                        file.write(fileData);
                                        file.close();
                                    }
                                }
                                else if (part.contains("name=\"content\""))
                                {
                                    // 解析富文本内容
                                    int contentStart = part.indexOf("\r\n\r\n") + 4;
                                    int contentEnd = part.lastIndexOf("\r\n--");

                                    QByteArray contentData = part.mid(contentStart, contentEnd - contentStart);

                                    // 这里处理contentData，例如存储或处理
                                }
                            }
                        }
                    }
                }

                // 返回响应
                QByteArray response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFile uploaded successfully!";
                socket->write(response);
                socket->disconnectFromHost();
            }
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SimpleHttpServer server;
    if (!server.listen(QHostAddress::Any, 8080))
    {
        qFatal("Failed to start server");
    }
    else
    {
        qDebug() << "Server started on port 8080";
    }

    return a.exec();
}

