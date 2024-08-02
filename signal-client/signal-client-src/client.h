#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent);
private slots:
    void requestNewSignal();
    void readSignal();
    void displayError();
private:
    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    QString signal;
};

#endif // CLIENT_H
