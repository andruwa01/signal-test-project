#ifndef SERVER_H
#define SERVER_H

#include <QString>
#include <QObject>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
class QTcpServer;
QT_END_NAMESPACE

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
private slots:
    void sendSignal();
private:
    void initServer();
    QTcpServer *tcpServer = nullptr;
    QVector<QPair<float, float>> generateSignal();
    QString generatedSignal;
};

#endif // SERVER_H
