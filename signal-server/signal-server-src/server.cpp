#include <QtNetwork>
#include <QtMath>
#include <QDebug>

#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent){
    initServer();
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::sendSignal);
}

void Server::initServer(){
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen()){
        qCritical() << QString("Unable to start the server: %1.").arg(tcpServer->errorString());
        return;
    }

    QString ipAddress;
    const QList<QHostAddress> ipAddressList = QNetworkInterface::allAddresses();
    for (const QHostAddress &address: ipAddressList) {
        if (address != QHostAddress::LocalHost && address.toIPv4Address()) {
            ipAddress = address.toString();
        }
    }

    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qInfo() << QString("The server is running on IP: %1, port: %2. Run client app now.").arg(ipAddress).arg(tcpServer->serverPort());
}


void Server::sendSignal(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);

    out << Server::generateSignal();

    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);

    clientConnection->write(block);
}

QVector<QPair<float, float>> Server::generateSignal(){

    int amplitude = 1;
    int frequency = 1;
    int phase     = 0;

    QVector<QPair<float, float>> signal;

    for(float t = 0; t < 5; t += 0.01){
        float sin_signal = amplitude * qAsin(2 * M_PI * frequency * t + phase);

        // round value
        int rounded_sin_signal = QString("%1.3f").arg(sin_signal).toFloat();

        // add t (time means in sec) and rounded calculated sin value
        signal.push_back(qMakePair(t, rounded_sin_signal));
    }

    return signal;
}
